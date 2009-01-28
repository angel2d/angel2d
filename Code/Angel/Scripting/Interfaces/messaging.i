%module angel
%{
#include "../../Messaging/Switchboard.h"
#include "../../Messaging/Message.h"
%}

class Message
{
public:
	Message(String messageType, MessageListener* sender = NULL);
	
	virtual const String GetMessageType();
	
	const MessageListener* GetSender();
	void SetSender(MessageListener* sender);
};


class MessageListener
{
public:
	virtual void ReceiveMessage(Message* m) = 0;
};

%nodefaultctor Switchboard;
class Switchboard
{
public:
	static Switchboard& GetInstance();
	
	void Broadcast(Message* message);
	void DeferredBroadcast(Message* message, float delay);
	
	const bool SubscribeTo(MessageListener* subscriber, String messageType);
	const bool UnsubscribeFrom(MessageListener* subscriber, String messageType);
	
	const std::set<MessageListener*> GetSubscribersTo(String messageType);
	const StringSet GetSubscriptionsFor(MessageListener* subscriber);
};