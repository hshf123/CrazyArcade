#include "pch.h"
#include "ForestMap.h"
#include <filesystem>
#include <fstream>
#include "Player.h"
#include "Room.h"
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

void ForestMap::EnterPlayer(Vector2Int cellPos, PlayerRef player)
{
	if (player == nullptr)
		return;

	_players[player] = cellPos;
}

bool ForestMap::MovePlayer(Vector2Int prevPos, Vector2Int afterPos, PlayerRef player)
{
	if (CanGo(afterPos) == false)
		return false;

	if (FindPlayer(player) != prevPos)
		return false;

	if ((afterPos - prevPos).sqrMagnitude() > 1)
		return false;

	_players[player] = afterPos;

	if (player->PosInfo.state() == Protocol::PPlayerState::MOVING)
	{
		Vector<PlayerRef> pvec = FindPlayer(afterPos, player);
		if (pvec.size() == 0)
			return true;

		// TODO : 같은 팀이라면 살려주기
		for (PlayerRef p : pvec)
		{
			if (p->PosInfo.state() == Protocol::PPlayerState::INTRAP)
				p->GetRoom()->PlayerDead(p);
		}
	}

	auto* cellPos = player->PosInfo.cellpos().New();
	cellPos->set_posx(afterPos.x);
	cellPos->set_posy(afterPos.y);

	return true;
}

void ForestMap::LeavePlayer(Vector2Int cellPos, PlayerRef player)
{
	if (FindPlayer(player) == Vector2Int::null())
		return;

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

	auto* cellpos = pkt->add_cellposes();
	cellpos->set_posx(pos.x);
	cellpos->set_posy(pos.y);
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

	for (int32 i = 1; i <= range; i++)
	{
		Vector2Int upRange = pos + Vector2Int(0, i);
		int32 x = upRange.x - MinX;
		int32 y = MaxY - upRange.y;
		if (CanGo(upRange) == false)
		{
			// Destroy
			if (_blocks[y][x] == 2)
			{
				auto* cellpos = pkt->add_cellposes();
				cellpos->set_posx(upRange.x);
				cellpos->set_posy(upRange.y);
				_blocks[y][x] = 0;
				break;
			}
			else if (_blocks[y][x] == 3)
			{
				// 연달아 터지게
				
				Vector<PlayerRef> vec = FindPlayer(upRange);
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
				break;
			}
		}

		Vector<PlayerRef> vec = FindPlayer(upRange);
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
	for (int32 i = 1; i <= range; i++)
	{
		Vector2Int rightRange = pos + Vector2Int(i, 0);
		int32 x = rightRange.x - MinX;
		int32 y = MaxY - rightRange.y;
		if (CanGo(rightRange) == false)
		{
			// Destroy
			if (_blocks[y][x] == 2)
			{
				auto* cellpos = pkt->add_cellposes();
				cellpos->set_posx(rightRange.x);
				cellpos->set_posy(rightRange.y);
				_blocks[y][x] = 0;
				break;
			}
			else if (_blocks[y][x] == 3)
			{
				// 연달아 터지게

				Vector<PlayerRef> vec = FindPlayer(rightRange);
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
				break;
			}
		}

		Vector<PlayerRef> vec = FindPlayer(rightRange);
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
	for (int32 i = 1; i <= range; i++)
	{
		Vector2Int downRange = pos + Vector2Int(0, -i);
		int32 x = downRange.x - MinX;
		int32 y = MaxY - downRange.y;
		if (CanGo(downRange) == false)
		{
			// Destroy
			if (_blocks[y][x] == 2)
			{
				auto* cellpos = pkt->add_cellposes();
				cellpos->set_posx(downRange.x);
				cellpos->set_posy(downRange.y);
				_blocks[y][x] = 0;
				break;
			}
			else if (_blocks[y][x] == 3)
			{
				// 연달아 터지게

				Vector<PlayerRef> vec = FindPlayer(downRange);
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
				break;
			}
		}

		Vector<PlayerRef> vec = FindPlayer(downRange);
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
	for (int32 i = 1; i <= range; i++)
	{
		Vector2Int leftRange = pos + Vector2Int(-i, 0);
		int32 x = leftRange.x - MinX;
		int32 y = MaxY - leftRange.y;
		if (CanGo(leftRange) == false)
		{
			// Destroy
			if (_blocks[y][x] == 2)
			{
				auto* cellpos = pkt->add_cellposes();
				cellpos->set_posx(leftRange.x);
				cellpos->set_posy(leftRange.y);
				_blocks[y][x] = 0;
				break;
			}
			else if (_blocks[y][x] == 3)
			{
				// 연달아 터지게

				Vector<PlayerRef> vec = FindPlayer(leftRange);
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
				break;
			}
		}

		Vector<PlayerRef> vec = FindPlayer(leftRange);
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
			getline(infile, line);
			MinX = stoi(line);
			getline(infile, line);
			MaxX = stoi(line);
			getline(infile, line);
			MinY = stoi(line);
			getline(infile, line);
			MaxY = stoi(line);

			int xCount = MaxX - MinX + 1;
			int yCount = MaxY - MinY + 1;

			_blocks = Vector<Vector<int>>(yCount, Vector<int>(xCount));
			for (int y = 0; y < yCount; y++)
			{
				getline(infile, line);
				for (int x = 0; x < xCount; x++)
				{
					_blocks[y][x] = line[x] - '0';
				}
			}
		}
	}
}
