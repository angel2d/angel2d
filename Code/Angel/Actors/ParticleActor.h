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

/** @file */
#pragma once

#include "../Actors/Actor.h"


///An Actor that draws and keeps track of drawing a particle system on screen. 
/**
 * Particle systems are a very common feature of most games -- they can be 
 *  used for effects like fire, smoke, sparklies, etc. A discussion of the general
 *  use of particles is beyond the scope of this documentation, but if you're
 *  not familiar with the concept, this article by Jeff Lander is a good 
 *  starting point. 
 * 
 * http://www.double.co.nz/dust/col0798.pdf
 */
class ParticleActor : public Actor
{
public:
	/** 
	 * The default constructor creates a particle system that doesn't really 
	 *  do anything, since its maximum number of particles is 0. You'll need
	 *  to call the "Set" functions below to make it look purty.
	 */
	ParticleActor();
	
	/** 
	 * Deletes all the particles this Actor is keeping track of. 
	 */
	~ParticleActor();
	
	/**
	 * Override of the normal Renderable::Update function. Changes the 
	 *  position and appearance of each individual particle appropriately.
	 * 
	 * @param dt The amount of time that's elapsed since the beginning of the last frame. 
	 */
	virtual void Update(float dt);
	
	/** 
	 * Override of the normal Renderable::Render function. Draws each particle.
	 */
	virtual void Render();

	/**
	 * Change the rate at which this system releases particles. Default is 
	 *  20 particles per second. 
	 * 
	 * @param pps The new release rate in particles per second. 
	 */
	void SetParticlesPerSecond(float pps);
	
	/**
	 * Change the system lifetime for this Actor. If the lifetime is set
	 *  less than or equal to 0.0 (the default), the system will last until 
	 *  it's explicitly removed from the world. Otherwise the system will 
	 *  properly remove and deallocate itself when the elapsed time is up. 
	 *  (Useful for when you just want a burst of particles for a period of 
	 *  time and don't want to set up housekeeping timer.)
	 * 
	 * @param lifetime The amount of time this system will persist, in seconds. 
	 */
	void SetSystemLifetime(float lifetime);
	
	/**
	 * Change the lifetime of each individual particle. 
	 * 
	 * @param lifetime Particle lifetime in seconds
	 */
	void SetParticleLifetime(float lifetime);
	
	/**
	 * Set the angle at which particles will disperse themselves. This affects
	 *  their intial velocity only. Default is 0.0 (straight line to the right). 
	 * 
	 * @param radians Emission angle in radians
	 */
	void SetSpread(float radians);
	
	/**
	 * Set the relative size each particle will grow (or shrink) to over its 
	 *  lifetime. The starting size is set with the normal Actor::SetSize 
	 *  function. The ending scale respects the starting aspect ratio. 
	 * 
	 * @param scale The multiplier gradually applied to each particle
	 */
	void SetEndScale(float scale);
	
	/**
	 * Set the color each particle should be at the end of its life. Use an
	 *  alpha of 0.0 to have the particles fade out over time. Starting color
	 *  is set with the normal Actor::SetColor function. 
	 * 
	 * @param color The ending color for each particle in the system. 
	 */
	void SetEndColor(const Color& color);
	
	/**
	 * Set the range of potential initial speeds for the particles. Each 
	 *  particle, at the start of its life, will randomly pick a speed in the 
	 *  given range. 
	 * 
	 * @param minSpeed The speed (in GL units per second) of the slowest particle
	 * @param maxSpeed The speed (in GL units per second) of the fastest particle
	 */
	void SetSpeedRange(float minSpeed, float maxSpeed);
	
	/**
	 * Set the lower range of potential initial speeds for the particles.
	 * 
	 * @param minSpeed The speed (in GL units per second) of the slowest particle
	 */
	void SetMinSpeed(float minSpeed);
	
	/**
	 * Set the lower range of potential initial speeds for the particles.
	 * 
	 * @param maxSpeed The speed (in GL units per second) of the fastest particle
	 */
	void SetMaxSpeed(float maxSpeed);
	
	/**
	 * Set the vector which will pull the particles in a specific direction 
	 *  at a specified magnitude. The default is (0.0, -4.0).
	 * 
	 * @param gravity The vector in which the particles should be pulled
	 *   (magnitude affecting the force of the pull). 
	 */
	void SetGravity(const Vector2& gravity);

	/**
	 * Set the attractor point for the particles -- in addition to gravity,
	 *  which gets applied as a vector, particles will be affected by their
	 *  attraction to this point. Defaults to the origin (0, 0), but since
	 *  the default attractor strength is zero, it will not actually affect
	 *  any movement out of the box. 
	 *
	 * @param attractor The point to which all particles emitted by the
	 *   system will be drawn. It is their destiny. 
	 */
	void SetAttractor(const Vector2& attractor);

	/**
	 * Set the strength of the attractor, or how quickly particles will move
	 *  to it. This does a very simple linear movement; it's not a force in
	 *  the physics sense, so they won't accelerate towards it or anything
	 *  like that. 
	 * 
	 * @param strength The magnitude of the vector between each particle and
	 *   the attractor point. 
	 */
	void SetAttractorStrength(float strength);
	
	/**
	 * Set the maximum number of particles this system can keep track of
	 *  at any one time. Decrease this number if you find you're having 
	 *  performance issues with your particles. 
	 * 
	 * @param maxParticles The maximum number of particles for this system. 
	 */
	void SetMaxParticles(int maxParticles);
	
	/**
	 * Used by the SetName function to create a basename for this class. 
	 *  Overridden from Actor::GetClassName.
	 * 
	 * @return The string "ParticleActor"
	 */
	virtual const String GetClassName() const { return "ParticleActor"; }

protected:
    struct Particle
    {
        Vector2 _pos;
        Vector2 _vel;
        float _age;
        float _lifetime;
        Color _color;
        float _scale;
    };
    
	Particle* _particles;
	int		_maxParticlesAlive;
	int		_numParticlesAlive;

	float	_particlesPerSecond;
	int		_maxParticlesToGenerate;
	float	_generationResidue;

	float	_systemLifetime;
	float	_particleLifetime;

	float	_spreadRadians;

	Color	_endColor; 

	float	_minSpeed; 
	float	_maxSpeed;

	float	_endScale; 

	Vector2 _gravity;
	Vector2 _attractor;
	float _attractorStrength;
};

