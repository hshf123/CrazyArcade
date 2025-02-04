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

	Protocol::PCellPos* GetCellPosProtocol(Vector2Int cellPos);

	bool CanGo(Vector2Int cellPos);
	bool ApplyMove(PlayerRef player, Protocol::C_MOVE& pkt);
	void ApplyLeave(PlayerRef player);
	Vector2Int FindPlayer(PlayerRef player);
	Vector<PlayerRef> FindPlayer(Vector2Int cellPos, PlayerRef exceptPlayer = nullptr);

	BombRef FindBomb(Vector2Int cellPos);
	bool SetBomb(Vector2Int pos, PlayerRef ownerPlayer);
	void DestroyBomb(Vector2Int pos, int32 range, Protocol::S_BOMBEND& pkt);
	bool CheckWaterCourse(Vector2Int pos);
	void BombResult(Protocol::S_BOMBEND& pkt);
	void SpawnItem(Vector2Int pos);

	void LoadMap(wstring pathPrefix = L"../Common/MapData");

public:
	int32 MinX;
	int32 MaxX;
	int32 MinY;
	int32 MaxY;
	int32 PlayerCount;
	RoomRef OwnerRoom;

private:
	Vector<Vector<int32>> _blocks;
	HashMap<PlayerRef, Vector2Int> _players;
	HashMap<Vector2Int, Protocol::PItemType> _spawnItems;
	HashMap<Vector2Int, BombRef> _bombs;

	HashSet<Vector2Int> _destroyObjects;
	HashSet<Vector2Int> _destroyItems;
	Set<PlayerRef> _trapPlayers;
};