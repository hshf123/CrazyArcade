#pragma once
#include "pch.h"

struct Pos
{
	Pos(float y, float x) { this->y = y; this->x = x; }
	float x;
	float y;
};

struct Vector2Int
{
	Vector2Int(int32 x, int32 y) { this->x = x; this->y = y; }

	static Vector2Int up() { return Vector2Int(0, 1); };
	static Vector2Int down() { return Vector2Int(0, -1); };
	static Vector2Int left() { return Vector2Int(-1, 0); };
	static Vector2Int right() { return Vector2Int(1, 0); };

	Vector2Int& operator=(const Vector2Int& other)
	{
		if (this != &other)
		{
			this->x = other.x;
			this->y = other.y;
		}
		return *this;
	}

	bool operator==(const Vector2Int& other) const
 	{
		return x == other.x && y == other.y;
	}

	bool operator!=(const Vector2Int& other) const
	{
		return !(x == other.x && y == other.y);
	}

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

struct Vector2
{
	Vector2(float x, float y) { this->x = x; this->y = y; }

	static Vector2 up() { return Vector2(0.f, 1.f); };
	static Vector2 down() { return Vector2(0, -1.f); };
	static Vector2 left() { return Vector2(-1.f, 0.f); };
	static Vector2 right() { return Vector2(1.f, 0.f); };

	Vector2& operator=(const Vector2& other)
	{
		if (this != &other)
		{
			this->x = other.x;
			this->y = other.y;
		}
		return *this;
	}

	Vector2 operator*(const float& value) const
	{
		return Vector2(x * value, y * value);
	}

	Vector2 operator+(const Vector2& other) const
	{
		return Vector2(x + other.x, y + other.y);
	}

	Vector2 operator+=(const Vector2& other) const
	{
		return Vector2(x + other.x, y + other.y);
	}

	Vector2 operator-(const Vector2& other) const
	{
		return Vector2(x - other.x, y - other.y);
	}

	float magnitude() { return static_cast<float>(sqrt(sqrMagnitude())); };
	int32 sqrMagnitude() { return (x * x + y * y); };
	int32 cellDistFromZero() { return abs(x) + abs(y); };

	float x;
	float y;
};