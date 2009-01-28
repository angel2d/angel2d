/*
* Copyright (c) 2006-2008 Erin Catto http://www.gphysics.com
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

#ifndef DOMINOS_H
#define DOMINOS_H

class Dominos : public Test
{
public:

	Dominos()
	{
		b2Body* b1;
		{
			b2PolygonDef sd;
			sd.SetAsBox(50.0f, 10.0f);

			b2BodyDef bd;
			bd.position.Set(0.0f, -10.0f);
			b1 = m_world->CreateBody(&bd);
			b1->CreateShape(&sd);
		}

		{
			b2PolygonDef sd;
			sd.SetAsBox(6.0f, 0.25f);

			b2BodyDef bd;
			bd.position.Set(-1.5f, 10.0f);
			b2Body* ground = m_world->CreateBody(&bd);
			ground->CreateShape(&sd);
		}

		{
			b2PolygonDef sd;
			sd.SetAsBox(0.1f, 1.0f);
			sd.density = 20.0f;
			sd.friction = 0.1f;

			for (int i = 0; i < 10; ++i)
			{
				b2BodyDef bd;
				bd.position.Set(-6.0f + 1.0f * i, 11.25f);
				b2Body* body = m_world->CreateBody(&bd);
				body->CreateShape(&sd);
				body->SetMassFromShapes();
			}
		}

		{
			b2PolygonDef sd;
			sd.SetAsBox(7.0f, 0.25f, b2Vec2_zero, 0.3f);

			b2BodyDef bd;
			bd.position.Set(1.0f, 6.0f);
			b2Body* ground = m_world->CreateBody(&bd);
			ground->CreateShape(&sd);
		}

		b2Body* b2;
		{
			b2PolygonDef sd;
			sd.SetAsBox(0.25f, 1.5f);

			b2BodyDef bd;
			bd.position.Set(-7.0f, 4.0f);
			b2 = m_world->CreateBody(&bd);
			b2->CreateShape(&sd);
		}

		b2Body* b3;
		{
			b2PolygonDef sd;
			sd.SetAsBox(6.0f, 0.125f);
			sd.density = 10.0f;

			b2BodyDef bd;
			bd.position.Set(-0.9f, 1.0f);
			bd.angle = -0.15f;

			b3 = m_world->CreateBody(&bd);
			b3->CreateShape(&sd);
			b3->SetMassFromShapes();
		}

		b2RevoluteJointDef jd;
		b2Vec2 anchor;

		anchor.Set(-2.0f, 1.0f);
		jd.Initialize(b1, b3, anchor);
		jd.collideConnected = true;
		m_world->CreateJoint(&jd);

		b2Body* b4;
		{
			b2PolygonDef sd;
			sd.SetAsBox(0.25f, 0.25f);
			sd.density = 10.0f;

			b2BodyDef bd;
			bd.position.Set(-10.0f, 15.0f);
			b4 = m_world->CreateBody(&bd);
			b4->CreateShape(&sd);
			b4->SetMassFromShapes();
		}

		anchor.Set(-7.0f, 15.0f);
		jd.Initialize(b2, b4, anchor);
		m_world->CreateJoint(&jd);

		b2Body* b5;
		{
			b2BodyDef bd;
			bd.position.Set(6.5f, 3.0f);
			b5 = m_world->CreateBody(&bd);

			b2PolygonDef sd;
			sd.density = 10.0f;
			sd.friction = 0.1f;

			sd.SetAsBox(1.0f, 0.1f, b2Vec2(0.0f, -0.9f), 0.0f);
			b5->CreateShape(&sd);

			sd.SetAsBox(0.1f, 1.0f, b2Vec2(-0.9f, 0.0f), 0.0f);
			b5->CreateShape(&sd);

			sd.SetAsBox(0.1f, 1.0f, b2Vec2(0.9f, 0.0f), 0.0f);
			b5->CreateShape(&sd);

			b5->SetMassFromShapes();
		}

		anchor.Set(6.0f, 2.0f);
		jd.Initialize(b1, b5, anchor);
		m_world->CreateJoint(&jd);

		b2Body* b6;
		{
			b2PolygonDef sd;
			sd.SetAsBox(1.0f, 0.1f);
			sd.density = 30.0f;
			sd.friction = 0.2f;

			b2BodyDef bd;
			bd.position.Set(6.5f, 4.1f);
			b6 = m_world->CreateBody(&bd);
			b6->CreateShape(&sd);
			b6->SetMassFromShapes();
		}

		anchor.Set(7.5f, 4.0f);
		jd.Initialize(b5, b6, anchor);
		m_world->CreateJoint(&jd);

		b2Body* b7;
		{
			b2PolygonDef sd;
			sd.SetAsBox(0.1f, 1.0f);
			sd.density = 10.0f;

			b2BodyDef bd;
			bd.position.Set(7.4f, 1.0f);

			b7 = m_world->CreateBody(&bd);
			b7->CreateShape(&sd);
			b7->SetMassFromShapes();
		}

		b2DistanceJointDef djd;
		djd.body1 = b3;
		djd.body2 = b7;
		djd.localAnchor1.Set(6.0f, 0.0f);
		djd.localAnchor2.Set(0.0f, -1.0f);
		b2Vec2 d = djd.body2->GetWorldPoint(djd.localAnchor2) - djd.body1->GetWorldPoint(djd.localAnchor1);
		djd.length = d.Length();
		m_world->CreateJoint(&djd);

		{
			b2CircleDef sd;
			sd.radius = 0.2f;
			sd.density = 10.0f;

			for (int32 i = 0; i < 4; ++i)
			{
				b2BodyDef bd;
				bd.position.Set(5.9f + 2.0f * sd.radius * i, 2.4f);
				b2Body* body = m_world->CreateBody(&bd);
				body->CreateShape(&sd);
				body->SetMassFromShapes();
			}
		}
	}

	static Test* Create()
	{
		return new Dominos;
	}
};

#endif
