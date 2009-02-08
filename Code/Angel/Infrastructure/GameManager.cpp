#include "../Infrastructure/GameManager.h"

#include "../Messaging/Switchboard.h"

void GameManager::Update(float /*dt*/)
{
}

void GameManager::Render()
{
}

GameManager::~GameManager()
{
	StringSet subs = theSwitchboard.GetSubscriptionsFor(this);
	StringSet::iterator it = subs.begin();
	while (it != subs.end())
	{
		theSwitchboard.UnsubscribeFrom(this, *it);
		++it;
	}
}