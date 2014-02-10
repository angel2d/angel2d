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

#include "stdafx.h"
#include "../Infrastructure/TagCollection.h"

#include <algorithm>
#include <iterator>


TagCollection* TagCollection::s_TagCollection = NULL;

TagCollection& TagCollection::GetInstance()
{
	if (s_TagCollection == NULL)
	{
		s_TagCollection = new TagCollection();
	}
	return *s_TagCollection;
}

TagCollection::TagCollection()
{

}

ActorSet TagCollection::GetObjectsTagged(String findTag)
{
	StringList tags = SplitString(findTag, ", ");
	if (tags.size() == 0)
	{
		return ActorSet();
	}
	else if (tags.size() == 1)
	{
		findTag = ToLower(findTag);
		std::map<String, ActorSet>::iterator it = _tagMappings.find(findTag);
		if (it != _tagMappings.end())
		{
			return it->second;
		}
		else
		{
			return ActorSet();
		}
	}
	else
	{
		ActorSet t1;
		ActorSet t2;
		String searchTag = ToLower(tags[0]);
		
		bool t1_active = true;
		t1 = GetObjectsTagged(searchTag);

		for(unsigned int i=1; i < tags.size(); i++)
		{
			searchTag = ToLower(tags[i]);
			ActorSet compare = GetObjectsTagged(searchTag);
			if (t1_active)
			{
				std::set_intersection(t1.begin(), t1.end(), compare.begin(), compare.end(), std::inserter(t2, t2.begin()));
				t1.clear();
				t1_active = false;
			}
			else
			{
				std::set_intersection(t2.begin(), t2.end(), compare.begin(), compare.end(), std::inserter(t1, t1.begin()));
				t2.clear();
				t1_active = true;
			}
		}

		if (t1_active)
		{
			return t1;
		}
		else
		{
			return t2;
		}
	}
}

StringSet TagCollection::GetTagList()
{
	StringSet forReturn;
	std::map<String, ActorSet>::iterator it = _tagMappings.begin();
	while (it != _tagMappings.end())
	{
		forReturn.insert(it->first);
		it++;
	}

	return forReturn;
}


void TagCollection::AddObjToTagList(Actor* obj, const String& tag)
{
	_tagMappings[tag].insert(obj);
}

void TagCollection::RemoveObjFromTagList(Actor* obj, const String& tag)
{
	_tagMappings[tag].erase(obj);
	if (_tagMappings[tag].empty())
	{
		_tagMappings.erase(tag);
	}
}