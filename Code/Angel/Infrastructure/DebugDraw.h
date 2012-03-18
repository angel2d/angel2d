#include "Vector2.h"

/* abstract */ class DebugDrawBase
{
protected:
	friend class World;
	virtual ~DebugDrawBase() {}
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
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(2, GL_FLOAT, 0, _points);
		glDrawArrays(GL_LINES, 0, 2);
	}

	float _points[4];
};

typedef std::vector< DebugDrawBase* >::iterator		DebugDrawIterator;

