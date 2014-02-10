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

Vector2 BoundingBox::Centroid() const
{
	return Min + (Max-Min)/2.f;
}

Vector2 BoundingBox::HalfLength() const
{
	return (Max-Min)/2.f;
}


void BoundingBox::GetCorners(Vector2 corners[]) const
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

bool BoundingBox::Intersects(const BoundingBox& box) const
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

bool BoundingBox::Intersects(const Ray2& ray, float& distanceAlongRay) const
{
	float distNear = MathUtil::MinFloat;
	float distFar = MathUtil::MaxFloat;

	distanceAlongRay = 0.f;

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
		
		if (minProj > distNear)
		{
			distNear = minProj;
		}
		
		if (maxProj < distFar)
		{
			distFar = maxProj;
		}
		
		if (distNear > distFar || distFar < 0.0)
		{
			return false;	// ray missed 
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
		
		if (minProj > distNear)
		{
			distNear = minProj;
		}
		
		if (maxProj < distFar)
		{
			distFar = maxProj;
		}
		
		if (distNear > distFar || distFar < 0.0)
		{
			return false;	// ray missed 
		}
	}
	
	if (distNear > 0.0f)
	{
		distanceAlongRay = distNear;
	}
	else
	{
		distanceAlongRay = distFar;
	}
	
	return true;
}

bool BoundingBox::Intersects(const Vector2& point, float radius) const
{
	int xZone = point.X < ( Min.X ) ? 0 : ( point.X > ( Max.X ) ? 2 : 1 );
	int yZone = point.Y < ( Min.Y ) ? 0 : ( point.Y > ( Max.Y ) ? 2 : 1 );

	int zone = xZone + 3*yZone;

	Vector2 halfLen(HalfLength());
	Vector2 center(halfLen+Min);

	bool bIntersects = false;
	switch ( zone ) 
	{
		// top and bottom side zones
		// check vertical distance between centers
		case 1:
		case 7:
			{
				float distY = fabs( point.Y - center.Y );
				if ( distY <= ( radius + halfLen.Y ) )
				{
					bIntersects = true;
				}
			}
			break;
		// left and right side zones. check distance between centers
		// check horizontal distance between centers
		case 3:
		case 5:
			{
				float distX = fabs( point.X - center.X );
				if ( distX <= ( radius + halfLen.X ) )
				{
					bIntersects = true;
				}
			}
			break;
		// inside zone. collision for sure
		case 4:
			bIntersects = true;
			break;
		// corner zone. 
		// get the corner and check if inside the circle
		default:
			{
				float cornerX = ( zone == 0 || zone == 6 ) ? Min.X : Max.X;
				float cornerY = ( zone == 0 || zone == 2 ) ? Min.Y : Max.Y;

				float distX = cornerX - point.X;
				float distY = cornerY - point.Y;
				float squaredist = distX*distX + distY*distY;

				if (squaredist <= radius* radius )
				{
					// corner is inside circle
					bIntersects = true;
				}
			}
			break;
	}

	return bIntersects;
}


ContainmentType BoundingBox::Contains(const BoundingBox& box) const
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

bool BoundingBox::Contains(const Vector2& point) const
{
	if ((((Min.X <= point.X) && (point.X <= Max.X)) && ((Min.Y <= point.Y) && (point.Y <= Max.Y))))
	{
		return true;
	}
	return false;
}

void BoundingBox::RenderOutline() const
{
	float vertices[] = {
		Min.X, Min.Y,
		Min.X, Max.Y,
		Max.X, Max.Y,
		Max.X, Min.Y,
	};
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, vertices);
	glDrawArrays(GL_LINE_LOOP, 0, 4);
}

void BoundingBox::RenderBox() const
{
	float vertices[] = {
		Max.X, Max.Y,
		Min.X, Max.Y,
		Max.X, Min.Y,
		Min.X, Min.Y,
	};
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, vertices);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}



bool operator ==(const BoundingBox& a, const BoundingBox& b)
{
	return a.Max == b.Max && a.Min == b.Min;
}

bool operator !=(const BoundingBox& a, const BoundingBox& b)
{
	return !operator==(a, b);
}

