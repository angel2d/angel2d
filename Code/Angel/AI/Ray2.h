#pragma once

#include "../Infrastructure/Vector2.h"

struct Ray2
{
	Vector2 Position;
	Vector2 Direction;
	Ray2(const Vector2& _position, const Vector2& _direction)
		: Position(_position)
		, Direction(_direction)
	{}

	Ray2() {}

	static Ray2 CreateRayFromTo( const Vector2& vFrom, const Vector2& vTo )
	{
		return Ray2(vFrom, Vector2::Normalize( vTo - vFrom ));
	}
};

bool operator ==(const Ray2& a, const Ray2& b);
bool operator !=(const Ray2& a, const Ray2& b);

