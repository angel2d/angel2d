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

#ifndef APPLY_FORCE_H
#define APPLY_FORCE_H

class ApplyForce : public Test
{
public:
	ApplyForce()
	{
		m_world->SetGravity(b2Vec2(0.0f, 0.0f));

		const float32 k_restitution = 0.4f;

		{
			b2BodyDef bd;
			bd.position.Set(0.0f, 20.0f);
			b2Body* ground = m_world->CreateBody(&bd);

			b2PolygonDef sd;
			sd.density = 0.0f;
			sd.restitution = k_restitution;

			sd.SetAsBox(0.2f, 20.0f, b2Vec2(-20.0f, 0.0f), 0.0f);
			ground->CreateShape(&sd);

			sd.SetAsBox(0.2f, 20.0f, b2Vec2(20.0f, 0.0f), 0.0f);
			ground->CreateShape(&sd);

			sd.SetAsBox(0.2f, 20.0f, b2Vec2(0.0f, -20.0f), 0.5f * b2_pi);
			ground->CreateShape(&sd);

			sd.SetAsBox(0.2f, 20.0f, b2Vec2(0.0f, 20.0f), -0.5f * b2_pi);
			ground->CreateShape(&sd);
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

			b2BodyDef bd;
			bd.angularDamping = 2.0f;
			bd.linearDamping = 0.1f;

			bd.position.Set(0.0f, 1.05f);
			bd.angle = b2_pi;
			m_body = m_world->CreateBody(&bd);
			m_body->CreateShape(&sd1);
			m_body->CreateShape(&sd2);
			m_body->SetMassFromShapes();
		}
	}

	void Keyboard(unsigned char key)
	{
		switch (key)
		{
		case 'w':
			{
				b2Vec2 f = m_body->GetWorldVector(b2Vec2(0.0f, -200.0f));
				b2Vec2 p = m_body->GetWorldPoint(b2Vec2(0.0f, 2.0f));
				m_body->ApplyForce(f, p);
			}
			break;

		case 'a':
			{
				m_body->ApplyTorque(20.0f);
			}
			break;

		case 'd':
			{
				m_body->ApplyTorque(-20.0f);
			}
			break;
		}
	}

	static Test* Create()
	{
		return new ApplyForce;
	}

	b2Body* m_body;
};

#endif
