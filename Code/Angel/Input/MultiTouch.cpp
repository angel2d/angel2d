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

#include "stdafx.h"
#include "../Input/MultiTouch.h"

#include "../Infrastructure/Common.h"

#if !ANGEL_MOBILE
	#include "../Input/Controller.h"
#endif

std::set<TouchListener*> _touchSubscribers;

std::vector<Touch*> TouchListener::_touchList;

TouchListener::TouchListener()
{
	RegisterTouchSubscriber(this);
}

TouchListener::~TouchListener()
{
	DeregisterTouchSubscriber(this);
}


void TouchListener::TouchMotionEvent(Touch* movedTouch) {}
void TouchListener::TouchEndEvent(Touch* endedTouch) {}
void TouchListener::TouchStartEvent(Touch* startedTouch) {}

TouchList &TouchListener::GetTouchList()
{
	return _touchList;
}

void RegisterTouchSubscriber(TouchListener* actor)
{
	_touchSubscribers.insert(actor);
}

void DeregisterTouchSubscriber(TouchListener *actor)
{
	std::set<TouchListener*>::iterator it = _touchSubscribers.find(actor);
	if (it != _touchSubscribers.end())
	{
		_touchSubscribers.erase(it);
	}
}

void SendTouchNotifiers(Touch* changedTouch, TouchInput type)
{
	std::set<TouchListener*>::iterator it = _touchSubscribers.begin();
	while (it != _touchSubscribers.end())
	{
		if (type == TOUCH_START)
		{
			(*it)->TouchStartEvent(changedTouch);
		}
		else if (type == TOUCH_MOVE)
		{
			(*it)->TouchMotionEvent(changedTouch);
		}
		else if (type == TOUCH_END)
		{
			(*it)->TouchEndEvent(changedTouch);
		}
		it++;
	}
}



Accelerometer* Accelerometer::s_Accelerometer = NULL;

Accelerometer::Accelerometer()
{
	_data = Vector3();
}

Accelerometer& Accelerometer::GetInstance()
{
	if (s_Accelerometer == NULL)
	{
		s_Accelerometer = new Accelerometer();
	}
	return *s_Accelerometer;
}

const Vector3 Accelerometer::GetData()
{
	#if !ANGEL_MOBILE
		return _data;
	#else
		if (theController.IsConnected())
		{
			Vector2 thumb = theController.GetLeftThumbVec2();
			Vector2 thumb2 = theController.GetRightThumbVec2();
			return Vector3(thumb.X, thumb.Y, thumb2.Y);
		}
		else
		{
			return Vector3();
		}
	#endif
}

void Accelerometer::NewAcceleration(Vector3 data)
{
	_data = data;
}

