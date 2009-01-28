#pragma once

#include "../Infrastructure/Common.h"
#include "../Infrastructure/Renderable.h"

typedef std::vector<Renderable*>	RenderList;
typedef std::map<int, RenderList>	RenderLayers;

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
