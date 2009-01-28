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

#ifndef SHAPE_EDITING_H
#define SHAPE_EDITING_H

class ShapeEditing : public Test
{
public:

	ShapeEditing()
	{
		{
			b2PolygonDef sd;
			sd.SetAsBox(50.0f, 10.0f);

			b2BodyDef bd;
			bd.position.Set(0.0f, -10.0f);

			b2Body* ground = m_world->CreateBody(&bd);
			ground->CreateShape(&sd);
		}

		b2BodyDef bodydef;
		bodydef.position.Set(0.0f, 10.0f);
		m_body = m_world->CreateBody(&bodydef);

		b2PolygonDef sd;
		sd.SetAsBox(4.0f, 4.0f, b2Vec2(0.0f, 0.0f), 0.0f);
		sd.density = 10.0f;
		m_shape1 = m_body->CreateShape(&sd);
		m_body->SetMassFromShapes();

		m_shape2 = NULL;
	}

	void Keyboard(unsigned char key)
	{
		switch (key)
		{
		case 'c':
			if (m_shape2 == NULL)
			{
				b2CircleDef sd;
				sd.radius = 3.0f;
				sd.density = 10.0f;
				sd.localPosition.Set(0.5f, -4.0f);
				m_shape2 = m_body->CreateShape(&sd);
				m_body->SetMassFromShapes();
				m_body->WakeUp();
			}
			break;

		case 'd':
			if (m_shape2 != NULL)
			{
				m_body->DestroyShape(m_shape2);
				m_shape2 = NULL;
				m_body->SetMassFromShapes();
				m_body->WakeUp();
			}
			break;
		}
	}


	void Step(Settings* settings)
	{
		Test::Step(settings);
		DrawString(5, m_textLine, "Press: (c) create a shape, (d) destroy a shape.");
		m_textLine += 15;
	}

	static Test* Create()
	{
		return new ShapeEditing;
	}

	b2Body* m_body;
	b2Shape* m_shape1;
	b2Shape* m_shape2;
};

#endif
