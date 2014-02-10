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

#pragma once

#include "../Infrastructure/Renderable.h"
#include "../Infrastructure/Color.h"
#include "../Infrastructure/Vector2.h"

///An Actor to draw lines at regular intervals
/**
 * A GridActor just makes it easy to draw grids in your game. This can be useful
 *  for placing objects while you're creating the world, or to just look cool. :-)
 */
class GridActor : public Renderable
{
public:
	/**
	 * The default constructor creates the "Angel grid." An interval of 1.0 GL
	 *  units, drawing from (-100, -100) to (100, 100), with light blue lines 
	 *  and red axis lines. 
	 */
	GridActor();
	
	/**
	 * If you have something else in mind for your grid, you can specify its 
	 *  visual appearance with this constructor. 
	 * 
	 * @param lines the color of the lines in the grid
	 * @param axis the color of the lines drawn at the X and Y axes
	 * @param interval the amount of space (in GL units) between each line
	 * @param minCoord the bottom-left coordinate from which to start drawing
	 * @param maxCoord the top-right coordinate at which to stop drawing
	 */ 
	GridActor(const Color& lines, const Color& axis, float interval, const Vector2& minCoord, const Vector2& maxCoord);
	
	/**
	 * Set the color of the non-axis lines of the grid. 
	 * 
	 * @param lineCol the color of the lines
	 */
	void SetLineColor(const Color &lineCol);
	
	/**
	 * Return the current line color of this GridActor.
	 * 
	 * @return the current line color as a Color object
	 */
	const Color& GetLineColor() const;
	
	/**
	 * Set the color of the axis lines of the grid. 
	 * 
	 * @param axisCol the color of the axis lines
	 */
	void SetAxisColor(const Color &axisCol);
	
	/**
	 * Return the current axis line color of this GridActor.
	 * 
	 * @return the current axis line color as a Color object
	 */
	const Color& GetAxisColor() const;
	
	/**
	 * Set the spacing of the lines. 
	 * 
	 * @param interval the amount of space between each line in GL units
	 */
	void SetInterval(float interval);
	
	/**
	 * Return the line spacing interval for this GridActor.
	 * 
	 * @return the current interval in GL units
	 */
	const float GetInterval() const;
	
	/**
	 * Set the bottom-left coordinate at which to start drawing the grid.
	 * 
	 * @param minCoord the bottom-left X and Y position in GL units 
	 */
	void SetMinCoord(const Vector2 &minCoord);
	
	/**
	 * Return the bottom-left start coordinate of the grid.
	 * 
	 * @return the bottom-left X and Y position in GL unites
	 */
	const Vector2 GetMinCoord() const;
	
	/**
	 * Set the top-right coordinate at which to stop drawing the grid.
	 * 
	 * @param maxCoord the top-right X and Y position in GL units
	 */
	void SetMaxCoord(const Vector2 &maxCoord);
	
	/**
	 * Return the top-right coordinate of the grid.
	 * 
	 * @return the top-right X and Y position in GL units
	 */
	const Vector2 GetMaxCoord() const;
	
	/**
	 * Override of the normal Renderable::Render function. Draws the lines that
	 *  have been specified. 
	 */
	virtual void Render();
	
	/**
	 * Override of the normal Renderable::Update function. Does nothing, here
	 *  to satisfy the abstract base class.
	 */
	virtual void Update(float dt) {}

private:
	Color _lineColor;
	Color _axisColor;
	float _interval;
	Vector2 _minCoord;
	Vector2 _maxCoord;

	std::vector<GLfloat> _points;
	GLfloat _axes[8];
	void RecalculatePoints();
};