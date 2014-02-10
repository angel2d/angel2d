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
#include "../Input/MobileSimulator.h"

#include "../Actors/Actor.h"
#include "../Input/InputManager.h"
#include "../Input/MultiTouch.h"
#include "../Messaging/Switchboard.h"

// maximum duration of touch (in seconds) to be considered a swipe
//  (too long and we're dragging)
#define SWIPE_MAX_DURATION 0.4f
// distance in pixels the touch must go to be considered a swipe
//  (too short and it might have just been a tap)
#define SWIPE_MIN_DISTANCE 50

// distance in pixels that the touches have to move before multi-touch
//  recognition starts
#define MULTI_MIN_DISTANCE 13
// angle in radians that the touches' vectors need to shift by to
//   be considered a rotation instead of a pinch
// (equivalent of 2.5 degrees)
#define MULTI_ROTATE_ANGLE 0.0436332313f

MobileSimulator::MobileSimulator()
{
	_multiGestureOngoing = false;
	_gestureType = NONE;
	_mouseDown = false;

	_fingerGhost1 = new Actor();
	_fingerGhost1->SetSize(1.5f);
	_fingerGhost1->SetDrawShape(ADS_Circle);
	_fingerGhost1->SetColor(0.8f, 0.8f, 0.8f, 0.0f);

	_fingerGhost2 = new Actor();
	_fingerGhost2->SetSize(1.5f);
	_fingerGhost2->SetDrawShape(ADS_Circle);
	_fingerGhost2->SetColor(0.8f, 0.8f, 0.8f, 0.0f);


	theWorld.Add(_fingerGhost1, 1000);
	theWorld.Add(_fingerGhost2, 1000);
}

MobileSimulator::~MobileSimulator()
{
	
}

void MobileSimulator::Update(float dt)
{
	if (theInput.IsKeyDown(ANGEL_KEY_LEFTCONTROL) || theInput.IsKeyDown(ANGEL_KEY_RIGHTCONTROL))
	{
		_fingerGhost1->SetAlpha(0.5f);
		_fingerGhost2->SetAlpha(0.5f);
	}
	else
	{
		_fingerGhost1->SetAlpha(0.0f);
		_fingerGhost2->SetAlpha(0.0f);
	}
}


void MobileSimulator::MouseMotionEvent(Vec2i screenCoordinates)
{
	Vector2 pos = MathUtil::ScreenToWorld(screenCoordinates);
	_fingerGhost1->SetPosition(pos);
	_fingerGhost2->SetPosition(-pos);

	if (_mouseDown)
	{
		//move touch(es)
		TouchList *tl = &TouchListener::GetTouchList();
		if (tl->size() > 0)
		{
			(*tl)[0]->CurrentPoint = screenCoordinates;
			if ( (*tl)[0]->MotionStartTime < 0.0f )
			{
				(*tl)[0]->MotionStartTime = theWorld.GetCurrentTimeSeconds();
			}
		}
		if (tl->size() > 1)
		{
			Vector2 negCoordsVec = MathUtil::WorldToScreen(-pos);
			Vec2i negCoords(negCoordsVec.X, negCoordsVec.Y);
			(*tl)[1]->CurrentPoint = negCoords;
			if ( (*tl)[1]->MotionStartTime < 0.0f )
			{
				(*tl)[1]->MotionStartTime = theWorld.GetCurrentTimeSeconds();
			}

			Touch* t1 = (*tl)[0];
			Touch* t2 = (*tl)[1];

			Vector2 start1(t1->StartingPoint);
			Vector2 current1(t1->CurrentPoint);
			Vector2 start2(t2->StartingPoint);
			Vector2 current2(t2->CurrentPoint);

			Vector2 initialVector = start2 - start1;
			Vector2 currentVector = current2 - current1;

			Vector2 initNorm = Vector2::Normalize(initialVector);
			Vector2 currentNorm = Vector2::Normalize(currentVector);
			float radiansRotated = acos(Vector2::Dot(initNorm, currentNorm));

			if (!_multiGestureOngoing)
			{					
				Vector2 motion = current1 - start1;

				if (motion.LengthSquared() >= (MULTI_MIN_DISTANCE * MULTI_MIN_DISTANCE) )
				{
					_multiGestureOngoing = true;
					
					// figure out if it's a rotate or a pinch
					if (radiansRotated > MULTI_ROTATE_ANGLE)
					{
						_gestureType = ROTATE;
					}
					else
					{
						_gestureType = PINCH;
					}
				}
			}

			if (_multiGestureOngoing)
			{
				GestureData gd;
				gd.Velocity = 0.0f; // don't want to store all the extra datums
									//  needed to actually calculate this

				if      (_gestureType == ROTATE)
				{
					float cross = Vector2::Cross(initNorm, currentNorm);
					if (cross > 0.0f)
					{
						radiansRotated = -radiansRotated;
					}
					gd.GestureMagnitude = radiansRotated;
					theSwitchboard.Broadcast(new TypedMessage<GestureData>("MultiTouchRotate", gd));
				}
				else if (_gestureType == PINCH)
				{
					gd.GestureMagnitude = currentVector.Length() / initialVector.Length();
					theSwitchboard.Broadcast(new TypedMessage<GestureData>("MultiTouchPinch", gd));	
				}
			}
		}
	}
}

void MobileSimulator::MouseDownEvent(Vec2i screenCoordinates, MouseButtonInput button)
{
	_mouseDown = true;

	TouchList* tl = &TouchListener::GetTouchList();

	if (theInput.IsKeyDown(ANGEL_KEY_LEFTCONTROL) || theInput.IsKeyDown(ANGEL_KEY_RIGHTCONTROL))
	{
		// add the two touches
		Touch* t = new Touch();
		t->__platformTouch = NULL;
		t->StartingPoint = screenCoordinates;
		t->CurrentPoint = t->StartingPoint;
		tl->push_back(t);
		SendTouchNotifiers(t, TOUCH_START);

		t = new Touch();
		t->__platformTouch = NULL;
		Vector2 pos2 = MathUtil::WorldToScreen(_fingerGhost2->GetPosition());
		t->StartingPoint = Vec2i(pos2.X, pos2.Y);
		t->CurrentPoint = t->StartingPoint;
		tl->push_back(t);
		SendTouchNotifiers(t, TOUCH_START);
	}
	else
	{
		// just a single touch
		Touch* t = new Touch();
		t->__platformTouch = NULL;
		t->StartingPoint = screenCoordinates;
		t->CurrentPoint = t->StartingPoint;
		tl->push_back(t);
		SendTouchNotifiers(t, TOUCH_START);
	}
}

void MobileSimulator::MouseUpEvent(Vec2i screenCoordinates, MouseButtonInput button)
{
	_multiGestureOngoing = false;
	_gestureType = NONE;
	_mouseDown = false;

	TouchList* tl = &TouchListener::GetTouchList();
	
	if (theInput.IsKeyDown(ANGEL_KEY_LEFTCONTROL) || theInput.IsKeyDown(ANGEL_KEY_RIGHTCONTROL))
	{
		TouchList::iterator it = tl->begin();
		while (it != tl->end())
		{
			SendTouchNotifiers((*it), TOUCH_END);
			delete (*it);
			it = tl->erase(it);
		}
	}
	else
	{
		// just a single touch, but we'll iterate anyway
		TouchList::iterator it = tl->begin();
		while (it != tl->end())
		{
			if ( (theWorld.GetCurrentTimeSeconds() - (*it)->MotionStartTime) < SWIPE_MAX_DURATION)
			{
				Vector2 start((*it)->StartingPoint.X, (*it)->StartingPoint.Y);
				Vector2 end((*it)->CurrentPoint.X, (*it)->CurrentPoint.Y);
				Vector2 motion = end - start;
				if (motion.LengthSquared() >= (SWIPE_MIN_DISTANCE * SWIPE_MIN_DISTANCE))
				{
					float angle = MathUtil::ToDegrees(acos(Vector2::Dot(Vector2::UnitX, Vector2::Normalize(motion))));
					if (motion.Y > 0.0f)
					{
						angle = 360.0f - angle;
					}

					if      ( (angle > 45.0f) && (angle <= 135.0f) )
					{
						// swipe up
						theSwitchboard.Broadcast(new Message("MultiTouchSwipeUp"));
					}
					else if ( (angle > 135.0f) && (angle <= 225.0f) )
					{
						// swipe left
						theSwitchboard.Broadcast(new Message("MultiTouchSwipeLeft"));
					}
					else if ( (angle > 225.0f) && (angle <= 315.0f) )
					{
						// swipe down
						theSwitchboard.Broadcast(new Message("MultiTouchSwipeDown"));
					}
					else
					{
						// swipe right
						theSwitchboard.Broadcast(new Message("MultiTouchSwipeRight"));
					}
				}
			}
			SendTouchNotifiers((*it), TOUCH_END);
			delete (*it);
			it = tl->erase(it);
		}
	}
}
