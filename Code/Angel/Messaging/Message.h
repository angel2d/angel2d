//////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2008-2013, Shane Liesegang
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions are met:
// 
//     * Redistributions of source code must retain the above copyright 
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright 
//       notice, this list of conditions and the following disclaimer in the 
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of the copyright holder nor the names of any 
//       contributors may be used to endorse or promote products derived from 
//       this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
// POSSIBILITY OF SUCH DAMAGE.
//////////////////////////////////////////////////////////////////////////////

#pragma once

#include "../Util/StringUtil.h"

//forward declaration
class MessageListener;

///The base message class which signals an event
/** 
 * A message is used by the Switchboard class to signal to any listeners that
 *  an event has happened. The only information it conveys is the message 
 *  name (a user-definable string) and who sent the message. 
 * 
 * Classes which implement the MessageListener interface can subscribe to
 *  specific types of messages to get notification.
 * 
 * @see MessageListener
 * @see TypedMessage
 * @see Switchboard
 */
class Message
{
public:
	/**
	 * The default constructor creates a Message with the name 
	 *  "GenericMessage" and no sender. 
	 */
	Message();
	
	/**
	 * Virtual destructor.
	 */
	virtual ~Message();
	
	/**
	 * This is the constructor you should actually use -- gives the Message
	 *  a name and sender. 
	 * 
	 * @param messageName The name of this Message; used by MessageListener 
	 *   and the Switchboard to manage delivery. 
	 * @param sender Who sent this Message; NULL by default
	 */
	Message(const String& messageName, MessageListener* sender = NULL);
	
	/**
	 * Get the name of this Message. Since all Messages come to the listener
	 *  via the same ReceiveMessage function, this can be used to filter 
	 *  for specific notifications. 
	 * 
	 * @return The name of this message
	 */
	virtual const String& GetMessageName() const;
	
	/**
	 * Find out who requested this Message to be sent. This can have all sorts
	 *  of semantics depending on what the Message itself is communicating. 
	 * 
	 * @return The sender
	 */
	MessageListener* const GetSender();
	
protected:
	String _messageName;
	MessageListener* _sender;
};

///A templated class for delivering additional information with Messages
/** 
 * This class lets you define your own message types that carry data with 
 *  them. For instance, if you wanted to create a Message that carried 
 *  a world location with it: 
 * 
 * \code
 * TypedMessage<Vector2> *m = new TypedMessage<Vector2>("SomethingHappenedHere", Vector2(-3, -2));
 * \endcode
 * 
 * This gets sent through the Switchboard as just a pointer to the base class,
 *  though, so your MessageReceivers will have to parse what it is from the
 *  Message::GetMessageType function and cast it appropriately from there. 
 */
template <class T>
class TypedMessage : public Message
{
public:
	/**
	 * Creates a new TypedMessage carrying the information you've designated
	 * 
	 * @param messageName The name of the message
	 * @param value Any data of the type defined in the template constructor
	 * @param sender Who is sending this message; NULL by default
	 */
	TypedMessage(const String& messageName, T value, MessageListener* sender = NULL)
	{
		_messageName = messageName;
		_value = value;
		_sender = sender;
	}
	
	/**
	 * Get the data that this Message carries with it
	 * 
	 * @return Data of the type defined in the template constructor
	 */
	const T GetValue()
	{
		return _value;
	}
	
protected:
	T _value;
};

///An interface for sending and receiving Messages via the Switchboard
/** 
 * Any class that wants to participate in messaging must implement this 
 *  interface. It simply defines a function for the Switchboard to call when
 *  delivering Messages. 
 */
class MessageListener
{
public:
	virtual ~MessageListener();
	
	/**
	 * The Switchboard class will call this function for every Message to 
	 *  be deliverd to a designated listener. Implementations of this function
	 *  should filter on Message::GetMessageName to make sure they're 
	 *  responding to the appropriate signals. 
	 * 
	 * @param m The message to be delivered. 
	 */
	virtual void ReceiveMessage(Message* m) = 0;
};
