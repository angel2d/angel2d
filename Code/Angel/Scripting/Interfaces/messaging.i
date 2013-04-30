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

template <class T>
class TypedMessage : public Message
{
public:
	TypedMessage(const String& messageName, T value, MessageListener* sender = NULL);
	
	const T GetValue();
};

%template(FloatMessage)		TypedMessage<float>;
%template(IntMessage)		TypedMessage<int>;
%template(StringMessage)	TypedMessage<String>;
%template(Vector2Message)	TypedMessage<Vector2>;
%template(Vector3Message)	TypedMessage<Vector3>;
%template(Vec2iMessage)		TypedMessage<Vec2i>;
%template(Vec2uiMessage)	TypedMessage<Vec2ui>;
%template(Vec3iMessage)		TypedMessage<Vec3i>;
%template(Vec3uiMessage)	TypedMessage<Vec3ui>;


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