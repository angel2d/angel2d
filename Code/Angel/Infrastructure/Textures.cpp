//////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2008-2010, Shane J. M. Liesegang
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

#include "../Infrastructure/Textures.h"

#include "../Infrastructure/Log.h"

#define ILUT_USE_OPENGL
#undef  _UNICODE
#include "IL/il.h"
#include "IL/ilu.h"
#include "IL/ilut.h"

void InitializeTextureLoading()
{
	ilInit();
	iluInit();
	ilutInit();
	glDisable(GL_TEXTURE_2D);
	
	// Convert any paletted images
	ilEnable(IL_CONV_PAL);
	// Allegedly gets rid of dithering on some nvidia cards. 
	ilutEnable(ILUT_OPENGL_CONV);
}

void FinalizeTextureLoading()
{
	//nothing right now
}

struct TextureCacheEntry
{
	String			filename;
	GLint			clampMode;
	GLint			filterMode;
	GLuint			textureIndex;
	bool			dirty;
};
std::map<String, TextureCacheEntry> theTextureCache;

void FlushTextureCache()
{
	// Iterate all the entries in the texture cache and dirty them.
	std::map<String,TextureCacheEntry>::iterator it = theTextureCache.begin();
	for (/*no init*/; it != theTextureCache.end(); ++it)
	{
		it->second.dirty = true;
		GetTextureReference(it->second.filename, it->second.clampMode, it->second.filterMode, false);
	}
}

const int GetTextureReference(String filename, bool bOptional)
{
	return GetTextureReference(filename, GL_CLAMP, GL_LINEAR, bOptional);
}

void HandleDevILErrors(String errorPrefix="")
{
	ILenum error = ilGetError();
	if (error != IL_NO_ERROR)
	{
		sysLog.Log("DevIL errors loading: " + errorPrefix);
		do 
		{
			sysLog.Log(iluErrorString(error));
		} while ((error = ilGetError()));
	}
}

// Modified from the ilut source file for GLBind
GLuint BindTexImageWithClampAndFilter(GLint ClampMode, GLint FilterMode)
{
	GLuint	TexID = 0;

	glGenTextures(1, &TexID);
	glBindTexture(GL_TEXTURE_2D, TexID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, ClampMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, ClampMode);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, FilterMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, FilterMode);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);
	glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
	glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
	glPixelStorei(GL_UNPACK_SWAP_BYTES, IL_FALSE);

	if (!ilutGLTexImage(0)) {
		glDeleteTextures(1, &TexID);
		return 0;
	}

	return TexID;
}

const int GetTextureReference(String filename, GLint clampmode, GLint filtermode, bool optional)
{
	bool cached = false;
	TextureCacheEntry* currentCacheEntry = NULL;
	
	//check cache to see if it's loaded already
	std::map<String,TextureCacheEntry>::iterator it = theTextureCache.find(filename);
	
	// See if we already have it in the cache.
	if (it != theTextureCache.end())
	{
		// If we found it and it's not dirty, bail out with the index.
		if (!it->second.dirty)
		{
			return it->second.textureIndex;
		}
		
		// We found it, but it's dirty.  We'll reload the texture below.
		cached = true;
		currentCacheEntry = &(it->second);
	}
	
	ILuint imgRef;
	GLuint texRef;

	ilGenImages(1, &imgRef);
	ilBindImage(imgRef);

	// Load it up, log any errors
	if (!ilLoadImage(filename.c_str()))
	{
		if (!optional)
		{
			HandleDevILErrors(filename);
		}
		return -1;
	}

	// Send it to GL
	texRef = BindTexImageWithClampAndFilter(clampmode, filtermode);

	// Clear it out
	ilDeleteImages(1, &imgRef);
	
	// output any errors that happened during the binding/deleting
	HandleDevILErrors(filename);
	
	// If it was cached, clear the dirty flag so we don't try and load it again.
	if (cached)
	{
		currentCacheEntry->dirty = false;
	}
	// If we're not cached, add a new entry.
	else 
	{
		TextureCacheEntry newEntry;
		newEntry.filename = filename;
		newEntry.clampMode = clampmode;
		newEntry.filterMode = filtermode;
		newEntry.textureIndex = texRef;
		newEntry.dirty = false;
		theTextureCache[filename] = newEntry;
	}
	
	return texRef;

}

bool PixelsToPositions(std::string filename, std::vector<Vector2> &positions, float gridSize, Color pixelColor, float tolerance)
{
	ILuint imgRef;

	ilGenImages(1, &imgRef);
	ilBindImage(imgRef);
	
	// load image into DevIL
	if (!ilLoadImage(filename.c_str()))
	{
		HandleDevILErrors(filename);
		return false;
	}
	
	// get image datums
	int width = ilGetInteger(IL_IMAGE_WIDTH);
	int height = ilGetInteger(IL_IMAGE_HEIGHT);
	Vector2 offset(-width*gridSize/2.f, -height*gridSize/2.f);
	
	// convert it to RGB floats
	ilConvertImage(IL_RGB, IL_FLOAT);
	
	// grab the raw data
	ILfloat* rawData = (ILfloat*)ilGetData(); 
	
	// check every pixel, see if it's within the tolerance of the target
	ILfloat pixR, pixG, pixB;
	unsigned int pixOffset = 0;
	for (int y=0; y < height; y++)
	{
		for (int x=0; x < width; x++)
		{
			pixOffset = (y * width * 3) + (x * 3);
			pixR = rawData[pixOffset];
			pixG = rawData[pixOffset + 1];
			pixB = rawData[pixOffset + 2];
			if (   fabs(pixR - pixelColor.R) <= tolerance
				&& fabs(pixG - pixelColor.G) <= tolerance
				&& fabs(pixB - pixelColor.B) <= tolerance
				)
			{
				positions.push_back(offset + Vector2(x * gridSize, y * gridSize));
			}
		}
	}
	
	// cleanup and return
	ilDeleteImages(1, &imgRef);
	return true;
}
