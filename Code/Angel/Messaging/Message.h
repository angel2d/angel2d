#pragma once

#include "../Infrastructure/Common.h"
#include "../Util/StringUtil.h"

class MessageListener;

class Message
{
public:
	Message();
	Message(String messageType, MessageListener* sender = NULL);
	
	virtual const String GetMessageType();
	
	const MessageListener* GetSender();
	void SetSender(MessageListener* sender);
	
protected:
	String _messageType;
	MessageListener* _sender;
};

template <class T>
class TypedMessage : public Message
{
public:
	TypedMessage(String messageType, T value, MessageListener* sender = NULL)
	{
		_messageType = messageType;
		_value = value;
		_sender = sender;
	}
	
	const T GetValue()
	{
		return _value;
	}
	void SetValue(T value)
	{
		_value = value;
	}
	
protected:
	T _value;
};

class MessageListener
{
public:
	virtual void ReceiveMessage(Message* m) = 0;
};