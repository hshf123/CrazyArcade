#pragma once
#include "Protocol.pb.h"

using PositionInfo = Protocol::PPositionInfo;
using CellPos = Protocol::PCellPos;
using WorldPos = Protocol::PWorldPos;

class ForestMap
{
public:
	int SizeX() { return MaxX - MinX + 1; }
	int SizeY() { return MaxY - MinY + 1; }

	Vector2Int WorldToCell(Vector2 pos);
	Vector2 CellToWorld(Vector2Int pos);
	Protocol::PCellPos* GetCellPosProtocol(Vector2Int cellPos);
	Protocol::PWorldPos* GetWorldPosProtocol(Vector2 worldPos);

	bool CanGo(Vector2Int cellPos, bool checkObjects = true);

	void EnterPlayer(Vector2Int cellPos, PlayerRef player);
	bool MovePlayer(Vector2Int prevPos, Vector2Int afterPos, PlayerRef player);
	void LeavePlayer(Vector2Int cellPos, PlayerRef player);
	PlayerRef FindPlayer(Vector2Int cellPos);

	bool FindBomb(Vector2Int cellPos);

	bool SetBomb(Vector2Int bomb);

	void DestroyBomb(Vector2Int pos, int32 range, Protocol::S_BOMBEND* pkt);
	void LoadMap(wstring pathPrefix = L"../Common/MapData");

public:
	int32 MinX;
	int32 MaxX;
	int32 MinY;
	int32 MaxY;

private:
	vector<vector<int>> _blocks;
	vector<vector<PlayerRef>> _players;
};