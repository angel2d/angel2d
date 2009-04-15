#include "Vector2.h"

/* abstract */ class DebugDrawBase
{
protected:
	friend class World;
	virtual void Draw() = 0;

	void SetupDraw()
	{
		glColor4f( _color.R, _color.G, _color.B, _color.A );
	}

	float _timeRemaining;
	bool _bPermanent;
	Color _color;
};

class DebugLine : public DebugDrawBase
{
protected:
	friend class World;

	virtual void Draw()
	{
		glBegin(GL_LINES);
			glVertex2f( _start.X, _start.Y );
			glVertex2f( _end.X, _end.Y );
		glEnd();
	}

	Vector2 _start;
	Vector2 _end;
};

typedef std::vector< DebugDrawBase* >::iterator		DebugDrawIterator;

