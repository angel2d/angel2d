#include "../AI/Sentient.h"

//#include "../Infrastructure/Console.h"
#include "../Infrastructure/TextRendering.h"
#include "../Util/DrawUtil.h"

Sentient::Sentient()
{
	_brain.SetActor(this);
}


void Sentient::Update(float dt)
{
	_brain.Update( dt );
	PhysicsActor::Update(dt);
}

void Sentient::Render()
{
	PhysicsActor::Render();
	_pathFinder.Render();
	_brain.Render();
}


