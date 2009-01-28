#pragma once

#include "../Actors/Actor.h"

///An Actor which takes up the whole drawing space.
/**
 * A FullScreenActor will resize itself whenever the size of the drawing space
 *  changes. This makes it useful for backdrops, curtains, splash screens, etc. 
 */
class FullScreenActor : public Actor
{
public:
	/**
	 * The constructor subscribes the Actor to CameraChange messages and does
	 *  the initial orientation to the camera. 
	 */
	FullScreenActor();
	
	/**
	 * You can lock a FullScreenActor to keep it from tracking the changes to 
	 *  the drawing area or camera. When you unlock it, it will snap back to 
	 *  taking up the whole screen. 
	 * 
	 * @param locked whether or not the FullScreenActor should continue to track
	 *   camera changes
	 */
	void SetLock(bool locked);
	
	/**
	 * To check on the lock status.
	 * 
	 * @return whether or not this FullScreenActor is currently tracking the camera
	 */
	const bool IsLocked();
	
	/**
	 * An implementation of the MessageListener interface, which listens for 
	 *  CameraChange messages and responds appropriately. 
	 * 
	 * @see MessageListener
	 * @param message The message getting delivered. 
	 */
	virtual void ReceiveMessage(Message *message);
	
private:
	bool _locked;
	void _resize();
};
