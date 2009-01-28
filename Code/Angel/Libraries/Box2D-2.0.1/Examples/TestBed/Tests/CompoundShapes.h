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

#ifndef COMPOUND_SHAPES_H
#define COMPOUND_SHAPES_H

// TODO_ERIN test joints on compounds.
class CompoundShapes : public Test
{
public:
	CompoundShapes()
	{
		{
			b2BodyDef bd;
			bd.position.Set(0.0f, -10.0f);
			b2Body* body = m_world->CreateBody(&bd);

			b2PolygonDef sd;
			sd.SetAsBox(50.0f, 10.0f);
			body->CreateShape(&sd);
		}

		{
			b2CircleDef sd1;
			sd1.radius = 0.5f;
			sd1.localPosition.Set(-0.5f, 0.5f);
			sd1.density = 2.0f;

			b2CircleDef sd2;
			sd2.radius = 0.5f;
			sd2.localPosition.Set(0.5f, 0.5f);
			sd2.density = 0.0f; // massless

			for (int i = 0; i < 10; ++i)
			{
				float32 x = b2Random(-0.1f, 0.1f);
				b2BodyDef bd;
				bd.position.Set(x + 5.0f, 1.05f + 2.5f * i);
				bd.angle = b2Random(-b2_pi, b2_pi);
				b2Body* body = m_world->CreateBody(&bd);
				body->CreateShape(&sd1);
				body->CreateShape(&sd2);
				body->SetMassFromShapes();
			}
		}

		{
			b2PolygonDef sd1;
			sd1.SetAsBox(0.25f, 0.5f);
			sd1.density = 2.0f;

			b2PolygonDef sd2;
			sd2.SetAsBox(0.25f, 0.5f, b2Vec2(0.0f, -0.5f), 0.5f * b2_pi);
			sd2.density = 2.0f;

			for (int i = 0; i < 10; ++i)
			{
				float32 x = b2Random(-0.1f, 0.1f);
				b2BodyDef bd;
				bd.position.Set(x - 5.0f, 1.05f + 2.5f * i);
				bd.angle = b2Random(-b2_pi, b2_pi);
				b2Body* body = m_world->CreateBody(&bd);
				body->CreateShape(&sd1);
				body->CreateShape(&sd2);
				body->SetMassFromShapes();
			}
		}

		{
			b2XForm xf1;
			xf1.R.Set(0.3524f * b2_pi);
			xf1.position = b2Mul(xf1.R, b2Vec2(1.0f, 0.0f));

			b2PolygonDef sd1;
			sd1.vertexCount = 3;
			sd1.vertices[0] = b2Mul(xf1, b2Vec2(-1.0f, 0.0f));
			sd1.vertices[1] = b2Mul(xf1, b2Vec2(1.0f, 0.0f));
			sd1.vertices[2] = b2Mul(xf1, b2Vec2(0.0f, 0.5f));
			sd1.density = 2.0f;

			b2XForm xf2;
			xf2.R.Set(-0.3524f * b2_pi);
			xf2.position = b2Mul(xf2.R, b2Vec2(-1.0f, 0.0f));

			b2PolygonDef sd2;
			sd2.vertexCount = 3;
			sd2.vertices[0] = b2Mul(xf2, b2Vec2(-1.0f, 0.0f));
			sd2.vertices[1] = b2Mul(xf2, b2Vec2(1.0f, 0.0f));
			sd2.vertices[2] = b2Mul(xf2, b2Vec2(0.0f, 0.5f));
			sd2.density = 2.0f;

			for (int32 i = 0; i < 10; ++i)
			{
				float32 x = b2Random(-0.1f, 0.1f);
				b2BodyDef bd;
				bd.position.Set(x, 2.05f + 2.5f * i);
				bd.angle = 0.0f;
				b2Body* body = m_world->CreateBody(&bd);
				body->CreateShape(&sd1);
				body->CreateShape(&sd2);
				body->SetMassFromShapes();
			}
		}

		{
			b2PolygonDef sd_bottom;
			sd_bottom.SetAsBox( 1.5f, 0.15f );
			sd_bottom.density = 4.0f;

			b2PolygonDef sd_left;
			sd_left.SetAsBox(0.15f, 2.7f, b2Vec2(-1.45f, 2.35f), 0.2f);
			sd_left.density = 4.0f;

			b2PolygonDef sd_right;
			sd_right.SetAsBox(0.15f, 2.7f, b2Vec2(1.45f, 2.35f), -0.2f);
			sd_right.density = 4.0f;

			b2BodyDef bd;
			bd.position.Set( 0.0f, 2.0f );
			b2Body* body = m_world->CreateBody(&bd);
			body->CreateShape(&sd_bottom);
			body->CreateShape(&sd_left);
			body->CreateShape(&sd_right);
			body->SetMassFromShapes();
		}
	}

	static Test* Create()
	{
		return new CompoundShapes;
	}
};

#endif
