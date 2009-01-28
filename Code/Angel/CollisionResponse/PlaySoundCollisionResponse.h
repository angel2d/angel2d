
#pragma once

#include "../CollisionResponse/CollisionResponse.h"
#include "../Infrastructure/SoundDevice.h"

class PlaySoundCollisionResponse : public CollisionResponse
{
public:
	DECLARE_COLLISIONRESPONSE(PlaySoundCollisionResponse)

	virtual void Execute();
protected:
	SAMPLE_HANDLE	_sample;
	float			_volume;
};