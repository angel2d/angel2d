#pragma once

#include "../Infrastructure/Common.h"
#include "../Messaging/Message.h"
#include "../Util/MathUtil.h"

#include <queue>

#define theSwitchboard Switchboard::GetInstance()

class Switchboard
{
public:
	static Switchboard& GetInstance();
	
	void Broadcast(Message* message);
	void DeferredBroadcast(Message* message, float delay);

	void Update(float dt);

	const bool SubscribeTo(MessageListener* subscriber, String messageType);
	const bool UnsubscribeFrom(MessageListener* subscriber, String messageType);
	
	const std::set<MessageListener*> GetSubscribersTo(String messageType);
	const StringSet GetSubscriptionsFor(MessageListener* subscriber);

	void SendAllMessages();

protected:
	Switchboard();
	static Switchboard* s_Switchboard;

private:
	std::queue<Message*> _messages;
	
	std::map< String, std::set<MessageListener*> > _subscribers;
	std::map< MessageListener*, StringSet > _subscriptions;
	
	struct MessageTimer
	{
		Message* _message;
		float _timeRemaining;

		MessageTimer(Message* message, float timeRemaining)
		{
			_message = message;
			_timeRemaining = MathUtil::Min(0.0f, timeRemaining);
		}
	};
	std::vector<MessageTimer> _delayedMessages;

	struct SubscriptionInfo 
	{
		MessageListener* _subscriber;
		String _messageType;
		
		SubscriptionInfo(MessageListener* subscriber, String messageType) :
			_subscriber(subscriber),
			_messageType(messageType)
		{}
	};
	bool _messagesLocked;
	std::vector<SubscriptionInfo> _deferredAdds;
	std::vector<SubscriptionInfo> _deferredRemoves;
};
