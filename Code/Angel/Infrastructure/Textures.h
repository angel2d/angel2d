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

/** 
 * @file
 *  A low-level C-style interface for managing textures. Most of the
 *   functionality is wrapped in the Actor classes, which is where you should 
 *   probably be focusing. The function you might otherwise care about in here 
 *   is FlushTextureCache.
 */
#pragma once

#include "../Util/StringUtil.h"
#include "../Infrastructure/Color.h"

/**
 * Do whatever setup needs to be done at program start. 
 */
void InitializeTextureLoading();

/**
 * Do whatever cleanup needs to be done at program end. 
 */
void FinalizeTextureLoading();

/**
 * Goes through all loaded textures and marks them as dirty, so the next time
 *  they're referenced the file will be loaded up fresh from the disk. The
 *  effect of this is that you can update your texture files and see them 
 *  in-game without having to restart. 
 */
void FlushTextureCache();

/**
 * Get the GL texture reference from a file path. If this is the first time
 *  a file has been referenced, it will be loaded from disk and formatted 
 *  appropriately for OpenGL. Thus you use this function to both load your
 *  textures initially and to reference them afterwards. 
 * 
 * @param name The path to the file to load. Must be readable by DevIL.
 *   (http://openil.sourceforge.net/)
 * @param optional If true, the engine won't complain if it can't load it. 
 * @return The GLuint that OpenGL uses to reference the texture. If the number
 *   is negative, that means the texture couldn't be loaded or found. 
 */
const int GetTextureReference(const String& name, bool optional = false);

/**
 * The same as the above function, but with some more available parameters if
 *  you want control over how to display this texture. See OpenGL docs for
 *  further explanation of how these parameters work. 
 * 
 * @param name The path to the file to load. Must be readable by DevIL.
 *   (http://openil.sourceforge.net/)
 * @param clampmode Either GL_CLAMP or GL_REPEAT. 
 * @param filtermode One of: GL_NEAREST, GL_LINEAR, GL_NEAREST_MIPMAP_NEAREST,
 *   GL_LINEAR_MIPMAP_NEAREST, GL_NEAREST_MIPMAP_LINEAR, or GL_LINEAR_MIPMAP_LINEAR
 * @param optional If true, the engine won't complain if it can't load it.
 * @return The GLuint that OpenGL uses to reference the texture. If the number
 *   is negative, that means the texture couldn't be loaded or found. 
 */
const int GetTextureReference(const String& filename, GLint clampmode, GLint filtermode, bool optional = false);

/**
 * Gets the dimensions for a loaded texture. 
 *
 * @param filename The path to the texture's file.
 * @return The width and height of the texture; if no texture is currently
 *   loaded from the given filename, will return (0, 0)
 */
const Vec2i GetTextureSize(const String& filename);

/**
 * Remove a texture from memory. On the desktop this usually isn't an issue 
 *  unless your game is long-running and uses lots of images, but those
 *  issues crop up earlier on mobile platforms. 
 * 
 * @param filename The filename of the texture to be removed
 * @return Whether the texture was previously loaded into memory or not
 */
bool PurgeTexture(const String& filename);

/**
 * Use this function to get the raw pixel data of an image as a vector
 *  of Color structures. 
 *
 * @param filename The path to the file to load
 * @param pixels The vector of Colors to populate
 * @return Whether the image was found and processed.
 */
bool GetRawImageData(const String& filename, std::vector<Color> &pixels);

/**
 * Use this function to process an image into positional data, in other words,
 *  use an image as map or level data. For every pixel within the tolerance
 *  range of the specified color, a Vector2 is added to positions. Resulting
 *  positions will be in range imageSizeX * gridSize, imageSizeY * gridSize, and
 *  be centered on 0,0. 
 * 
 * @param filename The path to the file to load.
 * @param positions The vector of Vector2s to populate
 * @param gridSize The size of the grid, i.e. how much space one pixel occupies.
 * @param pixelColor The color to search the image for (channels in 0.0-1.0 range).  
 *   NOTE: Alpha component is unused.
 * @param tolerance The amount RGB channels can deviate from pixelColor.
 * @return Whether the image was found and processed.
 */
bool PixelsToPositions(const String& filename, Vector2List &positions, float gridSize, const Color& pixelColor, float tolerance=0.1f);
