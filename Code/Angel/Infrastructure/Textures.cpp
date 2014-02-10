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
#include "../Infrastructure/Textures.h"

#include "../AngelConfig.h"
#include "../Infrastructure/Log.h"

#if ANGEL_MOBILE || ANGEL_DISABLE_DEVIL
	#define _ANGEL_DISABLE_DEVIL 1
#else
	#define _ANGEL_DISABLE_DEVIL 0
#endif

#if !_ANGEL_DISABLE_DEVIL
	#define ILUT_USE_OPENGL
	#undef  _UNICODE
	#include "IL/il.h"
	#include "IL/ilu.h"
	#include "IL/ilut.h"
#else
	#include "png.h"
#endif

void InitializeTextureLoading()
{
	#if !_ANGEL_DISABLE_DEVIL
		ilInit();
		iluInit();
		ilutInit();
		glDisable(GL_TEXTURE_2D);
		
		// Convert any paletted images
		ilEnable(IL_CONV_PAL);
		// Allegedly gets rid of dithering on some nvidia cards. 
		ilutEnable(ILUT_OPENGL_CONV);
	#endif
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
	GLuint			width;
	GLuint			height;
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

const int GetTextureReference(const String& filename, bool bOptional)
{
	return GetTextureReference(filename, GL_CLAMP, GL_LINEAR, bOptional);
}

bool PurgeTexture(const String& filename)
{
	std::map<String,TextureCacheEntry>::iterator it = theTextureCache.find(filename);
	if (it == theTextureCache.end())
	{
		return false;
	}
	glDeleteTextures(1, &it->second.textureIndex);
	theTextureCache.erase(it);
	return true;
}

#if !_ANGEL_DISABLE_DEVIL
	void HandleDevILErrors(const String& errorPrefix="")
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

	void ClearDevILErrors()
	{
		ILenum error = ilGetError();
		while (error != IL_NO_ERROR)
		{
			error = ilGetError();
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
		
		if (!ilutGLTexImage(0)) 
		{
			glDeleteTextures(1, &TexID);
			return 0;
		}
		
		return TexID;
	}
#else
	bool LoadPNG(const String& filename, png_byte* &PNG_image_buffer, png_uint_32 &width, png_uint_32 &height, bool optional)
	{
		FILE *PNG_file = fopen(filename.c_str(), "rb");
		if (PNG_file == NULL)
		{
			if (!optional)
				sysLog.Printf("ERROR: Couldn't open %s.", filename.c_str());
			return false;
		}
		
		GLubyte PNG_header[8];
		
		fread(PNG_header, 1, 8, PNG_file);
		if (png_sig_cmp(PNG_header, 0, 8) != 0)
		{
			if (!optional)
				sysLog.Printf("ERROR: %s is not a PNG.", filename.c_str());
			return false;
		}
		
		png_structp PNG_reader = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
		if (PNG_reader == NULL)
		{
			if (!optional)
				sysLog.Printf("ERROR: Can't start reading %s.", filename.c_str());
			fclose(PNG_file);
			return false;
		}
		
		png_infop PNG_info = png_create_info_struct(PNG_reader);
		if (PNG_info == NULL)
		{
			if (!optional)
				sysLog.Printf("ERROR: Can't get info for %s.", filename.c_str());
			png_destroy_read_struct(&PNG_reader, NULL, NULL);
			fclose(PNG_file);
			return false;
		}
		
		png_infop PNG_end_info = png_create_info_struct(PNG_reader);
		if (PNG_end_info == NULL)
		{
			if (!optional)
				sysLog.Printf("ERROR: Can't get end info for %s.", filename.c_str());
			png_destroy_read_struct(&PNG_reader, &PNG_info, NULL);
			fclose(PNG_file);
			return false;
		}
		
		if (setjmp(png_jmpbuf(PNG_reader)))
		{
			if (!optional)
				sysLog.Printf("ERROR: Can't load %s.", filename.c_str());
			png_destroy_read_struct(&PNG_reader, &PNG_info, &PNG_end_info);
			fclose(PNG_file);
			return false;
		}

		png_init_io(PNG_reader, PNG_file);
		png_set_sig_bytes(PNG_reader, 8);
		
		png_read_info(PNG_reader, PNG_info);
		
		width = png_get_image_width(PNG_reader, PNG_info);
		height = png_get_image_height(PNG_reader, PNG_info);

		png_uint_32 bit_depth, color_type;
		bit_depth = png_get_bit_depth(PNG_reader, PNG_info);
		color_type = png_get_color_type(PNG_reader, PNG_info);

		if (color_type == PNG_COLOR_TYPE_PALETTE)
		{
			png_set_palette_to_rgb(PNG_reader);
		}

		if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8) 
		{
			png_set_expand_gray_1_2_4_to_8(PNG_reader);
		}

		if (color_type == PNG_COLOR_TYPE_GRAY ||
			color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
		{
			png_set_gray_to_rgb(PNG_reader);
		}

		if (png_get_valid(PNG_reader, PNG_info, PNG_INFO_tRNS))
		{
			png_set_tRNS_to_alpha(PNG_reader);
		}
		else
		{
			png_set_filler(PNG_reader, 0xff, PNG_FILLER_AFTER);
		}

		if (bit_depth == 16)
		{
			png_set_strip_16(PNG_reader);
		}

		png_read_update_info(PNG_reader, PNG_info);

		PNG_image_buffer = (png_byte*)malloc(4 * width * height);
		png_byte** PNG_rows = (png_byte**)malloc(height * sizeof(png_byte*));

		unsigned int row;
		for (row = 0; row < height; ++row)
		{
			PNG_rows[height - 1 - row] = PNG_image_buffer + (row * 4 * width);
		}

		png_read_image(PNG_reader, PNG_rows);

		free(PNG_rows);

		png_destroy_read_struct(&PNG_reader, &PNG_info, &PNG_end_info);
		fclose(PNG_file);

		return true;
	}

	// adapted from SimpleImage
	// http://onesadcookie.com/svn/SimpleImage/
	int BindPNG(const String& filename, GLuint &texRef, GLuint &outWidth, GLuint &outHeight, GLint clampmode, GLint filtermode, bool optional)
	{
		png_byte* pngData;
		png_uint_32 width, height;
		
		if (!LoadPNG(filename, pngData, width, height, optional))
		{
			//error was output by the load
			return -1;
		}

		outWidth = width;
		outHeight = height;

		glGenTextures(1, &texRef);
		glBindTexture(GL_TEXTURE_2D, texRef);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, clampmode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, clampmode);
		
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filtermode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filtermode);
		
		glTexImage2D(
			GL_TEXTURE_2D,
			0, 
			GL_RGBA,
			width,
			height,
			0,
			GL_RGBA,
			GL_UNSIGNED_BYTE,
			pngData
		);
		
		free(pngData);
		
		return 0;
	}
#endif //_ANGEL_DISABLE_DEVIL

const int GetTextureReference(const String& filename, GLint clampmode, GLint filtermode, bool optional)
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

	GLuint texRef;
	GLuint width = 0;
	GLuint height = 0;
	#if !_ANGEL_DISABLE_DEVIL
		ILuint imgRef;

		ilGenImages(1, &imgRef);
		ilBindImage(imgRef);

		// Load it up, log any errors if we need to
		if (!ilLoadImage(filename.c_str()))
		{
			if (!optional)
			{
				HandleDevILErrors(filename);
			}
			else 
			{
				ClearDevILErrors();
			}

			ilDeleteImages(1, &imgRef);
			return -1;
		}

		// Store dimensions
		width = ilGetInteger(IL_IMAGE_WIDTH);
		height = ilGetInteger(IL_IMAGE_HEIGHT);

		// Send it to GL
		texRef = BindTexImageWithClampAndFilter(clampmode, filtermode);

		// Clear it out
		ilDeleteImages(1, &imgRef);
		
		// output any errors that happened during the binding/deleting
		HandleDevILErrors(filename);
	#else
		int result = BindPNG(filename, texRef, width, height, clampmode, filtermode, optional);
		if (result != 0)
		{
			return -1;
		}
	#endif //_ANGEL_DISABLE_DEVIL
	
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
		newEntry.width = width;
		newEntry.height = height;
		newEntry.dirty = false;
		theTextureCache[filename] = newEntry;
	}
	
	return texRef;
}

const Vec2i GetTextureSize(const String& filename)
{
	std::map<String,TextureCacheEntry>::iterator it = theTextureCache.find(filename);
	if (it == theTextureCache.end())
	{
		return Vec2i(0, 0);
	}
	else
	{
		return Vec2i(it->second.width, it->second.height);
	}
}

bool GetRawImageData(const String& filename, std::vector<Color> &pixels)
{
	#if _ANGEL_DISABLE_DEVIL
		png_byte* pngData;
		float* rawData;
		png_uint_32 width, height;
		
		if (!LoadPNG(filename, pngData, width, height, true))
		{
			//error was output by the load
			return false;
		}

		// convert png ubyte data to float array
		rawData = (float*)malloc(4 * width * height * sizeof(float));
		
		int j = 0;
		for (int i = 0; i < (4 * width * height); i++)
		{
			rawData[j] = (float)pngData[i] / 255.0f;
			j++;
		}

		free(pngData);
	#else
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
		unsigned int width  = ilGetInteger(IL_IMAGE_WIDTH);
		unsigned int height = ilGetInteger(IL_IMAGE_HEIGHT);
		
		// convert it to RGB floats for easy comparison
		ilConvertImage(IL_RGBA, IL_FLOAT);
	
		// flip it if we need to
		if (ilGetInteger(IL_IMAGE_ORIGIN) != IL_ORIGIN_LOWER_LEFT)
		{
			iluFlipImage();
		}

		// grab the raw data
		ILfloat* rawData = (ILfloat*)ilGetData(); 
	#endif //_ANGEL_DISABLE_DEVIL

	// convert every pixel into colors
	float pixR, pixG, pixB, pixA;
	unsigned int pixOffset = 0;
	for (int y=0; y < height; y++)
	{
		for (int x=0; x < width; x++)
		{
			pixOffset = (y * width * 4) + (x * 4);
			pixR = rawData[pixOffset];
			pixG = rawData[pixOffset + 1];
			pixB = rawData[pixOffset + 2];
			pixA = rawData[pixOffset + 3];
			pixels.push_back(Color(pixR, pixG, pixB, pixA));
		}
	}

	// cleanup and return
	#if _ANGEL_DISABLE_DEVIL
		free(rawData);
	#else
		ilDeleteImages(1, &imgRef);
	#endif

	return true;
}

bool PixelsToPositions(const String& filename, Vector2List &positions, float gridSize, const Color& pixelColor, float tolerance)
{
	#if _ANGEL_DISABLE_DEVIL
		png_byte* pngData;
		float* rawData;
		png_uint_32 width, height;
		
		if (!LoadPNG(filename, pngData, width, height, true))
		{
			//error was output by the load
			return false;
		}

		// convert png ubyte data to float array
		rawData = (float*)malloc(3 * width * height * sizeof(float));
		
		int j = 0;
		for (int i = 0; i < (4 * width * height); i++)
		{
			if ((i+1) % 4)
			{
				rawData[j] = (float)pngData[i] / 255.0f;
				j++;
			}
		}

		free(pngData);
	#else
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
		unsigned int width  = ilGetInteger(IL_IMAGE_WIDTH);
		unsigned int height = ilGetInteger(IL_IMAGE_HEIGHT);
		
		// convert it to RGB floats for easy comparison
		ilConvertImage(IL_RGB, IL_FLOAT);
	
		// flip it if we need to
		if (ilGetInteger(IL_IMAGE_ORIGIN) != IL_ORIGIN_LOWER_LEFT)
		{
			iluFlipImage();
		}

		// grab the raw data
		ILfloat* rawData = (ILfloat*)ilGetData(); 
	#endif //_ANGEL_DISABLE_DEVIL
	
	// check every pixel, see if it's within the tolerance of the target
	float w = -((float)width)*gridSize/2.f;
	float h = -((float)height)*gridSize/2.f;
	Vector2 offset(w, h);
	float pixR, pixG, pixB;
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
	#if _ANGEL_DISABLE_DEVIL
		free(rawData);
	#else
		ilDeleteImages(1, &imgRef);
	#endif

	return true;
}
