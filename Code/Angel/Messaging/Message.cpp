#include "../Messaging/Message.h"


Message::Message()
{
	_messageName = "GenericMessage";
	_sender = NULL;
}

Message::Message(String messageName, MessageListener* sender)
{
	_messageName = messageName;
	_sender = sender;
}

const String Message::GetMessageName()
{
	return _messageName;
}

const MessageListener* Message::GetSender()
{
	return _sender;
}
