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

#ifndef TIME_OF_IMPACT_H
#define TIME_OF_IMPACT_H

class TimeOfImpact : public Test
{
public:
	TimeOfImpact()
	{
		{
			b2PolygonDef sd;
			sd.density = 0.0f;

			sd.SetAsBox(0.1f, 10.0f, b2Vec2(10.0f, 0.0f), 0.0f);

			b2BodyDef bd;
			bd.position.Set(0.0f, 20.0f);
			bd.angle = 0.0f;
			m_body1 = m_world->CreateBody(&bd);
			m_shape1 = m_body1->CreateShape(&sd);
		}

		{
			b2PolygonDef sd;
			sd.SetAsBox(0.25f, 0.25f);
			sd.density = 1.0f;

			b2BodyDef bd;
			bd.position.Set(9.6363468f, 28.050615f);
			bd.angle = 1.6408679f;
			m_body2 = m_world->CreateBody(&bd);
			m_shape2 = (b2PolygonShape*)m_body2->CreateShape(&sd);
			m_body2->SetMassFromShapes();
		}
	}

	~TimeOfImpact()
	{
	}

	static Test* Create()
	{
		return new TimeOfImpact;
	}

	void Step(Settings* settings)
	{
		settings->pause = 1;
		Test::Step(settings);
		settings->pause = 0;

		b2Sweep sweep1;
		sweep1.c0.Set(0.0f, 20.0f);
		sweep1.a0 = 0.0f;
		sweep1.c = sweep1.c0;
		sweep1.a = sweep1.a0;
		sweep1.t0 = 0.0f;
		sweep1.localCenter = m_body1->GetLocalCenter();

		b2Sweep sweep2;
		sweep2.c0.Set(9.6363468f, 28.050615f);
		sweep2.a0 = 1.6408679f;
		sweep2.c = sweep2.c0 + b2Vec2(-0.075121880f, 0.27358246f);
		sweep2.a = sweep2.a0 - 10.434675f;
		sweep2.t0 = 0.0f;
		sweep2.localCenter = m_body2->GetLocalCenter();

		float32 toi = b2TimeOfImpact(m_shape1, sweep1, m_shape2, sweep2);

		DrawString(5, m_textLine, "toi = %g", (float) toi);
		m_textLine += 15;

		b2XForm xf2;
		sweep2.GetXForm(&xf2, toi);
		int32 vertexCount = m_shape2->GetVertexCount();
		b2Vec2 vertices[b2_maxPolygonVertices];
		const b2Vec2* localVertices;
		
		localVertices = m_shape2->GetVertices();
		for (int32 i = 0; i < vertexCount; ++i)
		{
			vertices[i] = b2Mul(xf2, localVertices[i]);
		}
		m_debugDraw.DrawPolygon(vertices, vertexCount, b2Color(0.5f, 0.7f, 0.9f));

		localVertices = m_shape2->GetCoreVertices();
		for (int32 i = 0; i < vertexCount; ++i)
		{
			vertices[i] = b2Mul(xf2, localVertices[i]);
		}
		m_debugDraw.DrawPolygon(vertices, vertexCount, b2Color(0.5f, 0.7f, 0.9f));
	}

	b2Body* m_body1;
	b2Body* m_body2;
	b2Shape* m_shape1;
	b2PolygonShape* m_shape2;
};

#endif
