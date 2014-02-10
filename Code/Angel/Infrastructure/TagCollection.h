//////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2008-2014, Shane Liesegang
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
 *  actually declare a new instance of a TagCollection. To access tags in 
 *  your world, use "theTagList" to retrieve the singleton object.  
 *  "theTagList" is defined in both C++ and Lua. 
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
	void AddObjToTagList(Actor* obj, const String& tag);
	
	/**
	 * Removes a tag from an Actor. Shouldn't be called directly; use the 
	 *  Actor::Untag function. 
	 * 
	 * @param obj The Actor to untag
	 * @param tag The tag to remove
	 */
	void RemoveObjFromTagList(Actor* obj, const String& tag);

protected:
	TagCollection();
	static TagCollection* s_TagCollection;

private:
	std::map<String, ActorSet> _tagMappings;
};
