#include "../Infrastructure/TagCollection.h"

#include <algorithm>


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
		
		bool t1_active = true;
		t1 = GetObjectsTagged(tags[0]);

		for(unsigned int i=1; i < tags.size(); i++)
		{
			ActorSet compare = GetObjectsTagged(tags[i]);
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


void TagCollection::AddObjToTagList(Actor* obj, String tag)
{
	_tagMappings[tag].insert(obj);
}

void TagCollection::RemoveObjFromTagList(Actor* obj, String tag)
{
	_tagMappings[tag].erase(obj);
	if (_tagMappings[tag].empty())
	{
		_tagMappings.erase(tag);
	}
}