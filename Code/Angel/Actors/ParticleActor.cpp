#include "../Actors/ParticleActor.h"

#include "../Infrastructure/DeveloperConsole.h"
#include "../Actors/ActorFactory.h"
#include "../Util/MathUtil.h"

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
				currentParticle._vel =  currentParticle._vel + _gravity * dt;

				currentParticle._color.R = MathUtil::Lerp(_color.R, _endColor.R, lifePercent);
				currentParticle._color.G = MathUtil::Lerp(_color.G, _endColor.G, lifePercent);
				currentParticle._color.B = MathUtil::Lerp(_color.B, _endColor.B, lifePercent);

				currentParticle._color.A = MathUtil::Lerp(_startAlpha, _endAlpha, lifePercent);

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
		_systemLifetime -= dt;

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
	dt += _generationResidue;

	int numParticlesToGenerate = int(_particlesPerSecond * dt);
	_generationResidue = _particlesPerSecond * dt - float(numParticlesToGenerate);
	
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

		glBegin(GL_QUADS);
			//glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex2f( 0.5f,  0.5f);
			glTexCoord2f(0.0f, 1.0f); glVertex2f(-0.5f,  0.5f);
			glTexCoord2f(0.0f, 0.0f); glVertex2f(-0.5f, -0.5f);
			glTexCoord2f(1.0f, 0.0f); glVertex2f( 0.5f, -0.5f);
		glEnd();

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

void ParticleActor::SetEndAlpha(float alpha)
{
	_endAlpha = alpha;
}

void ParticleActor::SetEndScale(float scale)
{
	_endScale = scale;
}

void ParticleActor::SetEndColor(Color& color)
{
	_endColor = color;
}

void ParticleActor::SetSpeedRange(float minSpeed, float maxSpeed)
{
	_minSpeed = minSpeed;
	_maxSpeed = maxSpeed;
}

void ParticleActor::SetGravity(Vector2& gravity)
{
	_gravity = gravity;
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


// 
// ActorFactory support.
//
void ActorFactorySetEmissionRate(const String& input)
{
	ACTORFACTORY_GETDELEGATE(pDel, ParticleActorFactoryDelegate);

	pDel->SetEmissionRate( StringToFloat(input) );
}

void ActorFactorySetSystemLifetime(const String& input)
{
	ACTORFACTORY_GETDELEGATE(pDel, ParticleActorFactoryDelegate);

	pDel->SetSystemLifetime( StringToFloat(input) );
}

void ActorFactorySetParticleLifetime(const String& input)
{
	ACTORFACTORY_GETDELEGATE(pDel, ParticleActorFactoryDelegate);

	pDel->SetParticleLifetime( StringToFloat(input) );
}

void ActorFactorySetSpread(const String& input)
{
	ACTORFACTORY_GETDELEGATE(pDel, ParticleActorFactoryDelegate);

	pDel->SetSpread( StringToFloat(input) );
}

void ActorFactorySetEndScale(const String& input)
{
	ACTORFACTORY_GETDELEGATE(pDel, ParticleActorFactoryDelegate);

	pDel->SetEndScale( StringToFloat(input) );
}

void ActorFactorySetEndColor(const String& input)
{
	ACTORFACTORY_GETDELEGATE(pDel, ParticleActorFactoryDelegate);

	float r,g,b;
	r=g=b=0.0f;

	StringList colors = SplitString(input);
	int size = colors.size();
	if( size > 0 )
		r = StringToFloat(colors[0]);
	if( size > 1 )
		g = StringToFloat(colors[1]);
	if( size > 2 )
		b = StringToFloat(colors[2]);

	pDel->SetEndColor( r, g, b	);
}

void ActorFactorySetEndAlpha(const String& input)
{
	ACTORFACTORY_GETDELEGATE(pDel, ParticleActorFactoryDelegate);

	pDel->SetEndAlpha( StringToFloat(input) );
}

void ActorFactorySetMinSpeed(const String& input)
{
	ACTORFACTORY_GETDELEGATE(pDel, ParticleActorFactoryDelegate);

	pDel->SetMinSpeed( StringToFloat(input) );
}

void ActorFactorySetMaxSpeed(const String& input)
{
	ACTORFACTORY_GETDELEGATE(pDel, ParticleActorFactoryDelegate);

	pDel->SetMaxSpeed( StringToFloat(input) );
}

void ActorFactorySetGravity(const String& input)
{
	ACTORFACTORY_GETDELEGATE(pDel, ParticleActorFactoryDelegate);

	StringList values = SplitString(input);
	int size = values.size();

	Vector2 gravity(0.0f, 0.0f);	

	// X and Y are specified.
	if (size == 2)
	{
		gravity.X = StringToFloat(values[0]);
		gravity.Y = StringToFloat(values[1]);
	}
	// If only one value specified, assume it's just vertical.
	else if (size == 1 )
	{
		gravity.X = 0.0f;
		gravity.Y = StringToFloat(values[0]);
	}

	pDel->SetGravity(gravity);
}

void ActorFactorySetMaxParticles(const String& input)
{
	ACTORFACTORY_GETDELEGATE(pDel, ParticleActorFactoryDelegate);

	pDel->SetMaxParticles( StringToInt(input) );
}

void ParticleActorFactoryDelegate::RegisterOriginalConsoleCommands()
{
	CONSOLE_DECLARECMDSTATICFLAGS( ActorFactorySetEmissionRate, ActorFactorySetEmissionRate, ConsoleCommand::CCF_CONFIG );
	CONSOLE_DECLARECMDSTATICFLAGS( ActorFactorySetSystemLifetime, ActorFactorySetSystemLifetime, ConsoleCommand::CCF_CONFIG );
	CONSOLE_DECLARECMDSTATICFLAGS( ActorFactorySetParticleLifetime, ActorFactorySetParticleLifetime, ConsoleCommand::CCF_CONFIG );
	CONSOLE_DECLARECMDSTATICFLAGS( ActorFactorySetSpread, ActorFactorySetSpread, ConsoleCommand::CCF_CONFIG );
	CONSOLE_DECLARECMDSTATICFLAGS( ActorFactorySetEndScale, ActorFactorySetEndScale, ConsoleCommand::CCF_CONFIG );
	CONSOLE_DECLARECMDSTATICFLAGS( ActorFactorySetEndColor, ActorFactorySetEndColor, ConsoleCommand::CCF_CONFIG );
	CONSOLE_DECLARECMDSTATICFLAGS( ActorFactorySetEndAlpha, ActorFactorySetEndAlpha, ConsoleCommand::CCF_CONFIG );
	CONSOLE_DECLARECMDSTATICFLAGS( ActorFactorySetMinSpeed, ActorFactorySetMinSpeed, ConsoleCommand::CCF_CONFIG );
	CONSOLE_DECLARECMDSTATICFLAGS( ActorFactorySetMaxSpeed, ActorFactorySetMaxSpeed, ConsoleCommand::CCF_CONFIG );
	CONSOLE_DECLARECMDSTATICFLAGS( ActorFactorySetGravity, ActorFactorySetGravity, ConsoleCommand::CCF_CONFIG );
	CONSOLE_DECLARECMDSTATICFLAGS( ActorFactorySetMaxParticles, ActorFactorySetMaxParticles, ConsoleCommand::CCF_CONFIG );
}

Actor* ParticleActorFactoryDelegate::CreateInstance()
{
	return new ParticleActor(); //rb - TODO - Revisit this.
}

void ParticleActorFactoryDelegate::FinishInstance(Actor* pActor)
{
	ParticleActor* pParticleActor = (ParticleActor*)pActor;
	
	pParticleActor->_particlesPerSecond = _emissionRate;
	pParticleActor->_systemLifetime = _systemLifetime;
	pParticleActor->_particleLifetime = _particleLifetime;
	pParticleActor->_spreadRadians = _spreadRadians;

	pParticleActor->_endColor = _end_color;

	pParticleActor->_endScale = _endScale;
	pParticleActor->_endAlpha = _endAlpha;

	pParticleActor->_minSpeed = _minSpeed;
	pParticleActor->_maxSpeed = _maxSpeed;

	pParticleActor->_gravity = _gravity;

	//rb - Make the rest of these use accessors.

	pParticleActor->SetMaxParticles(_maxParticles);
}

//
// Attribute set functions.
//
void ParticleActorFactoryDelegate::SetEmissionRate(float rate)
{
	_emissionRate = rate;
}

void ParticleActorFactoryDelegate::SetSystemLifetime(float lifetime)
{
	_systemLifetime = lifetime;
}

void ParticleActorFactoryDelegate::SetParticleLifetime(float lifetime)
{
	_particleLifetime = lifetime;
}

void ParticleActorFactoryDelegate::SetSpread(float spread)
{
	_spreadRadians = spread;	
}

void ParticleActorFactoryDelegate::SetEndScale(float endScale)
{
	_endScale = endScale;
}

void ParticleActorFactoryDelegate::SetEndColor(float r, float g, float b)
{
	_end_color = Color(r, g, b);
}

void ParticleActorFactoryDelegate::SetEndAlpha(float endAlpha)
{
	_endAlpha = endAlpha;
}

void ParticleActorFactoryDelegate::SetMinSpeed(float minSpeed)
{
	_minSpeed = minSpeed;
}

void ParticleActorFactoryDelegate::SetMaxSpeed(float maxSpeed)
{
	_maxSpeed = maxSpeed;
}

void ParticleActorFactoryDelegate::SetGravity(Vector2 gravity)
{
	_gravity = gravity;
}

void ParticleActorFactoryDelegate::SetMaxParticles(int maxParticles)
{
	_maxParticles = maxParticles;
}
