#include "../Messaging/Switchboard.h"

#include "../Infrastructure/World.h"


Switchboard* Switchboard::s_Switchboard = NULL;

Switchboard::Switchboard()
{
	_messagesLocked = false;
}

Switchboard& Switchboard::GetInstance()
{
	if (s_Switchboard == NULL)
	{
		s_Switchboard = new Switchboard();
	}
	return *s_Switchboard;
}

void Switchboard::Broadcast(Message* message)
{
	_messages.push(message);
}

void Switchboard::DeferredBroadcast(Message* message, float delay)
{
	MessageTimer mt(message, delay);
	_delayedMessages.push_back(mt);
}

void Switchboard::Update(float dt)
{
	std::vector<MessageTimer>::iterator it = _delayedMessages.begin();
	while (it != _delayedMessages.end())
	{
		(*it)._timeRemaining -= dt;
		if ((*it)._timeRemaining <= 0.0f)
		{
			Broadcast((*it)._message);
			it = _delayedMessages.erase(it);
		}
		else
		{
			it++;
		}
	}
}

const bool Switchboard::SubscribeTo(MessageListener* subscriber, String messageType)
{
	if (_messagesLocked)
	{
		_deferredAdds.push_back(SubscriptionInfo(subscriber, messageType));
		return false;
	}
	
	_subscriptions[subscriber].insert(messageType);
	std::pair<std::set<MessageListener*>::iterator, bool> insertResult = _subscribers[messageType].insert(subscriber);
	return insertResult.second;
}

const bool Switchboard::UnsubscribeFrom(MessageListener* subscriber, String messageType)
{
	if (_messagesLocked)
	{
		_deferredRemoves.push_back(SubscriptionInfo(subscriber, messageType));
		return false;
	}
	
	if (_subscribers.find(messageType) == _subscribers.end())
	{
		return false;
	}
	std::set<MessageListener*>::iterator it = _subscribers[messageType].find(subscriber);
	if (it == _subscribers[messageType].end())
	{
		return false;
	}
	else
	{
		_subscribers[messageType].erase(it);
		StringSet::iterator sIt = _subscriptions[subscriber].find(messageType);
		if (sIt != _subscriptions[subscriber].end())
			_subscriptions[subscriber].erase(sIt);
		return true;
	}
}

const std::set<MessageListener*> Switchboard::GetSubscribersTo(String messageType)
{
	if (_subscribers.find(messageType) == _subscribers.end())
	{
		return std::set<MessageListener*>();
	}
	else
	{
		return _subscribers[messageType];		
	}
}

const StringSet Switchboard::GetSubscriptionsFor(MessageListener* subscriber)
{
	if (_subscriptions.find(subscriber) == _subscriptions.end())
	{
		return StringSet();
	}
	else
	{
		return _subscriptions[subscriber];
	}
}

void Switchboard::SendAllMessages()
{
	_messagesLocked = true;
	while (!_messages.empty())
	{
		if (_subscribers.find(_messages.front()->GetMessageType()) != _subscribers.end())
		{
			std::set<MessageListener*>::iterator listenIt = _subscribers[_messages.front()->GetMessageType()].begin();
			while (listenIt != _subscribers[_messages.front()->GetMessageType()].end())
			{
				(*listenIt)->ReceiveMessage(_messages.front());
				listenIt++;
			}
		}
		delete _messages.front();
		_messages.pop();
	}
	_messagesLocked = false;
	
	for(unsigned int i = 0; i < _deferredAdds.size(); i++)
	{
		SubscribeTo(_deferredAdds[i]._subscriber, _deferredAdds[i]._messageType);
	}
	_deferredAdds.clear();
	for(unsigned int i = 0; i < _deferredRemoves.size(); i++)
	{
		UnsubscribeFrom(_deferredRemoves[i]._subscriber, _deferredRemoves[i]._messageType);
	}
	_deferredRemoves.clear();
}