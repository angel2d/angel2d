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

#include "../Infrastructure/World.h"
#include "../Infrastructure/Vector3.h"
#include "../Infrastructure/VecStructs.h"

///Struct to represent an individual touch in a multi-touch system
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

/**
 * An enumeration for the type of touch data received by a TouchListener
 */
enum TouchInput
{
	TOUCH_START,
	TOUCH_END,
	TOUCH_MOVE
};

/**
 * Structure which bundles the data about individual gestures that are received
 *  and sent via messages. 
 */
struct GestureData
{
	/**
	 * The "Velocity" of the gesture (only recorded on the actual iOS hardware.)
	 */
	float Velocity;

	/**
	 * In a rotation gesture, this will be the angle in radians. For a pinch,
	 *  it will be the scale. 
	 */
	float GestureMagnitude; 
};


typedef std::vector<Touch*> TouchList;

///An abstract interface for getting mouse events
/** 
 * This is an abstract base class which provides an interface to get 
 *  notifications about what's going on with the multi-touch system. If you
 *  want to get touch data, derive a class from this one and implement the 
 *  Touch*Event member functions. 
 */
class TouchListener
{
public:
	/**
	 * Base constructor adds this object to the list of objects to get 
	 *  notified when touchey things happen. 
	 */
	TouchListener();

	/**
	 * Base destructor removes this object from the list. 
	 */
	virtual ~TouchListener();
	
	/**
	 * Called whenever an existing touch moves. 
	 * 
	 * @param movedTouch A pointer to a Touch object representing the 
	 *   specific touch that moved. 
	 */
	virtual void TouchMotionEvent(Touch* movedTouch);

	/**
	 * Called whenever a touch ends. 
	 * 
	 * @param endedTouch A pointer to a Touch object representing the 
	 *   specific touch that just ended. 
	 */	
	virtual void TouchEndEvent(Touch* endedTouch);

	/**
	 * Called whenever a new touch starts. 
	 * 
	 * @param startedTouch A pointer to a Touch object representing the 
	 *   specific touch that just started. 
	 */	
	virtual void TouchStartEvent(Touch* startedTouch);
	
	/**
	 * A static function to get access to a list of the current Touch 
	 *  objects being detected. 
	 */
	static TouchList &GetTouchList();
	
private:
	static TouchList _touchList;
};

/** 
 * Adds a TouchListener to the list of objects getting notified when 
 *  touch events happen. Don't call this function directly; let the 
 *  TouchListener constructor handle it. 
 */
void RegisterTouchSubscriber(TouchListener* actor);

/** 
 * Removes a TouchListener from the list of objects getting notified when 
 *  touch events happen. Don't call this function directly; let the 
 *  TouchListener destructor handle it.
 */
void DeregisterTouchSubscriber(TouchListener* actor);

/** 
 * Sends notifications to all listeners when Touch events happen.
 *  Don't call this function directly; the system will call it internally.
 */
void SendTouchNotifiers(Touch* changedTouch, TouchInput type);


///A class to read the data from a hardware accelerometer
/**
 * This class facilitates reading data from the hardware accelerometer on
 *  iOS devices. Note that it performs some simple averaging of values 
 *  over time -- if you want to access the data more immediately, 
 *  you can tune the defined values in AngelAppDelegate.m
 */
class Accelerometer
{
public:
	/**
	 * Used to access the singleton instance of this class.
	 * 
	 * @return The singleton
	 */
	static Accelerometer& GetInstance();
	
	/**
	 * Read the current value or the detected accelerometer values.
	 * 
	 * @return The X, Y, and Z parameters being detected. Values 
	 *   are in Gs. 
	 */
	const Vector3 GetData();
	
	/**
	 * Push a new accelerometer value into the object. No need to 
	 *  call this directly -- it's either called by the iOS framework
	 *  or the MobileSimulator class.
	 * 
	 * @param data A 3D vector representing the current acceleration
	 */
	void NewAcceleration(Vector3 data);
	
private:
	Accelerometer();
	static Accelerometer* s_Accelerometer;
	
	Vector3 _data;
};
