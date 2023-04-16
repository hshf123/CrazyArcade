#include "pch.h"
#include "MapManager.h"
#include "GameObject.h"

bool MapManager::CanGo(Vector2Int cellPos, bool checkObjects /*= true*/)
{
	if (cellPos.x < MinX || cellPos.x > MaxX)
		return false;
	if (cellPos.y < MinY || cellPos.y > MaxY)
		return false;

	int x = cellPos.x - MinX;
	int y = MaxY - cellPos.y;
	return !_collision[y][x] && (!checkObjects || _objects[y][x] == nullptr);
}

GameObjectRef MapManager::Find(Vector2Int cellPos)
{
	if (cellPos.x < MinX || cellPos.x > MaxX)
		return nullptr;
	if (cellPos.y < MinY || cellPos.y > MaxY)
		return nullptr;

	int x = cellPos.x - MinX;
	int y = MaxY - cellPos.y;
	return _objects[y][x];
}

bool MapManager::ApplyLeave(GameObject gameObject)
{
	/*PositionInfo posInfo = gameObject.PosInfo;
	if (posInfo.PosX < MinX || posInfo.PosX > MaxX)
		return false;
	if (posInfo.PosY < MinY || posInfo.PosY > MaxY)
		return false;

	{
		int x = posInfo.PosX - MinX;
		int y = MaxY - posInfo.PosY;
		if (_objects[y, x] == gameObject)
			_objects[y, x] = null;
	}*/

	return true;
}

bool MapManager::ApplyMove(GameObject gameObject, Vector2Int dest)
{
	//ApplyLeave(gameObject);

	//PositionInfo posInfo = gameObject.PosInfo;
	//if (CanGo(dest, true) == false)
	//	return false;

	//{
	//	int x = dest.x - MinX;
	//	int y = MaxY - dest.y;
	//	_objects[y, x] = gameObject;
	//}

	//// 실제 좌표 이동
	//posInfo.set_allocated_cellpos(new Protocol::PCellPos(dest.x, dest.y));
	return true;
}

void MapManager::LoadMap(int32 mapId, string pathPrefix /*= "../../../../../Common/MapData"*/)
{
	/*string mapName = "Map_" + mapId.ToString("000");

	Collision 관련 파일
	string text = File.ReadAllText($"{pathPrefix}/{mapName}.txt");
	StringReader reader = new StringReader(text);

	MinX = int.Parse(reader.ReadLine());
	MaxX = int.Parse(reader.ReadLine());
	MinY = int.Parse(reader.ReadLine());
	MaxY = int.Parse(reader.ReadLine());

	int xCount = MaxX - MinX + 1;
	int yCount = MaxY - MinY + 1;
	_collision = new vector<vector<bool>>(yCount);
	_collision = new vector<vector<bool>>(yCount, new vector<bool>(xCount));
	_objects = new vector<vector<GameObjectRef>>(yCount, new vector<GameObjectRef>(xCount));

	for (int y = 0; y < yCount; y++)
	{
		string line = reader.ReadLine();
		for (int x = 0; x < xCount; x++)
		{
			_collision[y][x] = (line[x] == '1' ? true : false);
		}
	}*/
}

vector<Vector2Int> MapManager::CalcCellPathFromParent(vector<vector<Pos>> parent, Pos dest)
{
	vector<Vector2Int> cells;

	int y = dest.Y;
	int x = dest.X;
	while (parent[y][x].Y != y || parent[y][x].X != x)
	{
		cells.push_back(Pos2Cell(Pos(y, x)));
		Pos pos = parent[y][x];
		y = pos.Y;
		x = pos.X;
	}
	cells.push_back(Pos2Cell(Pos(y, x)));
	::reverse(cells.begin(), cells.end());

	return cells;
}

Pos MapManager::Cell2Pos(Vector2Int cell)
{
	// CellPos -> ArrayPos
	return Pos(MaxY - cell.y, cell.x - MinX);
}

Vector2Int MapManager::Pos2Cell(Pos pos)
{
	// ArrayPos -> CellPos
	return Vector2Int(pos.X + MinX, MaxY - pos.Y);
}
