#pragma once

#include "../Actors/Actor.h"

struct Particle
{
	Vector2 _pos;
	Vector2 _vel;
	float _age;
	float _lifetime;
	Color _color;
	float _scale;
};

class ParticleActor : public Actor
{
public:
	friend class ParticleActorFactoryDelegate;

	ParticleActor()
	{
		_maxParticlesAlive = 0;
		_particles = 0;

		_particlesPerSecond = 20.0f;

		_generationResidue = 0.0f;
		_numParticlesAlive = 0;

		_systemLifetime = 0.0f;
		_particleLifetime = 2.0f;

		_spreadRadians = 0.0f;

		_startAlpha = 1.0f;
		_endAlpha = 1.0f;

		_endColor = Color(1.0f, 1.0f, 1.0f);

		_minSpeed = 2.0f;
		_maxSpeed = 4.0f;

		_endScale = 1.0f;

		_gravity = Vector2(0.0f, -4.0f);
	}

	~ParticleActor()
	{
		delete [] _particles;
	}

	virtual void Update(float dt);
	virtual void Render();

	void SetParticlesPerSecond(float pps);
	void SetSystemLifetime(float lifetime);
	void SetParticleLifetime(float lifetime);
	void SetSpread(float radians);
	void SetEndAlpha(float alpha);
	void SetEndScale(float scale);
	void SetEndColor(Color& color);
	void SetSpeedRange(float minSpeed, float maxSpeed);
	void SetGravity(Vector2& gravity);
	void SetMaxParticles(int maxParticles);

protected:
	Particle* _particles;
	int		_maxParticlesAlive;
	int		_numParticlesAlive;

	float	_particlesPerSecond;
	int		_maxParticlesToGenerate;
	float	_generationResidue;

	float	_systemLifetime;		// How long the system will live.   (seconds) Good for one shot effects.
	float	_particleLifetime;	// How long the particles will live. (seconds)

	float	_spreadRadians;		// How much the particles can deviate in direction from the system.

	float	_startAlpha; // Particles lerp from _startAlpha to _endAlpha over their lifetime.
	float	_endAlpha;

	Color	_endColor; // We use the Actor _color as the start color.

	float	_minSpeed; // At emission, we choose a random speed between minSpeed and maxSpeed.
	float	_maxSpeed;

	float	_endScale; // Respects the starting aspect ratio of the sprite.

	Vector2 _gravity;
};

class ParticleActorFactoryDelegate  : public ActorFactoryDelegate
{
public:
	ParticleActorFactoryDelegate::ParticleActorFactoryDelegate() {}
	virtual void RegisterOriginalConsoleCommands();
	virtual Actor* CreateInstance(); 
	virtual void FinishInstance(Actor* pInstance);

	virtual void SetEmissionRate(float rate);
	virtual void SetParticleLifetime(float lifetime);
	virtual void SetSystemLifetime(float lifetime);
	virtual void SetSpread(float spread);
	virtual void SetEndScale(float endScale);
	virtual void SetEndColor(float r, float g, float b);
	virtual void SetEndAlpha(float endAlpha);
	virtual void SetMinSpeed(float minSpeed);
	virtual void SetMaxSpeed(float maxSpeed);
	virtual void SetMaxParticles(int maxParticles);
	virtual void SetGravity(Vector2 gravity);

	friend class ParticleActorFactory;

private:
	float	_emissionRate;  // Particles per second.
	float	_systemLifetime;
	float	_particleLifetime;
	float	_spreadRadians;
	float	_endScale;
	Color	_end_color;
	float	_endAlpha;
	float	_minSpeed;
	float	_maxSpeed;
	int	_maxParticles;
	Vector2 _gravity;
};
