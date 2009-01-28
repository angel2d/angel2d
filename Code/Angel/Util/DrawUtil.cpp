#include "../Util/DrawUtil.h"

#include "../Infrastructure/Common.h"

void DrawCross( const Vector2& point, float size )
{
	size *= 0.5f;
	Vector2 north(point + Vector2::UnitY * size );
	Vector2 south(point - Vector2::UnitY * size );
	Vector2 east(point + Vector2::UnitX * size );
	Vector2 west(point - Vector2::UnitX * size );

	glBegin(GL_LINES);

	glVertex2f(north.X, north.Y);
	glVertex2f(south.X, south.Y);
	glVertex2f(east.X, east.Y);
	glVertex2f(west.X, west.Y);

	glEnd();
}

void DrawPoint( const Vector2& point, float size )
{
	size *= 0.5f;
	Vector2 north(point + Vector2::UnitY * size );
	Vector2 south(point - Vector2::UnitY * size );
	Vector2 east(point + Vector2::UnitX * size );
	Vector2 west(point - Vector2::UnitX * size );

	glBegin(GL_LINES);

	glVertex2f(north.X, north.Y);
	glVertex2f(east.X, east.Y);

	glVertex2f(east.X, east.Y);
	glVertex2f(south.X, south.Y);

	glVertex2f(south.X, south.Y);
	glVertex2f(west.X, west.Y);

	glVertex2f(west.X, west.Y);
	glVertex2f(north.X, north.Y);

	glEnd();
}

void DrawLine( const Vector2& vFrom, const Vector2& vTo )
{
	glBegin(GL_LINES);

	glVertex2f(vFrom.X, vFrom.Y);
	glVertex2f(vTo.X, vTo.Y);

	glEnd();
}

