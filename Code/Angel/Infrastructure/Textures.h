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

/** 
 * @file
 *  A low-level C-style interface for managing textures. Most of the
 *   functionality is wrapped in the Actor classes, which is where you should 
 *   probably be focusing. The function you might otherwise care about in here 
 *   is FlushTextureCache.
 */
#pragma once

#include "../Util/StringUtil.h"

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
 * @param name The path to the file to load. Must be readable by FreeImage.
 *   (http://freeimage.sourceforge.net/)
 * @param optional If true, the engine won't complain if it can't load it. 
 * @return The GLuint that OpenGL uses to reference the texture. If the number
 *   is negative, that means the texture couldn't be loaded or found. 
 */
const int GetTextureReference(String name, bool optional = false);

/**
 * The same as the above function, but with some more available parameters if
 *  you want control over how to display this texture. See OpenGL docs for
 *  further explanation of how these parameters work. 
 * 
 * @param name The path to the file to load. Must be readable by FreeImage.
 *   (http://freeimage.sourceforge.net/)
 * @param clampmode Either GL_CLAMP or GL_REPEAT. 
 * @param filtermode One of: GL_NEAREST, GL_LINEAR, GL_NEAREST_MIPMAP_NEAREST,
 *   GL_LINEAR_MIPMAP_NEAREST, GL_NEAREST_MIPMAP_LINEAR, or GL_LINEAR_MIPMAP_LINEAR
 * @param optional If true, the engine won't complain if it can't load it.
 * @return The GLuint that OpenGL uses to reference the texture. If the number
 *   is negative, that means the texture couldn't be loaded or found. 
 */
const int GetTextureReference(String filename, GLint clampmode, GLint filtermode, bool optional = false);
