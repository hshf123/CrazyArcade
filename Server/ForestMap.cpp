#include "pch.h"
#include "ForestMap.h"
#include <filesystem>
#include <fstream>
#include "Player.h"
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
	int32 x = cellPos.x - MinX;
	int32 y = MaxY - cellPos.y;
	_players[y][x] = player;
}

bool ForestMap::MovePlayer(Vector2Int prevPos, Vector2Int afterPos, PlayerRef player)
{
	if (CanGo(afterPos) == false)
		return false;

	if (FindPlayer(prevPos) == nullptr)
		return false;

	int32 x = afterPos.x - MinX;
	int32 y = MaxY - afterPos.y;
	_players[y][x] = player;

	x = afterPos.x - MinX;
	y = MaxY - afterPos.y;
	_players[y][x] = player;

	return true;
}

void ForestMap::LeavePlayer(Vector2Int cellPos, PlayerRef player)
{
	if (FindPlayer(cellPos) == nullptr)
		return;

	int32 x = cellPos.x - MinX;
	int32 y = MaxY - cellPos.y;
	_players[y][x] = nullptr;
}

PlayerRef ForestMap::FindPlayer(Vector2Int cellPos)
{
	if (cellPos.x < MinX || cellPos.x > MaxX)
		return nullptr;
	if (cellPos.y < MinY || cellPos.y > MaxY)
		return nullptr;

	int x = cellPos.x - MinX;
	int y = MaxY - cellPos.y;
	return _players[y][x];
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

	// 범위 내에 destroy and 플레이어면 물풍선 가두기
	for (int32 i = 1; i <= range; i++)
	{
		Vector2Int ranges[4];
		ranges[0] = pos + Vector2Int(0, i);
		ranges[1] = pos + Vector2Int(i, 0);
		ranges[2] = pos + Vector2Int(0, -i);
		ranges[3] = pos + Vector2Int(-i, 0);
		for (int32 i = 0; i < 4; i++)
		{
			Vector2Int range = ranges[i];
			int32 x = range.x - MinX;
			int32 y = MaxY - range.y;
			if (CanGo(range) == false && _blocks[y][x] == 2)
			{
				// Destroy
				auto* cellpos = pkt->add_cellposes();
				cellpos->set_posx(range.x);
				cellpos->set_posy(range.y);
				_blocks[y][x] = 0;
			}

			PlayerRef player = FindPlayer(range);
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

			_blocks = vector<vector<int>>(yCount, vector<int>(xCount));
			_players = vector<vector<PlayerRef>>(yCount, vector<PlayerRef>(xCount));
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
