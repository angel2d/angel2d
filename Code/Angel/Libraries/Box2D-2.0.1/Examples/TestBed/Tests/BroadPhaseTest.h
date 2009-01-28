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

#ifndef BROAD_PHASE_TEST_H
#define BROAD_PHASE_TEST_H

#include "../Framework/Test.h"
#include "../Framework/Render.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include "freeglut/GL/glut.h"
#endif

const int32 k_actorCount = 256;
const float32 k_extent = 15.0f;

class BroadPhaseTest;

struct Actor
{
	b2AABB aabb;
	int32 overlapCount;
	uint16 proxyId;
};

class Callback : public b2PairCallback
{
public:
	void* PairAdded(void* proxyUserData1, void* proxyUserData2);

	void PairRemoved(void* proxyUserData1, void* proxyUserData2, void* pairUserData);

	BroadPhaseTest* m_test;
};

class BroadPhaseTest : public Test
{
public:
	static Test* Create();

	BroadPhaseTest();
	~BroadPhaseTest();

	float GetExtent() { return 1.5f * k_extent; }
	void Step(Settings* settings);

	void Keyboard(unsigned char key);

private:

	friend class Callback;

	void CreateProxy();
	void DestroyProxy();
	void MoveProxy();
	void Action();
	void Validate();

	int32 m_overlapCount;
	int32 m_overlapCountExact;

	Callback m_callback;
	b2BroadPhase* m_broadPhase;
	Actor m_actors[k_actorCount];
	bool m_overlaps[k_actorCount][k_actorCount];
	bool m_automated;
	int32 m_stepCount;
};

#endif
