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
	PhysicsEventActor::Update(dt);
}

void Sentient::Render()
{
	PhysicsEventActor::Render();
	_pathFinder.Render();
	_brain.Render();
}

void SentientFactoryDelegate::InitializeDelegate()
{
	PhysicsEventActorFactoryDelegate::InitializeDelegate();
	_shapeType = PhysicsActor::SHAPETYPE_CIRCLE;
}

