#pragma once

#include "../Infrastructure/VecStructs.h"

enum MouseButtonInput
{
	MOUSE_LEFT,
	MOUSE_MIDDLE,
	MOUSE_RIGHT
};

///An abstract interface for getting mouse events
/** 
 * This is an abstract base class which provides an interface to get 
 *  notifications about what's going on with the mouse. If you want to get
 *  mouse data, derive a class from this one and implement the Mouse*Event
 *  member functions. 
 */
class MouseListener
{
public:
	/**
	 * Base constructor adds this object to the list of objects to get 
	 *  notified when mousey things happen. 
	 */
	MouseListener();
	
	/**
	 * Base destructor removes this object from the list. 
	 * 
	 * @return 
	 */
	virtual ~MouseListener();

	/**
	 * Called whenever the player moves the mouse. 
	 * 
	 * @param screenCoordinates The new coordinates of the mouse in screen
	 *   coordinates (pixels). Use the MathUtil::ScreenToWorld function if
	 *   you want GL units. 
	 */
	virtual void MouseMotionEvent(Vec2i screenCoordinates);
	
	/**
	 * Called whenever the player presses down on a mouse button. 
	 * 
	 * @param screenCoordinates The new coordinates of the mouse in screen
	 *   coordinates (pixels). Use the MathUtil::ScreenToWorld function if
	 *   you want GL units.
	 * @param button Which button was pressed. Will be one of \c MOUSE_LEFT, 
	 *   \c MOUSE_MIDDLE, or \c MOUSE_RIGHT. 
	 */
	virtual void MouseDownEvent(Vec2i screenCoordinates, MouseButtonInput button);
	
	/**
	 * Called whenever the player releases a mouse button. 
	 * 
	 * @param screenCoordinates The new coordinates of the mouse in screen
	 *   coordinates (pixels). Use the MathUtil::ScreenToWorld function if
	 *   you want GL units.
	 * @param button Which button was released. Will be one of \c MOUSE_LEFT, 
	 *   \c MOUSE_MIDDLE, or \c MOUSE_RIGHT. 
	 */
	virtual void MouseUpEvent(Vec2i screenCoordinates, MouseButtonInput button);
};


/** 
 * Adds a MouseListener to the list of objects getting notified when 
 *  mouse events happen. Don't call this function directly; let the 
 *  MouseListener constructor handle it. 
 */
void RegisterMouseSubscriber(MouseListener* actor);

/** 
 * Adds a MouseListener to the list of objects getting notified when 
 *  mouse events happen. Don't call this function directly; let the 
 *  MouseListener destructor handle it.
 */
void DeregisterMouseSubscriber(MouseListener* actor);


/** 
 * A C-based function to get called by the windowing system when the mouse
 *  moves. Because our windowing/input toolkit (GLFW) is C-based, it needs 
 *  these loose functions to operate.
 */
void MouseMotion(int x, int y);

/** 
 * A C-based function to get called by the windowing system when the mouse
 *  is clicked. Because our windowing/input toolkit (GLFW) is C-based, it 
 *  needs these loose functions to operate.
 */
void MouseButton(int button, int state);
