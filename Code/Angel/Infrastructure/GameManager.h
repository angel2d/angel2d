#pragma once

#include "../Actors/Actor.h"
#include "../Messaging/Message.h"
#include "../Physics/PhysicsUtil.h"
#include "../Infrastructure/SoundDevice.h"

// forward declarations
class b2Shape;

class GameManager : public Renderable, public CollisionListener, public MessageListener
{
public:
	GameManager(){}
	~GameManager(){}

	virtual void Render();
	virtual void Update(float dt);
	virtual void OnCollision(b2Shape* s1, b2Shape* s2, float normalImpulse, Vector2& hitLocation);
	virtual bool IsProtectedFromUnloadAll( Renderable* renderable ) {return false;} 
	virtual void ReceiveMessage(Message* message) {}
	virtual void SoundEnded(SOUND_HANDLE sound){}
};
