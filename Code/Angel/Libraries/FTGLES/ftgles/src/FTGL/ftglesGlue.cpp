/*
 
 Copyright (c) 2010 David Petrie
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 
 */

#include "ftglesGlue.h"

struct Vertex 
{
	float xyz[3];
	float st[2];
	GLubyte c[4];
};

#define MAX_VERTS 16384

typedef struct Vertex Vertex;
Vertex immediate[MAX_VERTS];
Vertex vab;
short quad_indexes[MAX_VERTS * 3 / 2];
int curr_vertex;
GLenum curr_prim;
bool initted = false;

GLvoid ftglInitImmediateModeGL() 
{
	// deprecated.
}


GLvoid ftglBegin(GLenum prim) 
{
	if (!initted)
	{
		for (int i = 0; i < MAX_VERTS * 3 / 2; i += 6) 
		{
			int q = i / 6 * 4;
			quad_indexes[i + 0] = q + 0;
			quad_indexes[i + 1] = q + 1;
			quad_indexes[i + 2] = q + 2;
			
			quad_indexes[i + 3] = q + 0;
			quad_indexes[i + 4] = q + 2;
			quad_indexes[i + 5] = q + 3;
		}
		initted = true;
	}
	curr_vertex = 0;
	curr_prim = prim;
}


GLvoid ftglVertex3f(float x, float y, float z) 
{
	assert(curr_vertex < MAX_VERTS);
	vab.xyz[0] = x;
	vab.xyz[1] = y;
	vab.xyz[2] = z;
	immediate[curr_vertex] = vab;
	curr_vertex++;
}


GLvoid ftglVertex2f(float x, float y) 
{
	assert(curr_vertex < MAX_VERTS);
	vab.xyz[0] = x;
	vab.xyz[1] = y;
	vab.xyz[2] = 0.0f;
	immediate[curr_vertex] = vab;
	curr_vertex++;
}


GLvoid ftglColor4ub(GLubyte r, GLubyte g, GLubyte b, GLubyte a) 
{
	vab.c[0] = r;
	vab.c[1] = g;
	vab.c[2] = b;
	vab.c[3] = a;
}


GLvoid ftglColor4f(GLfloat r, GLfloat g, GLfloat b, GLfloat a) 
{
	vab.c[0] = (GLubyte) (r * 255);
	vab.c[1] = (GLubyte) (g * 255);
	vab.c[2] = (GLubyte) (b * 255);
	vab.c[3] = (GLubyte) (a * 255);
}


GLvoid ftglTexCoord2f(GLfloat s, GLfloat t) 
{
	vab.st[0] = s;
	vab.st[1] = t;
}


GLvoid bindArrayBuffers()
{
}


GLvoid ftglBindTexture()
{
	
}


GLvoid ftglEnd() 
{
	GLboolean vertexArrayEnabled;
	GLboolean texCoordArrayEnabled;
	GLboolean colorArrayEnabled;
	
	GLvoid * vertexArrayPointer;
	GLvoid * texCoordArrayPointer;
	GLvoid * colorArrayPointer;
	
	GLint vertexArrayType, texCoordArrayType, colorArrayType;
	GLint vertexArraySize, texCoordArraySize, colorArraySize;
	GLsizei vertexArrayStride, texCoordArrayStride, colorArrayStride;
	
	bool resetPointers = false;
	
	glGetPointerv(GL_VERTEX_ARRAY_POINTER, &vertexArrayPointer);
	glGetPointerv(GL_TEXTURE_COORD_ARRAY_POINTER, &texCoordArrayPointer);
	glGetPointerv(GL_COLOR_ARRAY_POINTER, &colorArrayPointer);

	glGetBooleanv(GL_VERTEX_ARRAY, &vertexArrayEnabled);
	glGetBooleanv(GL_TEXTURE_COORD_ARRAY, &texCoordArrayEnabled);
	glGetBooleanv(GL_COLOR_ARRAY, &colorArrayEnabled);

	if (!vertexArrayEnabled)
	{
		glEnableClientState(GL_VERTEX_ARRAY);
	}
	
	if (vertexArrayPointer != &immediate[0].xyz)
	{
		glGetIntegerv(GL_VERTEX_ARRAY_TYPE, &vertexArrayType);
		glGetIntegerv(GL_VERTEX_ARRAY_SIZE, &vertexArraySize);
		glGetIntegerv(GL_VERTEX_ARRAY_STRIDE, &vertexArrayStride);
		if (texCoordArrayEnabled)
		{
			glGetIntegerv(GL_TEXTURE_COORD_ARRAY_TYPE, &texCoordArrayType);
			glGetIntegerv(GL_TEXTURE_COORD_ARRAY_SIZE, &texCoordArraySize);
			glGetIntegerv(GL_TEXTURE_COORD_ARRAY_STRIDE, &texCoordArrayStride);
		}	
		if (colorArrayEnabled)
		{
			glGetIntegerv(GL_COLOR_ARRAY_TYPE, &colorArrayType);
			glGetIntegerv(GL_COLOR_ARRAY_SIZE, &colorArraySize);
			glGetIntegerv(GL_COLOR_ARRAY_STRIDE, &colorArrayStride);
		}	
		glVertexPointer(3, GL_FLOAT, sizeof(Vertex), immediate[0].xyz);
		glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), immediate[0].st);
		glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(Vertex), immediate[0].c);
		
		resetPointers = true;
	}
	
	if (!texCoordArrayEnabled)
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	
	if (!colorArrayEnabled)
		glEnableClientState(GL_COLOR_ARRAY);
	
	if (curr_vertex == 0) 
	{
		curr_prim = 0;
		return;
	}
	
	if (curr_prim == GL_QUADS) 
	{
		glDrawElements(GL_TRIANGLES, curr_vertex / 4 * 6, GL_UNSIGNED_SHORT, quad_indexes);
	} 
	else 
	{
		glDrawArrays(curr_prim, 0, curr_vertex);
	}
	curr_vertex = 0;
	curr_prim = 0;
	
	if (resetPointers)
	{
		if (vertexArrayEnabled)
		{
			glVertexPointer(vertexArraySize, vertexArrayType, 
							vertexArrayStride, vertexArrayPointer);	
		}
		if (texCoordArrayEnabled)
		{
			glTexCoordPointer(texCoordArraySize, texCoordArrayType, 
							  texCoordArrayStride, texCoordArrayPointer);
		}
		if (colorArrayEnabled)
		{
			glColorPointer(colorArraySize, colorArrayType, 
						   colorArrayStride, colorArrayPointer);
		}
	}
	
	if (!vertexArrayEnabled)
		glDisableClientState(GL_VERTEX_ARRAY);
	
	if (!texCoordArrayEnabled)
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	
	if (!colorArrayEnabled)
		glDisableClientState(GL_COLOR_ARRAY);
}


GLvoid ftglError(const char *source)
{
	GLenum error = glGetError();
	 
	switch (error) {
		case GL_NO_ERROR:
			break;
		case GL_INVALID_ENUM:
			printf("GL Error (%x): GL_INVALID_ENUM. %s\n\n", error, source);
			break;
		case GL_INVALID_VALUE:
			printf("GL Error (%x): GL_INVALID_VALUE. %s\n\n", error, source);
			break;
		case GL_INVALID_OPERATION:
			printf("GL Error (%x): GL_INVALID_OPERATION. %s\n\n", error, source);
			break;
		case GL_STACK_OVERFLOW:
			printf("GL Error (%x): GL_STACK_OVERFLOW. %s\n\n", error, source);
			break;
		case GL_STACK_UNDERFLOW:
			printf("GL Error (%x): GL_STACK_UNDERFLOW. %s\n\n", error, source);
			break;
		case GL_OUT_OF_MEMORY:
			printf("GL Error (%x): GL_OUT_OF_MEMORY. %s\n\n", error, source);
			break;
		default:
			printf("GL Error (%x): %s\n\n", error, source);
			break;
	}
}