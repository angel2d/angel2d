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

#include "../Util/MathUtil.h"

///Simplifies lerping Actor properties across a timeframe
/** 
 * This is a helper template class that manages Actor properties during 
 *  lerp transitions. The following functions show how they are setup, and
 *  the Actor::Update function shows how to update and get the next values. 
 * 
 * @see Actor::MoveTo
 * @see Actor::RotateTo
 * @see Actor::ChangeColorTo
 * @see Actor::ChangeSizeTo
 * 
 * You can use Intervals for ints, floats, and any class that has defined 
 *  subtraction and division (by a float) operators that return members of 
 *  that same class. Our Color, Vector2, and Vector3 classes are all able
 *  to be used in Intervals. 
 */
template<class T>
class Interval
{
public:
	
	/**
	 * Setting up the interval requires a starting value, a target ending state,
	 *  and how long it should take to get there. 
	 * 
	 * @param start The starting value
	 * @param end The ending value
	 * @param duration Length of the transition in seconds
	 * @param smooth Whether to use a smooth interpolation with ease-in and ease-out
	 *    instead of a simple linear interpolation.
	 */
	Interval(T start, T end, float duration, bool smooth=false) :
		_start(start),
		_end(end),
		_current(start),
		_duration(duration),
		_timer(0.0f),
		_shouldStep(true),
		_smoothStep(smooth)
	{
	}
	
	/**
	 * The default constructor just sets up an Interval that does nothing. It's
	 *  here because some compilers want it. 
	 */
	Interval()
	{
		_shouldStep = false;
	}
	
	
	/**
	 * The step function processes the appropriate change and shuts the interval
	 *  down if it's finished. 
	 * 
	 * @param dt How much time has elapsed since the last Step (so how much
	 *   the Interval should be incremented)
	 * @return The current value of the Interval after the Step has been completed. 
	 */
	T Step(float dt)
	{
		if (!_shouldStep)
		{
			return _current;
		}

		_timer += dt;

		if (_timer >= _duration)
		{
			_current = _end;
			_shouldStep = false;
		}
		else
		{
			float stepRatio = _timer / _duration;
			if (_smoothStep)
			{
				//smooth step
				_current = MathUtil::SmoothStep(_start, _end, stepRatio);
			}
			else
			{
				//simple lerp
				_current = MathUtil::Lerp(_start, _end, stepRatio);
			}
		}

		return _current;
	}
	
	/**
	 * Get the current value without Stepping the Interval
	 * 
	 * @return The current value
	 */
	float GetCurrent()
	{
		return _current;
	}
	
	/**
	 * Whether or not the Interval still has changes to process. If this
	 *  returns false, the Interval is done and you can discard it. 
	 * 
	 * @return 
	 */
	bool ShouldStep()
	{
		return _shouldStep;
	}
	
private:
	T _start;
	T _end;
	T _current;
	
	float _duration;
	float _timer;
	
	bool _shouldStep;
	bool _smoothStep;
};
