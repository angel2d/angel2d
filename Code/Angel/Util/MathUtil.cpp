//////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2008-2014, Shane Liesegang
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions are met:
// 
//     * Redistributions of source code must retain the above copyright 
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright 
//       notice, this list of conditions and the following disclaimer in the 
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of the copyright holder nor the names of any 
//       contributors may be used to endorse or promote products derived from 
//       this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
// POSSIBILITY OF SUCH DAMAGE.
//////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "../Util/MathUtil.h"

#include "../Infrastructure/World.h"
#include "../Infrastructure/Camera.h"

#include <math.h>
#include <time.h>

const float MathUtil::E = 2.718282f;
const float MathUtil::Log10E = 0.4342945f;
const float MathUtil::Log2E = 1.442695f;
const float MathUtil::Pi = 3.141593f;
const float MathUtil::PiOver2 = 1.570796f;
const float MathUtil::PiOver4 = 0.7853982f;
const float MathUtil::TwoPi = 6.283185f;
const float MathUtil::MaxFloat = 3.402823E+38f;
const float MathUtil::MinFloat = -3.402823E+38f;
const float MathUtil::Epsilon = 0.000001f;


float MathUtil::ToDegrees(float radians)
{
	return (radians * 57.29578f);
}

float MathUtil::ToRadians(float degrees)
{
	return (degrees * 0.01745329f);
}

Vector2 MathUtil::VectorFromAngle(float angle_in_degrees)
{
	return Vector2(cos(ToRadians(angle_in_degrees)), sin(ToRadians(angle_in_degrees)));
}

float MathUtil::AngleFromVector(const Vector2& v1)
{
	Vector2 localVector = v1;

	localVector.Normalize();
	return atan2( localVector.Y, localVector.X );	
}

float MathUtil::AngleFromVectors(const Vector2& v1, const Vector2& v2)
{
	return atan2(v1.Y, v1.X) - atan2(v2.Y, v2.X);
}


int MathUtil::RoundToInt(double x)
{
	return ((int)(floor(x+0.5)));
}

int MathUtil::RandomInt(int maximum)
{
	static bool firstTime = true;
	if (firstTime) 
	{
		firstTime = false;
		srand((int)time(NULL));
	}
	if (maximum <= 0) 
	{
		return 0;
	}
	return (rand() % maximum);
}

int MathUtil::RandomIntInRange(int min, int max)
{
	return RandomInt(max-min) + min;
}

int MathUtil::RandomIntWithError(int target, int error)
{
	return RandomIntInRange(target-error, target+error);
}

float MathUtil::RandomFloat(float maximum)
{
	const float bigNumber = 10000.0f;
	float randFloat = (float)RandomInt((int)bigNumber);
	randFloat = randFloat/bigNumber;
	return randFloat*maximum;
}

float MathUtil::RandomFloatInRange(float min, float max)
{
	return RandomFloat(max-min) + min;
}

float MathUtil::RandomFloatWithError(float target, float error)
{
	return RandomFloatInRange(target-error, target+error);
}

bool MathUtil::RandomBool()
{
	return MathUtil::RandomInt(2) > 0;
}

Vector2 MathUtil::RandomVector()
{
	return RandomVector(Vector2(1.0f));//.Normalize();
}

Vector2 MathUtil::RandomVector(const Vector2& maxValues)
{
	return RandomVector(Vector2::Zero, maxValues);
}

Vector2 MathUtil::RandomVector(const Vector2& minValues, const Vector2& maxValues)
{
	return Vector2(RandomFloatInRange(minValues.X, maxValues.X), RandomFloatInRange(minValues.Y, maxValues.Y));
}

bool __poissonFieldCheck(Vector2List list, Vector2 point, float minDist)
{
	for (int i=0; i < list.size(); i++) {
		if (Vector2::DistanceSquared(list[i], point) < minDist)
		{
			return true;
		}
	}
	return false;
}

Vector2List MathUtil::RandomPointField(int numPoints, const Vector2& min, const Vector2& max, float minDistance)
{
	Vector2List forReturn;
	
	int tryLimit = 100;
	float reductionFactor = 0.75f;
	
	int tries;
	Vector2 newPoint;
	
	while (forReturn.size() < numPoints)
	{
		tries = 0;
		
		do
		{
			newPoint = RandomVector(min, max);
			tries++;
		}
		while (__poissonFieldCheck(forReturn, newPoint, minDistance) && tries < tryLimit);

		if (tries < tryLimit)
		{
			forReturn.push_back(newPoint);
		}
		else 
		{
			minDistance *= reductionFactor;
		}
	}
	
	return forReturn;
}

bool MathUtil::FuzzyEquals(float value1, float value2, float epsilon)
{
	float a = value1 - value2;
	if (fabs(a) < epsilon)
	{
		return true;
	}
	return false;
}


bool MathUtil::FuzzyEquals(const Vector2& v1, const Vector2& v2, float epsilon)
{
	if ( (MathUtil::FuzzyEquals(v1.X, v2.X, epsilon)) && (MathUtil::FuzzyEquals(v1.Y, v2.Y, epsilon)) )
	{
		return true;
	}
	return false;
}

Vector2 MathUtil::ScreenToWorld(const Vec2i& screenCoordinates)
{
	return MathUtil::ScreenToWorld(screenCoordinates.X, screenCoordinates.Y);
}

Vector2 MathUtil::ScreenToWorld(int x, int y)
{
	if (theWorld.IsHighResScreen())
	{
		x *= 2;
		y *= 2;
	}
	
	Vector2 worldDimensions = GetWorldDimensions();

	float worldX = ( ((float)x / (float)theCamera.GetWindowWidth()) - 0.5f ) * worldDimensions.X;
	float worldY = ( 0.5f - ((float)y / (float)theCamera.GetWindowHeight()) ) * worldDimensions.Y;
	
	Vector2 camPos = theCamera.GetPosition();
	Vector2 forReturn(worldX + camPos.X, worldY + camPos.Y);
	
	return Vector2::Rotate(forReturn, MathUtil::ToRadians(-theCamera.GetRotation()));
}

Vector2 MathUtil::WorldToScreen(const Vector2& worldCoordinates)
{
	Vector2 startingWorldCoords(worldCoordinates.X, worldCoordinates.Y);
	Vector2 camPos = theCamera.GetPosition();
	startingWorldCoords.X -= camPos.X;
	startingWorldCoords.Y -= camPos.Y;
	startingWorldCoords = Vector2::Rotate(startingWorldCoords, ToRadians(theCamera.GetRotation()));
	
	Vector2 worldDimensions = GetWorldDimensions();
	
	float screenX = theCamera.GetWindowWidth() * ( (startingWorldCoords.X / worldDimensions.X) + 0.5f );
	float screenY = theCamera.GetWindowHeight() - (theCamera.GetWindowHeight() * ( 0.5f + (startingWorldCoords.Y / worldDimensions.Y) ));
	
	return Vector2(screenX, screenY);
}

Vector2 MathUtil::WorldToScreen(float x, float y)
{
	return WorldToScreen(Vector2(x, y));
}

Vector2 MathUtil::GetWorldDimensions()
{
	float worldWidth, worldHeight;
	int screenWidth = theCamera.GetWindowWidth();
	int screenHeight = theCamera.GetWindowHeight();
	float aspect = (float)screenWidth / (float)screenHeight;
	if (screenWidth > screenHeight)
	{
		//window is wider than it is tall; radius goes with height
		worldHeight = theCamera.GetViewRadius() * 2.0f;
		worldWidth = worldHeight * aspect;
	}
	else
	{
		//window is taller than it is wide; radius goes with width
		worldWidth = theCamera.GetViewRadius() * 2.0f;
		worldHeight = worldWidth / aspect;
	}
	
	return Vector2(worldWidth, worldHeight); 
}

float MathUtil::PixelsToWorldUnits(float pixels)
{
	float ratio = theCamera.GetWindowWidth() / GetWorldDimensions().X; 
	
	return pixels / ratio; 
}

float MathUtil::WorldUnitsToPixels(float worldUnits)
{
	float ratio = theCamera.GetWindowWidth() / GetWorldDimensions().X; 
	
	return worldUnits * ratio; 
}

MathUtil::AABBSplittingAxis MathUtil::GetMajorAxis(const BoundingBox& source)
{
	AABBSplittingAxis retVal = AA_X;
	float maxAxis = source.Max.X - source.Min.X;

	float yAxis = source.Max.Y - source.Min.Y;
	if (yAxis > maxAxis)
	{
		retVal = AA_Y;
		maxAxis = yAxis;
	}

	return retVal;
}

void MathUtil::SplitBoundingBox(const BoundingBox& source, AABBSplittingAxis axis, BoundingBox& LHS, BoundingBox& RHS)
{
	LHS = source;
	RHS = source;

	switch (axis)
	{
	case AA_X:
		LHS.Max.X = Lerp(LHS.Min.X, LHS.Max.X, 0.5f);
		RHS.Min.X = LHS.Max.X;
		break;
	case AA_Y:
		LHS.Max.Y = Lerp(LHS.Min.Y, LHS.Max.Y, 0.5f);
		RHS.Min.Y = LHS.Max.Y;
		break;
	}
}

float MathUtil::DeltaAngle(float A1, float A2)
{
	// Find the difference
	float Delta = A2 - A1;

	// If change is larger than PI
	if(Delta > Pi)
	{
		// Flip to negative equivalent
		Delta = Delta - (TwoPi);
	}
	else if(Delta < -Pi)
	{
		// Otherwise, if change is smaller than -PI
		// Flip to positive equivalent
		Delta = Delta + (TwoPi);
	}

	// Return delta in [-PI,PI] range
	return Delta;
}

float MathUtil::VectorDeltaAngle(const Vector2& v1, const Vector2& v2)
{
	return acos( Vector2::Dot(v1, v2) );
}

