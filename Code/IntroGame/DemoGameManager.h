#pragma once

#include <vector>
#include <string>

class DemoScreen : public Renderable
{
public:
	DemoScreen();

	virtual void Start();
	virtual void Stop(); //calls remove on all _objects and deletes them
	virtual void Update(float dt);
	virtual void Render();
	
	virtual void ReceiveMessage(Message *message) {}

protected:
	std::vector<Renderable*> _objects;
};


//DemoGameManager is a singleton and inherits from:
//  GameManager -- so we receive update and render calls, plus collision notifications
//  CCmdMemberFunctorOwner -- so we can define console commands to use internal functions
#define theDemoGame DemoGameManager::GetInstance()

class DemoGameManager : public GameManager, public CCmdMemberFunctorOwner
{
public:

	void MoveForwards();
	void MoveBackwards();

	static DemoGameManager &GetInstance();
	virtual void Render();

	virtual void SoundEnded(SOUND_HANDLE sound);

	virtual void ReceiveMessage(Message* message);

protected:
	DemoGameManager();
	static DemoGameManager *s_DemoGameManager;

private:
	std::vector<DemoScreen*> _screens;
	int _current;
	SAMPLE_HANDLE sample;
};
