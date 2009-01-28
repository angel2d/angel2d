#include "../Messaging/Message.h"


Message::Message(String messageType, MessageListener* sender)
{
	_messageType = messageType;
	_sender = sender;
}

const String Message::GetMessageType()
{
	return _messageType;
}

const void* Message::GetPayload()
{
	return _payload;
}

void Message::SetPayload(void* payload)
{
	_payload = payload;
}

const MessageListener* Message::GetSender()
{
	return _sender;
}

void Message::SetSender(MessageListener* sender)
{
	_sender = sender;
}
