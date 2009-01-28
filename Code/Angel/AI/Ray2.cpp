#include "../AI/Ray2.h"

bool operator ==(const Ray2& a, const Ray2& b)
{
	return a.Direction == b.Direction && a.Position == b.Position;
}

bool operator !=(const Ray2& a, const Ray2& b)
{
	return a.Direction != b.Direction || a.Position != b.Position;
}

