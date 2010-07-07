%module angel
%{
#include "../../Actors/ParticleActor.h"
%}

class ParticleActor : public Actor
{
public:
	ParticleActor();
	~ParticleActor();
	
	void SetParticlesPerSecond(float pps);
	void SetSystemLifetime(float lifetime);
	void SetParticleLifetime(float lifetime);
	void SetSpread(float radians);
	//void SetEndAlpha(float alpha);
	void SetEndScale(float scale);
	void SetEndColor(Color color);
	void SetSpeedRange(float minSpeed, float maxSpeed);
	void SetMinSpeed(float minSpeed);
	void SetMaxSpeed(float maxSpeed);
	void SetGravity(Vector2 gravity);
	void SetMaxParticles(int maxParticles);
};
