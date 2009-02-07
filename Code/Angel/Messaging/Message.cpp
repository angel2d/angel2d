#include "../Messaging/Message.h"


Message::Message()
{
	_messageType = "GenericMessage";
	_sender = NULL;
}

Message::Message(String messageType, MessageListener* sender)
{
	_messageType = messageType;
	_sender = sender;
}

const String Message::GetMessageType()
{
	return _messageType;
}

const MessageListener* Message::GetSender()
{
	return _sender;
}

void Message::SetSender(MessageListener* sender)
{
	_sender = sender;
}
