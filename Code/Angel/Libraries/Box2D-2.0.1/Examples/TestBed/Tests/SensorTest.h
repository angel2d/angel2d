/*
* Copyright (c) 2008 Erin Catto http://www.gphysics.com
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

#ifndef SENSOR_TEST_H
#define SENSOR_TEST_H

// This is used to test sensor shapes.
class SensorTest : public Test
{
public:

	SensorTest()
	{
		{
			b2BodyDef bd;
			bd.position.Set(0.0f, -10.0f);

			b2Body* ground = m_world->CreateBody(&bd);

			b2PolygonDef sd;
			sd.SetAsBox(50.0f, 10.0f);
			ground->CreateShape(&sd);

			b2CircleDef cd;
			cd.isSensor = true;
			cd.radius = 5.0f;
			cd.localPosition.Set(0.0f, 20.0f);
			m_sensor = ground->CreateShape(&cd);
		}

		{
			b2CircleDef sd;
			sd.radius = 1.0f;
			sd.density = 1.0f;

			for (int32 i = 0; i < 7; ++i)
			{
				b2BodyDef bd;
				bd.position.Set(-10.0f + 3.0f * i, 20.0f);

				b2Body* body = m_world->CreateBody(&bd);

				body->CreateShape(&sd);
				body->SetMassFromShapes();
			}
		}
	}

	void Step(Settings* settings)
	{
		Test::Step(settings);

		// Traverse the contact results. Apply a force on shapes
		// that overlap the sensor.
		for (int32 i = 0; i < m_pointCount; ++i)
		{
			ContactPoint* point = m_points + i;

			if (point->state == 2)
			{
				continue;
			}

			b2Shape* shape1 = point->shape1;
			b2Shape* shape2 = point->shape2;
			b2Body* other;

			if (shape1 == m_sensor)
			{
				other = shape2->GetBody();
			}
			else if (shape2 == m_sensor)
			{
				other = shape1->GetBody();
			}
			else
			{
				continue;
			}

			b2Body* ground = m_sensor->GetBody();

			b2CircleShape* circle = (b2CircleShape*)m_sensor;
			b2Vec2 center = ground->GetWorldPoint(circle->GetLocalPosition());

			b2Vec2 d = center - point->position;
			if (d.LengthSquared() < FLT_EPSILON * FLT_EPSILON)
			{
				continue;
			}

			d.Normalize();
			b2Vec2 F = 100.0f * d;
			other->ApplyForce(F, point->position);
		}
	}

	static Test* Create()
	{
		return new SensorTest;
	}

	b2Shape* m_sensor;
};

#endif
