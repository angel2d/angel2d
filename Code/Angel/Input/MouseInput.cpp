#include "../Input/MouseInput.h"

#include "../Infrastructure/Common.h"

std::set<MouseListener*> _mouseSubscribers;
Vec2i _mouseLocation;

MouseListener::MouseListener()
{
	RegisterMouseSubscriber(this);
}

MouseListener::~MouseListener()
{
	DeregisterMouseSubscriber(this);
}


void MouseListener::MouseDownEvent(Vec2i /*screenCoordinates*/, MouseButtonInput /*button*/) {}
void MouseListener::MouseUpEvent(Vec2i /*screenCoordinates*/, MouseButtonInput /*button*/) {}
void MouseListener::MouseMotionEvent(Vec2i /*screenCoordinates*/) {}

void RegisterMouseSubscriber(MouseListener* actor)
{
	_mouseSubscribers.insert(actor);
}

void DeregisterMouseSubscriber(MouseListener *actor)
{
	std::set<MouseListener*>::iterator it = _mouseSubscribers.find(actor);
	if (it != _mouseSubscribers.end())
	{
		_mouseSubscribers.erase(it);
	}
}

void MouseMotion(int x, int y)
{
	_mouseLocation.X = x;
	_mouseLocation.Y = y;
	std::set<MouseListener*>::iterator it = _mouseSubscribers.begin();
	while (it != _mouseSubscribers.end())
	{
		(*it)->MouseMotionEvent(Vec2i(x, y));
		it++;
	}
}

void MouseButton(int button, int state)
{
	MouseButtonInput mouseButton;
	if (button == GLFW_MOUSE_BUTTON_RIGHT)
	{
		mouseButton = MOUSE_RIGHT;
	}
	else if (button == GLFW_MOUSE_BUTTON_MIDDLE)
	{
		mouseButton = MOUSE_MIDDLE;
	}
	else
	{
		mouseButton = MOUSE_LEFT;
	}

	std::set<MouseListener*>::iterator it = _mouseSubscribers.begin();
	while (it != _mouseSubscribers.end())
	{
		if (state == GLFW_PRESS)
		{
			(*it)->MouseDownEvent(_mouseLocation, mouseButton);
		}
		else
		{
			(*it)->MouseUpEvent(_mouseLocation, mouseButton);
		}
		it++;
	}
}
