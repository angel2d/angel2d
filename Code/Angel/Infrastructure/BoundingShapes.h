#pragma once

#include "../Infrastructure/Vector2.h"

struct Ray2;

enum ContainmentType
{
	Disjoint,
	Within,
	Intersects
};

struct BoundingBox
{
	Vector2 Min;
	Vector2 Max;

	BoundingBox(const Vector2& min, const Vector2& max);
	BoundingBox() {}

	Vector2 Centroid();

	static BoundingBox CreateMerged(const BoundingBox& original, const BoundingBox& additional);

	void GetCorners(Vector2 corners[]);
	static BoundingBox CreateFromPoints(Vector2 points[], int count);

	bool Intersects(const BoundingBox& box);
	bool Intersects(const Ray2& ray, float& distanceAlongRay);

	ContainmentType Contains(const BoundingBox& box);
	bool Contains(const Vector2& point);

	void RenderOutline();
	void RenderBox();
};


bool operator ==(const BoundingBox& a, const BoundingBox& b);
bool operator !=(const BoundingBox& a, const BoundingBox& b);

