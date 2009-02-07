#pragma once

#include "../Actors/Actor.h"

#define theTagList TagCollection::GetInstance()

///A helper class that manages the tags you can set on Actors
/** 
 * Whenever you call Actor::Tag or Actor::Untag, the Actor manipulates the 
 *  tag collection appropriately for you. The only functions here you should
 *  be thinking about are TagCollection::GetObjectsTagged and 
 *  TagCollection::GetTagList. 
 * 
 * Like the Camera and the World, it uses the singleton pattern; you can't 
 *  actually declare a new instance of a TagCollection. To access sound in 
 *  your world, use "theTagList" to retrieve the singleton object. "theTagList" 
 *  is defined in both C++ and Python. 
 * 
 * If you're not familiar with the singleton pattern, this paper is a good 
 *  starting point. (Don't be afraid that it's written by Microsoft.)
 * 
 * http://msdn.microsoft.com/en-us/library/ms954629.aspx
 */
class TagCollection
{
public:
	/**
	 * Used to access the singleton instance of this class. As a shortcut, 
	 *  you can just use "theTagList". 
	 * 
	 * @return The singleton
	 */
	static TagCollection& GetInstance();
	
	/**
	 * Returns the set of all Actors who have the given tag. 
	 * 
	 * @param findTag The tag of interest
	 * @return An ActorSet of everyone who is tagged thusly
	 */
	ActorSet GetObjectsTagged(String findTag);
	
	/**
	 * Get a list of all the tags currently in use. 
	 * 
	 * @return All current tags as a StringSet
	 */
	StringSet GetTagList();

	/**
	 * Adds a tag to a given Actor. Shouldn't be called directly; use the 
	 *  Actor::Tag function. 
	 * 
	 * @param obj The Actor to tag
	 * @param tag The tag to apply
	 */
	void AddObjToTagList(Actor* obj, String tag);
	
	/**
	 * Removes a tag from an Actor. Shouldn't be called directly; use the 
	 *  Actor::Untag function. 
	 * 
	 * @param obj The Actor to untag
	 * @param tag The tag to remove
	 */
	void RemoveObjFromTagList(Actor* obj, String tag);

protected:
	TagCollection();
	static TagCollection* s_TagCollection;

private:
	std::map<String, ActorSet> _tagMappings;
};
