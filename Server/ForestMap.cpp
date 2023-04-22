#include "pch.h"
#include "ForestMap.h"
#include <filesystem>
#include <fstream>
#include "Player.h"
#include "Room.h"
#include "Protocol.pb.h"
#include "Bomb.h"
namespace fs = std::filesystem;

Vector2Int ForestMap::WorldToCell(Vector2 pos)
{
	return Vector2Int(static_cast<int32>(std::floor(pos.x)), static_cast<int32>(std::floor(pos.y)));
}

Vector2 ForestMap::CellToWorld(Vector2Int pos)
{
	return Vector2(pos.x + .5f, pos.y + .5f);
}

Protocol::PCellPos* ForestMap::GetCellPosProtocol(Vector2Int cellPos)
{
	Protocol::PCellPos* pcellpos = new Protocol::PCellPos();
	pcellpos->set_posx(cellPos.x);
	pcellpos->set_posy(cellPos.y);
	return pcellpos;
}

Protocol::PWorldPos* ForestMap::GetWorldPosProtocol(Vector2 worldPos)
{
	Protocol::PWorldPos* pworldpos = new Protocol::PWorldPos();
	pworldpos->set_posx(worldPos.x);
	pworldpos->set_posy(worldPos.y);
	return pworldpos;
}

bool ForestMap::CanGo(Vector2Int cellPos)
{
	if (cellPos.x < MinX || cellPos.x > MaxX)
		return false;
	if (cellPos.y < MinY || cellPos.y > MaxY)
		return false;

	int x = cellPos.x - MinX;
	int y = MaxY - cellPos.y;

	if (_blocks[y][x] != 0)
		return false;

	auto findIt = _bombs.find(cellPos);
	if (findIt != _bombs.end())
		return false;

	return true;
}

void ForestMap::ApplyMove(PlayerRef player, Vector2Int dest)
{
	ApplyLeave(player);

	if (CanGo(dest) == false)
		return;

	_players[player] = dest;

	// 실제 좌표 이동
	player->SetCellPos(dest);

#pragma region LOG
	{
		wstringstream log;
		log << L"Player ID : ";
		log << player->PlayerInfo.id();
		log << L" | MOVE(";
		log << player->PosInfo.cellpos().posx();
		log << L", ";
		log << player->PosInfo.cellpos().posy();
		log << L")";
		Utils::Log(log);
	}
#pragma endregion

	// 이동 중에 물풍선 갇힌 애들 발견했을 때
	if (player->PosInfo.state() == Protocol::PPlayerState::MOVING)
	{
		Vector<PlayerRef> pvec = FindPlayer(dest, player);
		if (pvec.size() != 0)
		{
			// TODO : 같은 팀이라면 살려주기
			for (PlayerRef p : pvec)
			{
				if (p->PosInfo.state() == Protocol::PPlayerState::INTRAP)
				{
					p->GetRoom()->PlayerDead(p);
					wstringstream log;
					log << L"Player ID : ";
					log << player->PlayerInfo.id();
					log << L" killed ";
					log << p->PlayerInfo.id();
					Utils::Log(log);
				}
			}
		}
	}

	// 아이템 획득
	auto findIt = _spawnItems.find(dest);
	if (findIt != _spawnItems.end())
	{
		Protocol::PItemType type = findIt->second;
		Protocol::S_ITEMACQUISITION itemSpawnPkt;
		player->ApplyItemAbility(type);
		itemSpawnPkt.set_allocated_playerinfo(player->GetPlayerProtocol());
		auto* itemCellPos = new Protocol::PCellPos();
		itemCellPos->set_posx(findIt->first.x);
		itemCellPos->set_posy(findIt->first.y);
		itemSpawnPkt.set_allocated_itempos(itemCellPos);
		_spawnItems.erase(dest);
		OwnerRoom->Broadcast(itemSpawnPkt);
	}
}

void ForestMap::ApplyLeave(PlayerRef player)
{
	_players.erase(player);
}

Vector<PlayerRef> ForestMap::FindPlayer(Vector2Int cellPos, PlayerRef exceptPlayer/*= nullptr*/)
{
	Vector<PlayerRef> ret;
	if (cellPos.x < MinX || cellPos.x > MaxX)
		return ret;
	if (cellPos.y < MinY || cellPos.y > MaxY)
		return ret;

	for (auto& p : _players)
	{
		if (exceptPlayer != nullptr && exceptPlayer == p.first)
			continue;

		if (p.second == cellPos)
			ret.push_back(p.first);
	}

	return ret;
}

Vector2Int ForestMap::FindPlayer(PlayerRef player)
{
	auto findIt = _players.find(player);
	if (findIt == _players.end())
		return Vector2Int::null();

	return findIt->second;
}

BombRef ForestMap::FindBomb(Vector2Int cellPos)
{
	auto findIt = _bombs.find(cellPos);
	if (findIt == _bombs.end())
		return nullptr;

	return findIt->second;
}

bool ForestMap::SetBomb(Vector2Int pos, PlayerRef ownerPlayer)
{
	if (CanGo(pos) == false)
		return false;

	if (ownerPlayer->AddBomb() == false)
		return false;

	BombRef bomb = MakeShared<Bomb>();
	bomb->OwnerPlayer = ownerPlayer;

	_bombs[pos] = bomb;
	return true;
}

void ForestMap::DestroyBomb(Vector2Int pos, int32 range, Protocol::S_BOMBEND& pkt)
{
	auto findIt = _bombs.find(pos);
	if (findIt == _bombs.end())
		return;

	pkt.set_allocated_bombcellpos(GetCellPosProtocol(pos));

	findIt->second->OwnerPlayer->SubBomb();
	_bombs.erase(pos);

	Vector<PlayerRef> vec = FindPlayer(pos);
	for (PlayerRef player : vec)
	{
		if (player != nullptr)
		{
			// TRAP
			auto* trapPlayer = pkt.add_trapplayers();
			player->OnTrap();
			trapPlayer->CopyFrom(player->PlayerInfo);
		}
	}

	// 위 방향 물줄기
	for (int32 i = 1; i <= range; i++)
	{
		Vector2Int upRange = pos + Vector2Int(0, i);
		if (CheckWaterCourse(upRange) == false)
			break;
	}
	// 오른쪽 방향 물줄기
	for (int32 i = 1; i <= range; i++)
	{
		Vector2Int rightRange = pos + Vector2Int(i, 0);
		if (CheckWaterCourse(rightRange) == false)
			break;
	}
	// 아래 방향 물줄기
	for (int32 i = 1; i <= range; i++)
	{
		Vector2Int downRange = pos + Vector2Int(0, -i);
		if (CheckWaterCourse(downRange) == false)
			break;
	}
	// 왼쪽 방향 물줄기
	for (int32 i = 1; i <= range; i++)
	{
		Vector2Int leftRange = pos + Vector2Int(-i, 0);
		if (CheckWaterCourse(leftRange) == false)
			break;
	}
}

bool ForestMap::CheckWaterCourse(Vector2Int pos)
{
	int32 x = pos.x - MinX;
	int32 y = MaxY - pos.y;
	if (CanGo(pos) == false)
	{
		// Destroy
		if (_blocks[y][x] == 2)
		{
			_destroyObjects.insert(pos);
			return false;
		}

		auto findIt = _bombs.find(pos);
		if (findIt != _bombs.end())
		{
			// 연달아 터지게
			BombRef bomb = findIt->second;
			Protocol::S_BOMBEND bombEndPkt;
			bombEndPkt.set_allocated_player(bomb->OwnerPlayer->GetPlayerProtocol());
			DestroyBomb(pos, bomb->OwnerPlayer->PlayerInfo.bombrange(), bombEndPkt);
			OwnerRoom->Broadcast(bombEndPkt);
			wstringstream log;
			log << L"Player ID : " << bomb->OwnerPlayer->PlayerInfo.id();
			log << L" A bomb located at (" << pos.x << ", " << pos.y << ")" << L" exploded.";
			Utils::Log(log);
		}

		return false;
	}
	// TODO : 아이템은 사라지게

	Vector<PlayerRef> vec = FindPlayer(pos);
	for (PlayerRef player : vec)
	{
		if (player != nullptr)
		{
			// TRAP
			_trapPlayers.insert(player);
		}
	}

	return true;
}

void ForestMap::BombResult(Protocol::S_BOMBEND& pkt)
{
	::srand(static_cast<uint32>(time(nullptr)));
	for (Vector2Int pos : _destroyObjects)
	{
		auto* cellpos = pkt.add_destroyobjectcellposes();
		cellpos->set_posx(pos.x);
		cellpos->set_posy(pos.y);
		int32 x = pos.x - MinX;
		int32 y = MaxY - pos.y;
		_blocks[y][x] = 0;

		int32 probability = ::rand() % 10;
		if (probability < 2)
			SpawnItem(pos);
	}
	for (PlayerRef player : _trapPlayers)
	{
		auto* trapPlayer = pkt.add_trapplayers();
		player->OnTrap();
		trapPlayer->CopyFrom(player->PlayerInfo);
	}
	_destroyObjects.clear();
	_trapPlayers.clear();
}

void ForestMap::SpawnItem(Vector2Int pos)
{
	// 물풍선 : 물병 : 스케이트 : 해골
	//    3   :   3  :     3    :   1
	Protocol::S_ITEMSPAWN itemSpawnPkt;
	Protocol::PCellPos* cellpos = new Protocol::PCellPos();
	cellpos->set_posx(pos.x);
	cellpos->set_posy(pos.y);
	itemSpawnPkt.set_allocated_cellpos(cellpos);

	wstringstream log;
	log << L"ITEM SPAWN AT (" << pos.x << L", " << pos.y << L")";
	int32 probability = ::rand() % 10;
	switch (probability)
	{
	case 0:
	case 1:
	case 2:
		itemSpawnPkt.set_itemtype(Protocol::PItemType::INCBOMBCOUNT);
		log << L" BOMBCOUNT+1 ITEM";
		break;
	case 3:
	case 4:
	case 5:
		itemSpawnPkt.set_itemtype(Protocol::PItemType::INCBOMBRANGE);
		log << L" BOMBRANGE+1 ITEM";
		break;
	case 6:
	case 7:
	case 8:
		itemSpawnPkt.set_itemtype(Protocol::PItemType::INCSPEED);
		log << L" SPEED+1 ITEM";
		break;
	case 9:
		itemSpawnPkt.set_itemtype(Protocol::PItemType::MAXBOMBRANGE);
		log << L" BOMBRANGEMAX ITEM";
		break;
	default:
		break;
	}
	Utils::Log(log);
	_spawnItems[pos] = itemSpawnPkt.itemtype();
	OwnerRoom->Broadcast(itemSpawnPkt);
}

void ForestMap::LoadMap(wstring pathPrefix /*= L"../Common/MapData"*/)
{
	// 폴더 경로 설정
	fs::path folder_path = fs::path(pathPrefix).lexically_normal();

	// 폴더 내 모든 파일을 탐색
	for (auto& file : fs::recursive_directory_iterator(folder_path))
	{
		// 파일이 텍스트 파일인 경우에만 처리
		if (file.path().extension() == ".txt" && file.path().filename() == "ForestMapInfo.txt")
		{
			// 파일 읽기
			std::wifstream infile(file.path());
			if (!infile.is_open())
			{
				std::cerr << "Error opening file " << file.path() << std::endl;
				continue;
			}

			std::wstring line;
			::getline(infile, line);
			MinX = stoi(line);
			::getline(infile, line);
			MaxX = stoi(line);
			::getline(infile, line);
			MinY = stoi(line);
			::getline(infile, line);
			MaxY = stoi(line);

			int xCount = MaxX - MinX + 1;
			int yCount = MaxY - MinY + 1;

			_blocks = Vector<Vector<int>>(yCount, Vector<int>(xCount));
			for (int y = 0; y < yCount; y++)
			{
				::getline(infile, line);
				for (int x = 0; x < xCount; x++)
				{
					_blocks[y][x] = line[x] - '0';
				}
			}
		}
	}

	wstringstream log;
	log << L"LOAD FORESTMAP";
	Utils::Log(log);
}
