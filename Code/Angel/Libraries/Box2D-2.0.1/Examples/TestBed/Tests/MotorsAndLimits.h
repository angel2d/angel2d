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

#ifndef MOTORS_AND_LIMITS_H
#define MOTORS_AND_LIMITS_H

class MotorsAndLimits : public Test
{
public:
	MotorsAndLimits()
	{
		b2Body* ground = NULL;
		{
			b2PolygonDef sd;
			sd.SetAsBox(50.0f, 10.0f);

			b2BodyDef bd;
			bd.position.Set(0.0f, -10.0f);
			ground = m_world->CreateBody(&bd);
			ground->CreateShape(&sd);
		}

		{
			b2PolygonDef sd;
			sd.SetAsBox(2.0f, 0.5f);
			sd.density = 5.0f;
			sd.friction = 0.05f;

			b2BodyDef bd;

			b2RevoluteJointDef rjd;

			b2Body* body = NULL;
			b2Body* prevBody = ground;
			const float32 y = 8.0f;

			bd.position.Set(3.0f, y);
			body = m_world->CreateBody(&bd);
			body->CreateShape(&sd);
			body->SetMassFromShapes();

			rjd.Initialize(prevBody, body, b2Vec2(0.0f, y));
			rjd.motorSpeed = 1.0f * b2_pi;
			rjd.maxMotorTorque = 10000.0f;
			rjd.enableMotor = true;
			
			m_joint1 = (b2RevoluteJoint*)m_world->CreateJoint(&rjd);

			prevBody = body;

			bd.position.Set(9.0f, y);
			body = m_world->CreateBody(&bd);
			body->CreateShape(&sd);
			body->SetMassFromShapes();

			rjd.Initialize(prevBody, body, b2Vec2(6.0f, y));
			rjd.motorSpeed = 0.5f * b2_pi;
			rjd.maxMotorTorque = 2000.0f;
			rjd.enableMotor = true;
			rjd.lowerAngle = - 0.5f * b2_pi;
			rjd.upperAngle = 0.5f * b2_pi;
			rjd.enableLimit = true;

			m_joint2 = (b2RevoluteJoint*)m_world->CreateJoint(&rjd);

			bd.position.Set(-10.0f, 10.0f);
			bd.angle = 0.5f * b2_pi;
			body = m_world->CreateBody(&bd);
			body->CreateShape(&sd);
			body->SetMassFromShapes();

			b2PrismaticJointDef pjd;
			pjd.Initialize(ground, body, b2Vec2(-10.0f, 10.0f), b2Vec2(1.0f, 0.0f));
			pjd.motorSpeed = 10.0f;
			pjd.maxMotorForce = 1000.0f;
			pjd.enableMotor = true;
			pjd.lowerTranslation = 0.0f;
			pjd.upperTranslation = 20.0f;
			pjd.enableLimit = true;

			m_joint3 = (b2PrismaticJoint*)m_world->CreateJoint(&pjd);
		}
	}

	void Keyboard(unsigned char key)
	{
		switch (key)
		{
		case 'l':
			m_joint2->EnableLimit(!m_joint2->IsLimitEnabled());
			m_joint3->EnableLimit(!m_joint3->IsLimitEnabled());
			m_joint2->GetBody1()->WakeUp();
			m_joint3->GetBody2()->WakeUp();
			break;

		case 'm':
			m_joint1->EnableMotor(!m_joint1->IsMotorEnabled());
			m_joint2->EnableMotor(!m_joint2->IsMotorEnabled());
			m_joint3->EnableMotor(!m_joint3->IsMotorEnabled());
			m_joint2->GetBody1()->WakeUp();
			m_joint3->GetBody2()->WakeUp();
			break;

		case 'p':
			m_joint3->GetBody2()->WakeUp();
			m_joint3->SetMotorSpeed(-m_joint3->GetMotorSpeed());
			break;
		}
	}

	void Step(Settings* settings)
	{
		Test::Step(settings);
		DrawString(5, m_textLine, "Keys: (l) limits, (m) motors, (p) prismatic speed");
		m_textLine += 15;
		float32 torque1 = m_joint1->GetMotorTorque();
		float32 torque2 = m_joint2->GetMotorTorque();
		float32 force3 = m_joint3->GetMotorForce();
		DrawString(5, m_textLine, "Motor Torque = %4.0f, %4.0f : Motor Force = %4.0f", (float) torque1, (float) torque2, (float) force3);
		m_textLine += 15;
	}

	static Test* Create()
	{
		return new MotorsAndLimits;
	}

	b2RevoluteJoint* m_joint1;
	b2RevoluteJoint* m_joint2;
	b2PrismaticJoint* m_joint3;
};

#endif
