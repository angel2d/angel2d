%module(directors="1") angel
%{
#include "../../Messaging/Switchboard.h"
#include "../../Messaging/Message.h"
%}

class Message
{
public:
	Message(String messageName, MessageListener* sender = NULL);
	
	virtual const String GetMessageName();
	
	MessageListener* const GetSender();
};

%feature("director") MessageListener;
class MessageListener
{
public:
	virtual ~MessageListener();
	virtual void ReceiveMessage(Message* m) = 0;
};

%nodefaultctor Switchboard;
class Switchboard
{
public:
	static Switchboard& GetInstance();
	
	%apply SWIGTYPE *DISOWN {Message* message};
	void Broadcast(Message* message);
	void DeferredBroadcast(Message* message, float delay);
	%clear Message* message;
	
	const bool SubscribeTo(MessageListener* subscriber, String messageType);
	const bool UnsubscribeFrom(MessageListener* subscriber, String messageType);
	
	const std::set<MessageListener*> GetSubscribersTo(String messageType);
	const StringSet GetSubscriptionsFor(MessageListener* subscriber);
};