#pragma once

#include "../Infrastructure/VecStructs.h"

enum MouseButtonInput
{
	MOUSE_LEFT,
	MOUSE_MIDDLE,
	MOUSE_RIGHT
};

class MouseListener
{
public:
	MouseListener();
	virtual ~MouseListener();

	virtual void MouseMotionEvent(Vec2i screenCoordinates);
	virtual void MouseDownEvent(Vec2i screenCoordinates, MouseButtonInput button);
	virtual void MouseUpEvent(Vec2i screenCoordinates, MouseButtonInput button);
};

void RegisterMouseSubscriber(MouseListener* actor);
void DeregisterMouseSubscriber(MouseListener* actor);

void MouseMotion(int x, int y);
void MouseButton(int button, int state);
