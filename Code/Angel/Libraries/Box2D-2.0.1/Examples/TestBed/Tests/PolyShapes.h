/*
* Copyright (c) 2006-2007 Erin Catto http://www.gphysics.com
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

#ifndef POLY_SHAPES_H
#define POLY_SHAPES_H

#include "../Framework/Render.h"

const int32 k_maxBodies = 256;

class PolyShapes : public Test
{
public:
	PolyShapes()
	{
		// Ground body
		{
			b2PolygonDef sd;
			sd.SetAsBox(50.0f, 10.0f);
			sd.friction = 0.3f;
			sd.filter.categoryBits = 0x0001;
			
			b2BodyDef bd;
			bd.position.Set(0.0f, -10.0f);
			b2Body* ground = m_world->CreateBody(&bd);
			ground->CreateShape(&sd);
		}

		sds[0].vertexCount = 3;
		sds[0].vertices[0].Set(-0.5f, 0.0f);
		sds[0].vertices[1].Set(0.5f, 0.0f);
		sds[0].vertices[2].Set(0.0f, 1.5f);
		sds[0].density = 1.0f;
		sds[0].friction = 0.3f;
		sds[0].filter.categoryBits = 0x0002;
		//sds[0].maskBits = 0x0003;
		
		sds[1].vertexCount = 3;
		sds[1].vertices[0].Set(-0.1f, 0.0f);
		sds[1].vertices[1].Set(0.1f, 0.0f);
		sds[1].vertices[2].Set(0.0f, 1.5f);
		sds[1].density = 1.0f;
		sds[1].friction = 0.3f;
		sds[1].filter.categoryBits = 0x0004;

		sds[2].vertexCount = 8;
		float32 w = 1.0f;
		float32 b = w / (2.0f + sqrtf(2.0f));
		float32 s = sqrtf(2.0f) * b;
		sds[2].vertices[0].Set(0.5f * s, 0.0f);
		sds[2].vertices[1].Set(0.5f * w, b);
		sds[2].vertices[2].Set(0.5f * w, b + s);
		sds[2].vertices[3].Set(0.5f * s, w);
		sds[2].vertices[4].Set(-0.5f * s, w);
		sds[2].vertices[5].Set(-0.5f * w, b + s);
		sds[2].vertices[6].Set(-0.5f * w, b);
		sds[2].vertices[7].Set(-0.5f * s, 0.0f);
		sds[2].density = 1.0f;
		sds[2].friction = 0.3f;
		sds[2].filter.categoryBits = 0x0004;

		sds[3].vertexCount = 4;
		sds[3].vertices[0].Set(-0.5f, 0.0f);
		sds[3].vertices[1].Set(0.5f, 0.0f);
		sds[3].vertices[2].Set(0.5f, 1.0f);
		sds[3].vertices[3].Set(-0.5f, 1.0f);
		sds[3].density = 1.0f;
		sds[3].friction = 0.3f;
		sds[3].filter.categoryBits = 0x0004;

		circleDef.radius = 0.5f;
		circleDef.density = 1.0f;

		bodyIndex = 0;
		memset(bodies, 0, sizeof(bodies));
	}

	void Create(int32 index)
	{
		if (bodies[bodyIndex] != NULL)
		{
			m_world->DestroyBody(bodies[bodyIndex]);
			bodies[bodyIndex] = NULL;
		}

		b2BodyDef bd;

		float32 x = b2Random(-2.0f, 2.0f);
		bd.position.Set(x, 10.0f);
		bd.angle = b2Random(-b2_pi, b2_pi);

		if (index == 4)
		{
			bd.angularDamping = 0.02f;
		}

		bodies[bodyIndex] = m_world->CreateBody(&bd);

		if (index < 4)
		{
			bodies[bodyIndex]->CreateShape(sds + index);
		}
		else
		{
			bodies[bodyIndex]->CreateShape(&circleDef);
		}
		bodies[bodyIndex]->SetMassFromShapes();

		bodyIndex = (bodyIndex + 1) % k_maxBodies;
	}

	void DestroyBody()
	{
		for (int32 i = 0; i < k_maxBodies; ++i)
		{
			if (bodies[i] != NULL)
			{
				m_world->DestroyBody(bodies[i]);
				bodies[i] = NULL;
				return;
			}
		}
	}

	void Keyboard(unsigned char key)
	{
		switch (key)
		{
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
			Create(key - '1');
			break;

		case 'd':
			DestroyBody();
			break;
		}
	}

	void Step(Settings* settings)
	{
		Test::Step(settings);
		DrawString(5, m_textLine, "Press 1-5 to drop stuff");
		m_textLine += 15;
	}

	static Test* Create()
	{
		return new PolyShapes;
	}

	int32 bodyIndex;
	b2Body* bodies[k_maxBodies];
	b2PolygonDef sds[4];
	b2CircleDef circleDef;
};

#endif
