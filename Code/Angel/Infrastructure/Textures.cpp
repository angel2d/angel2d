#include "../Infrastructure/Textures.h"

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
		//std::cout << "Found cached texture - " << filename.c_str() << std::endl;
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

		//std::cout << "Loading - " << texFile << std::endl;

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
			std::cout << "Failed to find - " << texFile << std::endl;
		}
		return -1;
	}
}