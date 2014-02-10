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
#include "../Actors/ParticleActor.h"

#include "../Util/MathUtil.h"

ParticleActor::ParticleActor()
{
	_maxParticlesAlive = 0;
	_particles = 0;

	_particlesPerSecond = 20.0f;

	_generationResidue = 0.0f;
	_numParticlesAlive = 0;

	_systemLifetime = 0.0f;
	_particleLifetime = 2.0f;

	_spreadRadians = 0.0f;

	_endColor = Color(1.0f, 1.0f, 1.0f);

	_minSpeed = 2.0f;
	_maxSpeed = 4.0f;

	_endScale = 1.0f;

	_gravity = Vector2(0.0f, -4.0f);
	_attractor = Vector2(0.0f, 0.0f);
	_attractorStrength = 0.0f;
}

ParticleActor::~ParticleActor()
{
	delete [] _particles;
}

void ParticleActor::Update(float dt)
{
	Actor::Update(dt);

	if (_maxParticlesAlive == 0)
		return;

	//
	// Update existing particles.
	//
	_numParticlesAlive = 0;
	for (int i=0; i<_maxParticlesAlive; ++i)
	{
		Particle& currentParticle = _particles[i];

		if (currentParticle._age < 0.0f)
			continue;

		if (currentParticle._age < currentParticle._lifetime)
		{
			currentParticle._age += dt;

			if (currentParticle._age < currentParticle._lifetime)
			{
				// Where are we in our lifespan? (0..1)
				float lifePercent = currentParticle._age / currentParticle._lifetime;

				// Determine current position based on last known position, velocity and
				// current time delta.
				currentParticle._pos = currentParticle._pos + currentParticle._vel * dt;

				// Update our current velocity, which will be used next update.
				currentParticle._vel = currentParticle._vel + _gravity * dt;
				if (!MathUtil::FuzzyEquals(_attractorStrength, 0.0f))
				{
					Vector2 attractorShift = _attractor - currentParticle._pos;
					attractorShift.Normalize();
					attractorShift *= _attractorStrength;
					currentParticle._vel += attractorShift * dt;
				}

				currentParticle._color = MathUtil::Lerp(_color, _endColor, lifePercent);

				currentParticle._scale = MathUtil::Lerp(1.0f, _endScale, lifePercent);
				
				++_numParticlesAlive;
			}
			else 
			{
				currentParticle._age = -1.0f;
				
			}
		}
	}

	// Systems with 0.0f lifetime live forever.
	if (_systemLifetime > 0.0f)
	{
		_systemLifetime -= dt;
		if (_systemLifetime <= 0.f)
			_systemLifetime = -1.f;
	}

	// We're dead, but we're waiting for our particle to finish.
	if (_systemLifetime < 0.0f)
	{
		if (_numParticlesAlive == 0)
		{
			Destroy();
		}

		return;
	}

	//
	// Create new particles.
	//

	// Add in any residual time from last emission.
	float particlesToGenerate = _particlesPerSecond * dt + _generationResidue;
	int numParticlesToGenerate = int(floorf(particlesToGenerate));
	_generationResidue = particlesToGenerate - float(numParticlesToGenerate);
	
	if (numParticlesToGenerate > 0)
	{		
		float rot = MathUtil::ToRadians(GetRotation());
		float particleRot;

		int particlesGenerated = 0;
		for (int i=0; i<_maxParticlesAlive; ++i)
		{
			Particle& currentParticle = _particles[i];

			if (currentParticle._age < 0.0f)
			{
				currentParticle._age = 0.0f;
				currentParticle._lifetime = _particleLifetime;
				currentParticle._pos = _position;
				currentParticle._scale = 1.0f;
				currentParticle._color = _color;
				
				particleRot = MathUtil::RandomFloatWithError(rot, _spreadRadians);
				float speed = MathUtil::RandomFloatInRange(_minSpeed, _maxSpeed); 
				currentParticle._vel = Vector2(speed*cos(particleRot), speed*sin(particleRot));

				++particlesGenerated;

				// If we've generated enough, break out.
				if (particlesGenerated == numParticlesToGenerate)
					break;
			}
		}
	}
}

void ParticleActor::Render()
{
	if (!_particles)
		return;

	int textureReference = _spriteTextureReferences[_spriteCurrentFrame];
	if (textureReference >= 0)
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, textureReference);
	}

	// Render all of our particles.
	for (int i=0; i<_maxParticlesAlive; ++i)
	{
		Particle& currentParticle = _particles[i];

		if (currentParticle._age < 0.0f)
			continue;

		glPushMatrix();

		glTranslatef(currentParticle._pos.X, currentParticle._pos.Y, 0.0f);
		glRotatef(_rotation, 0, 0, 1);
		glScalef(_size.X * currentParticle._scale, _size.Y * currentParticle._scale, 1.0f);

		glColor4f(	currentParticle._color.R, 
					currentParticle._color.G, 
					currentParticle._color.B, 
					currentParticle._color.A);
		
		const static float vertices[] = {
			-0.5f,  0.5f,
			-0.5f, -0.5f,
			 0.5f,  0.5f,
			 0.5f, -0.5f,
		};
		const static float texCoords[] = {
			0.0f, 1.0f,
			0.0f, 0.0f,
			1.0f, 1.0f,
			1.0f, 0.0f,
		};
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glVertexPointer(2, GL_FLOAT, 0, vertices);
		glTexCoordPointer(2, GL_FLOAT, 0, texCoords);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		glPopMatrix();
	}

	if (textureReference >= 0)
	{
		glDisable(GL_TEXTURE_2D);
	}
}

void ParticleActor::SetParticlesPerSecond(float pps)
{
	if (pps < 0.0f)
	{
		pps = 0.0f;
	}
	_particlesPerSecond = pps;
}

void ParticleActor::SetSystemLifetime(float lifetime)
{
	if (lifetime < 0.0f)
	{
		lifetime = 0.0f;
	}
	_systemLifetime = lifetime;
}

void ParticleActor::SetParticleLifetime(float lifetime)
{
	if (lifetime < 0.0f)
	{
		lifetime = 0.0f;
	}
	_particleLifetime = lifetime;
}

void ParticleActor::SetSpread(float radians)
{
	_spreadRadians = radians;
}

void ParticleActor::SetEndScale(float scale)
{
	_endScale = scale;
}

void ParticleActor::SetEndColor(const Color& color)
{
	_endColor = color;
}

void ParticleActor::SetSpeedRange(float minSpeed, float maxSpeed)
{
	_minSpeed = minSpeed;
	_maxSpeed = maxSpeed;
}

void ParticleActor::SetMinSpeed(float minSpeed)
{
	_minSpeed = minSpeed;
}

void ParticleActor::SetMaxSpeed(float maxSpeed)
{
	_maxSpeed = maxSpeed;
}

void ParticleActor::SetGravity(const Vector2& gravity)
{
	_gravity = gravity;
}

void ParticleActor::SetAttractor(const Vector2& attractor)
{
	_attractor = attractor;
}

void ParticleActor::SetAttractorStrength(float strength)
{
	_attractorStrength = strength;
}

void ParticleActor::SetMaxParticles(int maxParticles)
{
	// Nothing to do if these match.
	if (_maxParticlesAlive == maxParticles)
		return;

	if (maxParticles <= 0)
	{
		maxParticles = 1;
	}

	if (_particles)
	{
		delete [] _particles;
	}
	_maxParticlesAlive = maxParticles;
	_particles = new Particle[_maxParticlesAlive];

	// Make them all available.   Age < 0.0f = free.
	for (int i=0; i<_maxParticlesAlive; ++i)
	{
		_particles[i]._age = -1.0f;
	}
}

