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

#include "../Messaging/Message.h"
#include "../Util/MathUtil.h"

#include <queue>

//Singleton shortcut
#define theSwitchboard Switchboard::GetInstance()

///The central class which handles delivery of Messages
/** 
 * This class is where all Messages pass through to get to their subscribers.
 *  It manages subscribers lists, delivery, and broadcast of messages. 
 * 
 * Like the World, it uses the singleton pattern; you can't actually declare 
 *  a new instance of a Switchboard. To access messaging in your world, use 
 *  "theSwitchboard" to retrieve the singleton object. "theSwitchboard" is 
 *  defined in both C++ and Lua. 
 * 
 * If you're not familiar with the singleton pattern, this paper is a good 
 *  starting point. (Don't be afraid that it's written by Microsoft.)
 * 
 * http://msdn.microsoft.com/en-us/library/ms954629.aspx
 */
class Switchboard
{
public:
	/**
	 * Used to access the singleton instance of this class. As a shortcut, 
	 *  you can just use "theSwitchboard". 
	 * 
	 * @return The singleton
	 */
	static Switchboard& GetInstance();
	
	/**
	 * Send a Message to all the MessageListeners who have subscribed to 
	 *  Messages of that particular name. All Messages are sent at the end
	 *  of the current frame, outside the Update loop. (Which means you can
	 *  safely remove objects from the World in response to a Message.)
	 * 
	 * @param message The message to send
	 */
	void Broadcast(Message* message);
	
	/**
	 * Lets you send a Message after a designated delay. Oftentimes you want
	 *  something to happen a little while *after* an event, and it can be
	 *  be easier to simply defer the sending of the Message rather than
	 *  make the MessageListener responsible for implementing the delay. 
	 * 
	 * @param message The message to send
	 * @param delay Amount of time (in seconds) to wait before sending
	 */
	void DeferredBroadcast(Message* message, float delay);
	
	/**
	 * Takes the same form as the Renderable::Update function, but Switchboard
	 *  is not a Renderable. This function gets called by the World to let
	 *  the Switchboard know about the passage of time so it can manage 
	 *  deferred broadcasts. 
	 * 
	 * @param dt The amount of time elapsed since the last frame
	 */
	void Update(float dt);
	
	/**
	 * Sign a MessageListener up to receive notifications when Messages of
	 *  a specific class are broadcast through the Switchboard. 
	 * 
	 * @param subscriber The MessageListener to sign up
	 * @param messageType The name of the Message it's interested in
	 * @return True if the MessageListener was successfully subscribed -- 
	 *   could be false if the subscription was attempted while messages were
	 *   being delivered (in which case the subscription will start when this
	 *   round of delivery is done) or if the MessageListener was already 
	 *   subscribed to Messages of that name. 
	 */
	const bool SubscribeTo(MessageListener* subscriber, const String& messageType);
	
	/**
	 * Lets a MessageListener stop receiving notifications of specific 
	 *  name. MessageListeners automatically unsubscribe from all their Messages 
	 *  when their destructors are called, so you don't have to worry about
	 *  this when destroying an object; this would only be called directly in 
	 *  user code when you no longer care about a particular Message. 
	 * 
	 * @param subscriber The MessageListener that doesn't want to get these
	 *   Messages anymore
	 * @param messageType The name of the Message they're tired of hearing 
	 *   about
	 * @return True if the MessageListener was successfully unsubscribed --
	 *   could be false if the unsubscription was attempted while messages 
	 *   were being delivered (in which case the subscription will be removed
	 *   when this round of delivery is done) or if the MessageListener was
	 *   not subscribed to Messages of that name. 
	 */
	const bool UnsubscribeFrom(MessageListener* subscriber, const String& messageType);
	
	/**
	 * Get a list of all MessageListeners subscribed to Messages with a 
	 *  given name. 
	 * 
	 * @param messageName The Message you care about
	 * @return A std::set of objects subscribed
	 */
	const std::set<MessageListener*> GetSubscribersTo(const String& messageName);
	
	/**
	 * Get a list of all Message subscriptions for a certain MessageListener
	 * 
	 * @param subscriber The MessageListener you care about
	 * @return A StringSet of all their subscriptions
	 */
	const StringSet GetSubscriptionsFor(MessageListener* subscriber);
	
	/**
	 * Immediately sends all Messages to the appropriate subscribers. Called
	 *  by the World at the end of each frame; you shouldn't call this 
	 *  directly in your game code. 
	 */
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
			_timeRemaining = MathUtil::Max(0.0f, timeRemaining);
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
