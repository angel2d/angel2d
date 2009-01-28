#include "../Infrastructure/RenderableIterator.h"

#include "../Infrastructure/World.h"

RenderableIterator& RenderableIterator::begin()
{
	if (theWorld.GetLayers().size() == 0)
	{
		return end();
	}
	_layerIterator = theWorld.GetLayers().begin();
	while ((_layerIterator->second.size() == 0))
	{
		if (_layerIterator != theWorld.GetLayers().end())
		{
			return end();
		}
		_layerIterator++;
	}
	_myIterator = _layerIterator->second.begin();
	_ptr = *_myIterator;
	return *this;
}

RenderableIterator& RenderableIterator::end()
{
	_ptr = 0;
	return *this;
}

bool RenderableIterator::operator!=( const RenderableIterator& iter ) const
{
	return ( _ptr != iter._ptr );
}

RenderableIterator& RenderableIterator::erase( RenderableIterator& item_to_remove )
{
	Renderable* pValueToErase = *item_to_remove;

	RenderLayers::iterator layerElements = theWorld.GetLayers().find( pValueToErase->GetLayer() );
	if (layerElements != theWorld.GetLayers().end())
	{
		RenderList::iterator element = (*layerElements).second.begin();

		while ( element != (*layerElements).second.end() )
		{
			if ( *element == pValueToErase)
			{					
				_myIterator = (*layerElements).second.erase(element);

				// Have to force to next layer.
				// Let our ++ operator do it's magic.
				if ( _myIterator == (*layerElements).second.end() )
				{
					++item_to_remove;
				}
				else
				{
					_ptr = *_myIterator;
				}

				return *this;
			}
			++element;
		}
	}
	return *this;
}

const RenderableIterator& RenderableIterator::operator++()
{
	if (_myIterator == _layerIterator->second.end())
	{
		if (_layerIterator == theWorld.GetLayers().end())
		{
			_ptr = 0;
			return *this;
		}
	}
	else
		++_myIterator;

	// See if we've reached the end of the vector for the current layer.
	if (_myIterator == _layerIterator->second.end())
	{
		++_layerIterator;
		// Go through layers until you reach the end or a non-empty layer.
		while (_layerIterator != theWorld.GetLayers().end() && _layerIterator->second.size() == 0)
			++_layerIterator;

		if (_layerIterator != theWorld.GetLayers().end() && _layerIterator->second.size() > 0)
		{	
			_myIterator = _layerIterator->second.begin();
		}
		else
			_ptr = NULL;
	}
	if (_ptr)
		_ptr = *_myIterator;

	return *this;
}