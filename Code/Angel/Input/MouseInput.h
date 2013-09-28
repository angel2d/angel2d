//////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2008-2013, Shane Liesegang
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions are met:
// 
//     * Redistributions of source code must retain the above copyright 
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright 
//       notice, this list of conditions and the following disclaimer in the 
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of the copyright holder nor the names of any 
//       contributors may be used to endorse or promote products derived from 
//       this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
// POSSIBILITY OF SUCH DAMAGE.
//////////////////////////////////////////////////////////////////////////////

#pragma once

#include "../Infrastructure/VecStructs.h"
#include "../Infrastructure/Vector2.h"

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

	/**
	 * Called whenever the player moves the scroll wheel on the mouse.
	 * 
	 * @param scrollOffset The change in position of the scroll wheel. Note that
	 *   if it's an actual wheel, the X component of the vector will always be
	 *   0; the two-dimensional vector also takes into account trackpad scrolling.
	 */
	virtual void MouseWheelEvent(const Vector2& scrollOffset);
};


/** 
 * Adds a MouseListener to the list of objects getting notified when 
 *  mouse events happen. Don't call this function directly; let the 
 *  MouseListener constructor handle it. 
 */
void RegisterMouseSubscriber(MouseListener* actor);

/** 
 * Removes a MouseListener from the list of objects getting notified when 
 *  mouse events happen. Don't call this function directly; let the 
 *  MouseListener destructor handle it.
 */
void DeregisterMouseSubscriber(MouseListener* actor);


/** 
 * A C-based function to get called by the windowing system when the mouse
 *  moves. Because our windowing/input toolkit (GLFW) is C-based, it needs 
 *  these loose functions to operate.
 */
void MouseMotion(GLFWwindow* window, double x, double y);

/** 
 * A C-based function to get called by the windowing system when the mouse
 *  is clicked. Because our windowing/input toolkit (GLFW) is C-based, it 
 *  needs these loose functions to operate.
 */
void MouseButton(GLFWwindow* window, int button, int state, int mods);

/** 
 * A C-based function to get called by the windowing system when the
 *  mouse-wheel moves. Because our windowing/input toolkit (GLFW) is 
 *  C-based, it needs these loose functions to operate.
 */
void MouseWheel(GLFWwindow* window, double x, double y);
