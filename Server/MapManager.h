#pragma once

using PositionInfo = Protocol::PPositionInfo;
using CellPos = Protocol::PCellPos;
using WorldPos = Protocol::PWorldPos;
using GameObjectRef = shared_ptr<class GameObject>;

struct Pos
{
	Pos(float y, float x) { Y = y; X = x; }
	float Y;
	float X;
};

struct Vector2Int
{
	Vector2Int(int32 x, int32 y) { x = x; y = y; }

	static Vector2Int up() { return Vector2Int(0, 1); };
	static Vector2Int down() { return Vector2Int(0, -1); };
	static Vector2Int left() { return Vector2Int(-1, 0); };
	static Vector2Int right() { return Vector2Int(1, 0); };

	Vector2Int operator+(const Vector2Int& other) const
	{
		return Vector2Int(x + other.x, y + other.y);
	}

	Vector2Int operator-(const Vector2Int& other) const
	{
		return Vector2Int(x - other.x, y - other.y);
	}

	float magnitude() { return static_cast<float>(sqrt(sqrMagnitude())); };
	int32 sqrMagnitude() { return (x * x + y * y); };
	int32 cellDistFromZero() { return abs(x) + abs(y); };

	int32 x;
	int32 y;
};

class MapManager
{
public:
	int32 MinX;
	int32 MaxX;
	int32 MinY;
	int32 MaxY;

	int SizeX() { return MaxX - MinX + 1; }
	int SizeY() { return MaxY - MinY + 1; }

	vector<vector<bool>> _collision;
	vector<vector<GameObjectRef>> _objects;

	bool CanGo(Vector2Int cellPos, bool checkObjects = true);

	GameObjectRef Find(Vector2Int cellPos);

	bool ApplyLeave(GameObject gameObject);

	bool ApplyMove(GameObject gameObject, Vector2Int dest);

	void LoadMap(int32 mapId, string pathPrefix = "../../../../../Common/MapData");

	vector<Vector2Int> CalcCellPathFromParent(vector<vector<Pos>> parent, Pos dest);

	Pos Cell2Pos(Vector2Int cell);

	Vector2Int Pos2Cell(Pos pos);
};