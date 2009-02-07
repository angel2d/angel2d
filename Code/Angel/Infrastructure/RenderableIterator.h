#pragma once

#include "../Infrastructure/Common.h"
#include "../Infrastructure/Renderable.h"

typedef std::vector<Renderable*>	RenderList;
typedef std::map<int, RenderList>	RenderLayers;

///An iterator class to access Renderables in the World
/** 
 * This class is an iterator that gives access to all the Renderables that have
 *  been added to the World. Access is sequential, going through one layer at
 *  at a time, but current ordering behavior shouldn't be relied on. 
 */
class RenderableIterator: public std::iterator<std::forward_iterator_tag, Renderable*>
{
public:
	RenderableIterator() : _ptr(NULL)
	{
	}

	Renderable* operator*()
	{
		return (_ptr);
	}

	RenderableIterator& begin();
	RenderableIterator& end();

	bool operator!=( const RenderableIterator& iter ) const;
	RenderableIterator& erase( RenderableIterator& item_to_remove );
	const RenderableIterator& operator++();

private:	
	RenderLayers::iterator _layerIterator;
	RenderList::iterator _myIterator;
	Renderable *_ptr;
};
