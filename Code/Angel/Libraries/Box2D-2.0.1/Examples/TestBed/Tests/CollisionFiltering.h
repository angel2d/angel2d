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

#ifndef COLLISION_FILTERING_H
#define COLLISION_FILTERING_H

// This is a test of collision filtering.
// There is a triangle, a box, and a circle.
// There are 6 shapes. 3 large and 3 small.
// The 3 small ones always collide.
// The 3 large ones never collide.
// The boxes don't collide with triangles (except if both are small).
const int16	k_smallGroup = 1;
const int16 k_largeGroup = -1;

const uint16 k_defaultCategory = 0x0001;
const uint16 k_triangleCategory = 0x0002;
const uint16 k_boxCategory = 0x0004;
const uint16 k_circleCategory = 0x0008;

const uint16 k_triangleMask = 0xFFFF;
const uint16 k_boxMask = 0xFFFF ^ k_triangleCategory;
const uint16 k_circleMask = 0xFFFF;

class CollisionFiltering : public Test
{
public:
	CollisionFiltering()
	{
		// Ground body
		{
			b2PolygonDef sd;
			sd.SetAsBox(50.0f, 10.0f);
			sd.friction = 0.3f;

			b2BodyDef bd;
			bd.position.Set(0.0f, -10.0f);

			b2Body* ground = m_world->CreateBody(&bd);
			ground->CreateShape(&sd);
		}

		// Small triangle
		b2PolygonDef triangleShapeDef;
		triangleShapeDef.vertexCount = 3;
		triangleShapeDef.vertices[0].Set(-1.0f, 0.0f);
		triangleShapeDef.vertices[1].Set(1.0f, 0.0f);
		triangleShapeDef.vertices[2].Set(0.0f, 2.0f);
		triangleShapeDef.density = 1.0f;

		triangleShapeDef.filter.groupIndex = k_smallGroup;
		triangleShapeDef.filter.categoryBits = k_triangleCategory;
		triangleShapeDef.filter.maskBits = k_triangleMask;

		b2BodyDef triangleBodyDef;
		triangleBodyDef.position.Set(-5.0f, 2.0f);

		b2Body* body1 = m_world->CreateBody(&triangleBodyDef);
		body1->CreateShape(&triangleShapeDef);
		body1->SetMassFromShapes();

		// Large triangle (recycle definitions)
		triangleShapeDef.vertices[0] *= 2.0f;
		triangleShapeDef.vertices[1] *= 2.0f;
		triangleShapeDef.vertices[2] *= 2.0f;
		triangleShapeDef.filter.groupIndex = k_largeGroup;
		triangleBodyDef.position.Set(-5.0f, 6.0f);
		triangleBodyDef.fixedRotation = true; // look at me!

		b2Body* body2 = m_world->CreateBody(&triangleBodyDef);
		body2->CreateShape(&triangleShapeDef);
		body2->SetMassFromShapes();

		// Small box
		b2PolygonDef boxShapeDef;
		boxShapeDef.SetAsBox(1.0f, 0.5f);
		boxShapeDef.density = 1.0f;

		boxShapeDef.filter.groupIndex = k_smallGroup;
		boxShapeDef.filter.categoryBits = k_boxCategory;
		boxShapeDef.filter.maskBits = k_boxMask;

		b2BodyDef boxBodyDef;
		boxBodyDef.position.Set(0.0f, 2.0f);

		b2Body* body3 = m_world->CreateBody(&boxBodyDef);
		body3->CreateShape(&boxShapeDef);
		body3->SetMassFromShapes();

		// Large box (recycle definitions)
		boxShapeDef.SetAsBox(2.0f, 1.0f);
		boxShapeDef.filter.groupIndex = k_largeGroup;
		boxBodyDef.position.Set(0.0f, 6.0f);

		b2Body* body4 = m_world->CreateBody(&boxBodyDef);
		body4->CreateShape(&boxShapeDef);
		body4->SetMassFromShapes();

		// Small circle
		b2CircleDef circleShapeDef;
		circleShapeDef.radius = 1.0f;
		circleShapeDef.density = 1.0f;

		circleShapeDef.filter.groupIndex = k_smallGroup;
		circleShapeDef.filter.categoryBits = k_circleCategory;
		circleShapeDef.filter.maskBits = k_circleMask;

		b2BodyDef circleBodyDef;
		circleBodyDef.position.Set(5.0f, 2.0f);
		
		b2Body* body5 = m_world->CreateBody(&circleBodyDef);
		body5->CreateShape(&circleShapeDef);
		body5->SetMassFromShapes();

		// Large circle
		circleShapeDef.radius *= 2.0f;
		circleShapeDef.filter.groupIndex = k_largeGroup;
		circleBodyDef.position.Set(5.0f, 6.0f);

		b2Body* body6 = m_world->CreateBody(&circleBodyDef);
		body6->CreateShape(&circleShapeDef);
		body6->SetMassFromShapes();
	}
	static Test* Create()
	{
		return new CollisionFiltering;
	}
};

#endif
