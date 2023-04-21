#include "pch.h"
#include "ForestMap.h"
#include <filesystem>
#include <fstream>
#include "Player.h"
#include "Room.h"
#include "Protocol.pb.h"
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

bool ForestMap::CanGo(Vector2Int cellPos, bool checkObjects /*= true*/)
{
	if (cellPos.x < MinX || cellPos.x > MaxX)
		return false;
	if (cellPos.y < MinY || cellPos.y > MaxY)
		return false;

	int x = cellPos.x - MinX;
	int y = MaxY - cellPos.y;

	if (_blocks[y][x] != 0)
		return false;

	return true;
}

void ForestMap::ApplyMove(PlayerRef player, Vector2Int dest)
{
	ApplyLeave(player);

	if (CanGo(dest, true) == false)
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
		Vector<PlayerRef> pvec = FindPlayer(player->GetCellPos(), player);
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
	auto findIt = _spawnItems.find(player->GetCellPos());
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
		_spawnItems.erase(player->GetCellPos());
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

bool ForestMap::FindBomb(Vector2Int cellPos)
{
	return _blocks[cellPos.x][cellPos.y] == 3;
}

bool ForestMap::SetBomb(Vector2Int pos)
{
	if (CanGo(pos) == false)
		return false;

	int x = pos.x - MinX;
	int y = MaxY - pos.y;
	_blocks[y][x] = 3;
	return true;
}

void ForestMap::DestroyBomb(Vector2Int pos, int32 range, Protocol::S_BOMBEND* pkt)
{
	int x = pos.x - MinX;
	int y = MaxY - pos.y;
	if (_blocks[y][x] != 3)
		return;

	pkt->set_allocated_bombcellpos(GetCellPosProtocol(pos));

	_blocks[y][x] = 0;

	Vector<PlayerRef> vec = FindPlayer(pos);
	for (PlayerRef player : vec)
	{
		if (player != nullptr)
		{
			// TRAP
			auto* trapPlayer = pkt->add_trapplayers();
			player->OnTrap();
			trapPlayer->CopyFrom(player->PlayerInfo);
		}
	}

	// 위 방향 물줄기
	for (int32 i = 1; i <= range; i++)
	{
		Vector2Int upRange = pos + Vector2Int(0, i);
		if (CheckWaterCourse(upRange, pkt) == false)
			break;
	}
	// 오른쪽 방향 물줄기
	for (int32 i = 1; i <= range; i++)
	{
		Vector2Int rightRange = pos + Vector2Int(i, 0);
		if (CheckWaterCourse(rightRange, pkt) == false)
			break;
	}
	// 아래 방향 물줄기
	for (int32 i = 1; i <= range; i++)
	{
		Vector2Int downRange = pos + Vector2Int(0, -i);
		if (CheckWaterCourse(downRange, pkt) == false)
			break;
	}
	// 왼쪽 방향 물줄기
	for (int32 i = 1; i <= range; i++)
	{
		Vector2Int leftRange = pos + Vector2Int(-i, 0);
		if (CheckWaterCourse(leftRange, pkt) == false)
			break;
	}

	::srand(static_cast<uint32>(time(nullptr)));
	for (auto& cellpos : pkt->destroyobjectcellposes())
	{
		int32 probability = ::rand() % 10;
		if (probability < 2)
			SpawnItem(Vector2Int(cellpos.posx(), cellpos.posy()));
	}
}

bool ForestMap::CheckWaterCourse(Vector2Int pos, Protocol::S_BOMBEND* pkt)
{
	int32 x = pos.x - MinX;
	int32 y = MaxY - pos.y;
	if (CanGo(pos) == false)
	{
		// Destroy
		if (_blocks[y][x] == 2)
		{
			auto* cellpos = pkt->add_destroyobjectcellposes();
			cellpos->set_posx(pos.x);
			cellpos->set_posy(pos.y);
			_blocks[y][x] = 0;
			return false;
		}
		else if (_blocks[y][x] == 3)
		{
			// TODO : 연달아 터지게

			Vector<PlayerRef> vec = FindPlayer(pos);
			for (PlayerRef player : vec)
			{
				if (player != nullptr)
				{
					// TRAP
					auto* trapPlayer = pkt->add_trapplayers();
					player->OnTrap();
					trapPlayer->CopyFrom(player->PlayerInfo);
				}
			}
		}
		else
		{
			return false;
		}
	}

	Vector<PlayerRef> vec = FindPlayer(pos);
	for (PlayerRef player : vec)
	{
		if (player != nullptr)
		{
			// TRAP
			auto* trapPlayer = pkt->add_trapplayers();
			player->OnTrap();
			trapPlayer->CopyFrom(player->PlayerInfo);
		}
	}

	return true;
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
