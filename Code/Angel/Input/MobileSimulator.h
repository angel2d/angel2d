//////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2008-2014, Shane Liesegang
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

#include "../Actors/Actor.h"
#include "../Input/MouseInput.h"

///A class to somewhat simulate the setup of an iOS app on the desktop.
/** 
 * If you add this Renderable to the world, it'll pretend to be the mobile hardware,
 *  filling the same data structures that the real hardware would, meaning you can 
 *  use this to prototype a lot of iOS gameplay without having the hardware 
 *  immediately accessible. 
 * 
 * You shouldn't actually have to call any of the methods on this class. Add
 *  it to the world and then use the interfaces defined in MultiTouch.h.
 */
class MobileSimulator : public Renderable, MouseListener
{
public:
	MobileSimulator();

	virtual ~MobileSimulator();

	virtual void Update(float dt);

	virtual void MouseMotionEvent(Vec2i screenCoordinates);
	virtual void MouseDownEvent(Vec2i screenCoordinates, MouseButtonInput button);
	virtual void MouseUpEvent(Vec2i screenCoordinates, MouseButtonInput button);

private:
	Actor* _fingerGhost1;
	Actor* _fingerGhost2;

	enum MultiGestureType
	{
		ROTATE,
		PINCH,
		NONE
	};

	bool _multiGestureOngoing;
	MultiGestureType _gestureType;
	bool _mouseDown;
};
