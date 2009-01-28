#pragma once

#include "../Infrastructure/Common.h"
#include "../Util/StringUtil.h"

class MessageListener;

class Message
{
public:
	Message(String messageType, MessageListener* sender = NULL);

	virtual const String GetMessageType();
	
	virtual const void* GetPayload();
	void SetPayload(void* payload);

	const MessageListener* GetSender();
	void SetSender(MessageListener* sender);

private:
	String _messageType;
	MessageListener* _sender;
	void* _payload;
};


class MessageListener
{
public:
	virtual void ReceiveMessage(Message* m) = 0;
};