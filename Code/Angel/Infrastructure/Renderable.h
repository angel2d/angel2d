#pragma once

///Our base simulation element that gets inserted to the World
/** 
 * This is the base class from which most of the simulation elements in Angel
 *  derive. When you insert a Renderable into the World, it will receive 
 *  Update and Render calls once per frame. 
 */
class Renderable
{
	friend class World;

public:
	/**
	 * The base constructor just sets a flag on the Renderable to not 
	 *  delete it, since that would be kind of a buzzkill out of the gate. 
	 * 
	 * @param _deleteMe 
	 */
	Renderable() : _deleteMe(false) {}
	
	/**
	 * Abstract base class needs a virtual destructor. 
	 */
	virtual ~Renderable() {}
	
	/**
	 * This function gets called once per frame. Any game logic for an Actor
	 *  should be done in this function, since it provides you with a dt for
	 *  controlling rate of movement, animation, etc. 
	 * 
	 * Pure virtual function; must be implemented in the subclass. 
	 * 
	 * @param dt The amount of time (in seconds) that has elapsed since the 
	 *  last frame. 
	 */
	virtual void Update(float dt) = 0;
	
	/**
	 * This function also gets called once per frame, \b after the 
	 *  Renderable::Update call. Anything you do in this function should be
	 *  strictly related to drawing something on the screen. Moving it, 
	 *  changing its appearance/properties/etc. should happen in Update. 
	 */
	virtual void Render() = 0;
	
	/**
	 * A safe way to kill off a Renderable -- it will be removed from the 
	 *  world and delete from memory at the end of the current Update loop. 
	 * 
	 * The protected Renderable::PreDestroy function is guaranteed to be 
	 *  called exactly once by this function, even if you call it many times. 
	 */
	void Destroy() 
	{
		if( IsDestroyed() )
			return;
		PreDestroy(); 
		_deleteMe = true;
	}
	
	/**
	 * Used by the World to see if a Renderable is flagged to be deleted. 
	 * 
	 * @return True if the Renderable should be removed and deleted. 
	 */
	bool IsDestroyed() {return _deleteMe;}
	
	/**
	 * The layer to which this Renderable has been assigned in the world. 
	 *  returns garbage if it hasn't been added to the World yet. (Negative 
	 *  layers are valid.)
	 * 
	 * @return The world layer for this Renderable
	 */
	int GetLayer() {return _layer;}
protected:
	/**
	 * Will get called before this Renderable is destroyed (if you do it via 
	 *  the Destroy function, obviously). Override this function in a subclass
	 *  to do any cleanup work that is appropriate to your element. 
	 */
	virtual void PreDestroy() {}

protected:
	bool _deleteMe;
	int _layer;
};
