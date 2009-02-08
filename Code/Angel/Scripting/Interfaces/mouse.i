%module angel
%{
#include "../../Input/MouseInput.h"
%}

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
