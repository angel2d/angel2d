#pragma once

template<class T>
class Interval
{
public:
	Interval(T start, T end, float duration) :
		_start(start),
		_end(end),
		_current(start),
		_duration(duration),
		_timer(0.0f)
	{
		_shouldStep = true;
	}
	
	Interval()
	{
		_shouldStep = false;
	}
	
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
			//simple lerp
			float stepRatio = dt / _duration;
			_current = _current + ((_end - _start) * stepRatio);
		}

		return _current;
	}
	
	float GetCurrent()
	{
		return _current;
	}
	
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
};
