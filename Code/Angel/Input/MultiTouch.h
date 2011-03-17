//////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2008-2011, Shane Liesegang
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

#include "../Infrastructure/World.h"
#include "../Infrastructure/Vector3.h"
#include "../Infrastructure/VecStructs.h"

struct Touch
{
	Vec2i StartingPoint;
	Vec2i CurrentPoint;
	float StartTime;
	float MotionStartTime;

	void* __platformTouch;

	Touch()
	{
		StartTime = theWorld.GetCurrentTimeSeconds();
		MotionStartTime = -1.0f;
	}
};

enum TouchInput
{
	TOUCH_START,
	TOUCH_END,
	TOUCH_MOVE
};

struct GestureData
{
	float Velocity;
	float GestureMagnitude; // For rotation, this will be the angle in radians, for pinch it will be the scale
};

typedef std::vector<Touch*> TouchList;


class TouchListener
{
public:
	TouchListener();
	virtual ~TouchListener();
	
	virtual void TouchMotionEvent(Touch* movedTouch);
	virtual void TouchEndEvent(Touch* endedTouch);
	virtual void TouchStartEvent(Touch* startedTouch);
	
	static TouchList &GetTouchList();
	
private:
	static TouchList _touchList;
};



void RegisterTouchSubscriber(TouchListener* actor);
void DeregisterTouchSubscriber(TouchListener* actor);

void SendTouchNotifiers(Touch* changedTouch, TouchInput type);



class Accelerometer
{
public:
	static Accelerometer& GetInstance();
	
	const Vector3 GetData();
	
	void NewAcceleration(Vector3 data);
	
private:
	Accelerometer();
	static Accelerometer* s_Accelerometer;
	
	Vector3 _data;
};
