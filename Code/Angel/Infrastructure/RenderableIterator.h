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
