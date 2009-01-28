#include "../Actors/GridActor.h"

#include "../Infrastructure/Common.h"

GridActor::GridActor()
{
	//yay for magic numbers! (default parameters of the grid)
	_lineColor = Color(.76f, .83f, 1.0f);
	_axisColor = Color(1.0f, .41f, .6f);
	_interval = 1.0f;
	_minCoord = Vector2(-100.0f, -100.0f);
	_maxCoord = Vector2(100.0f, 100.0f);
}

GridActor::GridActor(Color lines, Color axis, float interval, Vector2 minCoord, Vector2 maxCoord)
{
	_lineColor = lines;
	_axisColor = axis;
	_interval = interval;
	_minCoord = minCoord;
	_maxCoord = maxCoord;
}

void GridActor::SetLineColor(Color lineCol)
{
	_lineColor = lineCol;
}

const Color GridActor::GetLineColor()
{
	return _lineColor;
}

void GridActor::SetAxisColor(Color axisCol)
{
	_axisColor = axisCol;
}

const Color GridActor::GetAxisColor()
{
	return _axisColor;
}

void GridActor::SetInterval(float interval)
{
	_interval = interval;
}

const float GridActor::GetInterval()
{
	return _interval;
}

void GridActor::SetMinCoord(Vector2 minCoord)
{
	_minCoord = minCoord;
}

const Vector2 GridActor::GetMinCoord()
{
	return _minCoord;
}

void GridActor::SetMaxCoord(Vector2 maxCoord)
{
	_maxCoord = maxCoord;
}

const Vector2 GridActor::GetMaxCoord()
{
	return _maxCoord;
}

void GridActor::Render()
{
	glColor3f(_lineColor.R, _lineColor.G, _lineColor.B);
	glBegin(GL_LINES);
	float i;
	for(i = _minCoord.X; i < _maxCoord.X; i += _interval)
	{
		glVertex2f(i, _minCoord.Y);
		glVertex2f(i, _maxCoord.Y);
	}
	for(i = _minCoord.Y; i < _maxCoord.Y; i += _interval)
	{
		glVertex2f(_minCoord.X, i);
		glVertex2f(_maxCoord.X, i);
	}

	//drawing axes
	glColor3f(_axisColor.R, _axisColor.G, _axisColor.B);
	glVertex2f(_minCoord.X, 0.0f);
	glVertex2f(_maxCoord.X, 0.0f);
	glVertex2f(0.0f, _minCoord.Y);
	glVertex2f(0.0f, _maxCoord.Y);
	glEnd();
}