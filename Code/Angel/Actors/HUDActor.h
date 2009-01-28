#pragma once

#include "../Actors/Actor.h"

///An Actor that gets drawn in screen-space
/**
 * A HUDActor is drawn in screen-space rather than world-space. You can treat it
 *  just like any other normal Actor, but both its position and size are described
 *  in pixels instead of GL units. The screenspace coordinate system starts at the 
 *  top-left of the window. 
 * 
 * For example, to have an actor be 100 pixels wide and situated in the bottom-right
 *  quadrant of the window (assuming the default window size of 1024x768):
 * 
 * \code
 * HUDActor *h = new HUDActor();
 * h->SetSize(100.0f);
 * h->SetPosition(974.0f, 718.0f);
 * theWorld.Add(h);
 * \endcode
 */
class HUDActor : public Actor 
{
public:
	
	/**
	 * Override of the Actor::Render function to handle drawing in screen-space.
	 */
	virtual void Render();	
};