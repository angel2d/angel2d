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
#include "../Actors/GridActor.h"

#include "../Infrastructure/Common.h"

GridActor::GridActor()
{
	//yay for magic numbers! (default parameters of the grid)
	_lineColor = Color(.76f, .83f, 1.0f);
	_axisColor = Color(1.0f, .41f, .6f);
	_interval = 1.0f;
	_minCoord = Vector2(-20.0f, -20.0f);
	_maxCoord = Vector2(20.0f, 20.0f);

	RecalculatePoints();
}

GridActor::GridActor(const Color& lines, const Color& axis, float interval, const Vector2& minCoord, const Vector2& maxCoord)
{
	_lineColor = lines;
	_axisColor = axis;
	_interval = interval;
	_minCoord = minCoord;
	_maxCoord = maxCoord;

	RecalculatePoints();
}

void GridActor::SetLineColor(const Color& lineCol)
{
	_lineColor = lineCol;
}

const Color& GridActor::GetLineColor() const
{
	return _lineColor;
}

void GridActor::SetAxisColor(const Color& axisCol)
{
	_axisColor = axisCol;
}

const Color& GridActor::GetAxisColor() const
{
	return _axisColor;
}

void GridActor::SetInterval(float interval)
{
	_interval = interval;
}

const float GridActor::GetInterval() const
{
	return _interval;
}

void GridActor::SetMinCoord(const Vector2& minCoord)
{
	_minCoord = minCoord;
	RecalculatePoints();
}

const Vector2 GridActor::GetMinCoord() const
{
	return _minCoord;
}

void GridActor::SetMaxCoord(const Vector2& maxCoord)
{
	_maxCoord = maxCoord;
	RecalculatePoints();
}

const Vector2 GridActor::GetMaxCoord() const
{
	return _maxCoord;
}

void GridActor::RecalculatePoints()
{
	_points.clear();

	float i;
	for (i = _minCoord.X; i < _maxCoord.X; i += _interval)
	{
		_points.push_back(i);
		_points.push_back(_minCoord.Y);
		_points.push_back(i);
		_points.push_back(_maxCoord.Y);
	}
	for (i = _minCoord.Y; i < _maxCoord.Y; i += _interval)
	{
		_points.push_back(_minCoord.X);
		_points.push_back(i);
		_points.push_back(_maxCoord.X);
		_points.push_back(i);
	}

	_axes[0] = _minCoord.X;
	_axes[1] = 0.0f;
	_axes[2] = _maxCoord.X;
	_axes[3] = 0.0f;
	_axes[4] = 0.0f;
	_axes[5] = _minCoord.Y;
	_axes[6] = 0.0f;
	_axes[7] = _maxCoord.Y;
}

void GridActor::Render()
{
	// lines
	glEnableClientState(GL_VERTEX_ARRAY);
	glLineWidth(1.0f);
	glColor4f(_lineColor.R, _lineColor.G, _lineColor.B, 1.0f);
	glVertexPointer(2, GL_FLOAT, 0, &_points[0]);
	glDrawArrays(GL_LINES, 0, _points.size() / 2);
	
	// axes
	glColor4f(_axisColor.R, _axisColor.G, _axisColor.B, 1.0f);
	glVertexPointer(2, GL_FLOAT, 0, _axes);
	glDrawArrays(GL_LINES, 0, 4);
}
