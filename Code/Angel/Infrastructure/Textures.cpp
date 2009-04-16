//////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2008-2009, Shane J. M. Liesegang
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

#include "FreeImage.h"

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

	const char *texFile = filename.c_str();

	// get the image file type from FreeImage
	FREE_IMAGE_FORMAT fifmt = FreeImage_GetFileType(texFile, 0);

	if (fifmt == FIF_UNKNOWN)
	{
		fifmt = FreeImage_GetFIFFromFilename(texFile);
	}

	//actually load the image file
	FIBITMAP *dib = FreeImage_Load(fifmt, texFile, 0);

	if (dib != NULL)
	{
		GLuint texRef = 0;

		// Only generate an index if it's not cached.
		if (cached)
			texRef = currentCacheEntry->textureIndex;
		else
			glGenTextures(1, &texRef);

		glBindTexture(GL_TEXTURE_2D, texRef);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, clampmode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, clampmode);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filtermode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filtermode);

		GLenum format;
		int numComponents;

		if (FreeImage_IsTransparent(dib))
		{
			numComponents = 4;
			#if defined(WIN32)
				format = GL_BGRA_EXT;
			#else
				format = GL_RGBA;
			#endif
		}
		else
		{
			numComponents = 3;
			#if defined(WIN32)
				format = GL_BGR_EXT;
			#else
				format = GL_RGB;
			#endif
			dib = FreeImage_ConvertTo24Bits(dib); //want to ensure we don't have an alpha
		}

		BYTE* pixels = (BYTE*)FreeImage_GetBits(dib);

		gluBuild2DMipmaps(
			GL_TEXTURE_2D,
			numComponents,
			FreeImage_GetWidth(dib),
			FreeImage_GetHeight(dib),
			format,
			GL_UNSIGNED_BYTE,
			pixels
			);
		
		FreeImage_Unload(dib);
		
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
	else
	{
		if (!optional)
		{
			sysLog.Log("Failed to find - " + String(texFile));
		}
		return -1;
	}
}

bool PixelsToPositions(std::string filename, std::vector<Vector2> &positions, float gridSize, Color pixelColor, float tolerance)
{
	const char *texFile = filename.c_str();

	// get the image file type from FreeImage
	FREE_IMAGE_FORMAT fifmt = FreeImage_GetFileType(texFile, 0);

	if (fifmt == FIF_UNKNOWN)
	{
		fifmt = FreeImage_GetFIFFromFilename(texFile);
	}

	//actually load the image file
	FIBITMAP *dib = FreeImage_Load(fifmt, texFile, 0);

	if (dib != NULL)
	{
		GLenum format;
		int numComponents;

		if (FreeImage_IsTransparent(dib))
		{
			numComponents = 4;
			//NOTE: FreeImage loads in BGR[A] on little-endian and RGB[A] on big-endian
			//  doesn't matter since we're only using x86/Windows, but this would need to be
			//  ifdeffed if we wanted to support cross-platform stuffs. -- SJML
			format = GL_BGRA_EXT;
		}
		else
		{
			numComponents = 3;
			//NOTE: see above
			format = GL_BGR_EXT;
			dib = FreeImage_ConvertTo24Bits(dib); //want to ensure we don't have an alpha
		}

		BYTE* pixels = (BYTE*)FreeImage_GetBits(dib);

		int width = FreeImage_GetWidth(dib);
		int height = FreeImage_GetHeight(dib);
		int widthCount = 0;
		int count = 0;
		Vector2 offset(-width*gridSize/2.f, -height*gridSize/2.f);
		RGBQUAD targetRGB;
		targetRGB.rgbBlue = BYTE(255.f * pixelColor.B);
		targetRGB.rgbGreen = BYTE(255.f * pixelColor.G);
		targetRGB.rgbRed = BYTE(255.f * pixelColor.R);
		BYTE tol = BYTE(255.f * tolerance);
		RGBQUAD* rgb = new RGBQUAD();
		for (int y=0; y < height; y++)
		{
			for (int x=0; x < width; x++)
			{
				FreeImage_GetPixelColor(dib, x, y, rgb);
				if (abs((int)rgb->rgbBlue - (int)targetRGB.rgbBlue) <= tol
					&& abs((int)rgb->rgbGreen - (int)targetRGB.rgbGreen) <= tol
					&& abs((int)rgb->rgbRed - (int)targetRGB.rgbRed) <= tol 
					)
				{
					positions.push_back(offset + Vector2(x * gridSize, y * gridSize));
				}
			}
		}
		FreeImage_Unload(dib);
		return true; 
	}
	else
	{
		sysLog.Log("Failed to find - " + String(texFile));
		return false;
	}
}