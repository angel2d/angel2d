//////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2008-2009, Shane J. M. Liesegang
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

#include "../AI/BoundingShapes.h"

#include "../Infrastructure/Common.h"
#include "../Util/MathUtil.h"
#include "../AI/Ray2.h"


BoundingBox::BoundingBox(const Vector2& min, const Vector2& max)
: Min(min)
, Max(max)
{}

/*static*/ BoundingBox BoundingBox::CreateMerged(const BoundingBox& original, const BoundingBox& additional)
{
	return BoundingBox(Vector2::Min(original.Min, additional.Min), Vector2::Max(original.Max, additional.Max));

}

Vector2 BoundingBox::Centroid()
{
	return Min + (Max-Min)/2.f;
}


void BoundingBox::GetCorners(Vector2 corners[])
{
	corners[0] = Vector2(Min.X, Min.Y);
	corners[1] = Vector2(Min.X, Max.Y);
	corners[2] = Vector2(Max.X, Max.Y);
	corners[3] = Vector2(Max.X, Min.Y);
}

/*static*/ BoundingBox BoundingBox::CreateFromPoints(Vector2 points[], int count)
{
	if( count < 1 )
		return BoundingBox(Vector2::Zero, Vector2::Zero );

	BoundingBox retVal = BoundingBox( Vector2(MathUtil::MaxFloat), Vector2(MathUtil::MinFloat) );
	for( int i = 0 ; i < count; ++i )
	{
		Vector2& compare = points[i];
		retVal.Min = Vector2::Min( retVal.Min, compare );
		retVal.Max = Vector2::Max( retVal.Max, compare );
	}
	return retVal;
}

bool BoundingBox::Intersects(const BoundingBox& box)
{
	if ((Max.X < box.Min.X) || (Min.X > box.Max.X))
	{
		return false;
	}
	if ((Max.Y < box.Min.Y) || (Min.Y > box.Max.Y))
	{
		return false;
	}

	return true;
}

bool BoundingBox::Intersects(const Ray2& ray, float& distanceAlongRay )
{
	distanceAlongRay = 0.f;
	float maxValue = MathUtil::MaxFloat;
	if (MathUtil::Abs(ray.Direction.X) < MathUtil::Epsilon)
	{
		if ((ray.Position.X < Min.X) || (ray.Position.X > Max.X))
		{
			return false;
		}
	}
	else
	{
		float invMag = 1.f / ray.Direction.X;
		float minProj = (Min.X - ray.Position.X) * invMag;
		float maxProj = (Max.X - ray.Position.X) * invMag;
		if (minProj > maxProj)
		{
			float temp = minProj;
			minProj = maxProj;
			maxProj = temp;
		}
		distanceAlongRay = MathUtil::Max(minProj, distanceAlongRay);
		maxValue = MathUtil::Min(maxProj, maxValue);
		if (distanceAlongRay > maxValue)
		{
			return false;
		}
	}

	if (MathUtil::Abs(ray.Direction.Y) < MathUtil::Epsilon)
	{
		if ((ray.Position.Y < Min.Y) || (ray.Position.Y > Max.Y))
		{
			return false;
		}
	}
	else
	{
		float invMag = 1.f / ray.Direction.Y;
		float minProj = (Min.Y - ray.Position.Y) * invMag;
		float maxProj = (Max.Y - ray.Position.Y) * invMag;
		if (minProj > maxProj)
		{
			float temp = minProj;
			minProj = maxProj;
			maxProj = temp;
		}
		distanceAlongRay = MathUtil::Max(minProj, distanceAlongRay);
		maxValue = MathUtil::Min(maxProj, maxValue);
		if (distanceAlongRay > maxValue)
		{
			return false;
		}
	}

	return true;
}


ContainmentType BoundingBox::Contains(const BoundingBox& box)
{
	if ((Max.X < box.Min.X) || (Min.X > box.Max.X))
	{
		return Disjoint;
	}
	if ((Max.Y < box.Min.Y) || (Min.Y > box.Max.Y))
	{
		return Disjoint;
	}
	if ((((Min.X <= box.Min.X) && (box.Max.X <= Max.X)) && ((Min.Y <= box.Min.Y) && (box.Max.Y <= Max.Y))))
	{
		return Within;
	}
	return ::Intersects;
}

bool BoundingBox::Contains(const Vector2& point)
{
	if ((((Min.X <= point.X) && (point.X <= Max.X)) && ((Min.Y <= point.Y) && (point.Y <= Max.Y))))
	{
		return true;
	}
	return false;
}

void BoundingBox::RenderOutline()
{
	glBegin(GL_LINES);
	{
		glVertex2f(Min.X, Min.Y);
		glVertex2f(Min.X, Max.Y);

		glVertex2f(Min.X, Max.Y);
		glVertex2f(Max.X, Max.Y);

		glVertex2f(Max.X, Max.Y);
		glVertex2f(Max.X, Min.Y);

		glVertex2f(Max.X, Min.Y);
		glVertex2f(Min.X, Min.Y);
	}
	glEnd();
}

void BoundingBox::RenderBox()
{
	glBegin(GL_QUADS);
	{

		glVertex2f(Max.X, Max.Y);
		glVertex2f(Min.X, Max.Y);
		glVertex2f(Min.X, Min.Y);
		glVertex2f(Max.X, Min.Y);
	}
	glEnd();
}



bool operator ==(const BoundingBox& a, const BoundingBox& b)
{
	return a.Max == b.Max && a.Min == b.Min;
}

bool operator !=(const BoundingBox& a, const BoundingBox& b)
{
	return !operator==(a, b);
}

