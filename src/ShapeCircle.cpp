/*
 * ShapeCricle.cpp
 *
 *  Created on: Aug 21, 2012
 *      Author: stashell
 */
#include <math.h>
#include <stdlib.h>

#include "ShapeCircle.h"
#include "Constants.h"

ShapeCircle::ShapeCircle(Point p_pt, int p_radius) : Shape(p_pt)
{
	radius = p_radius;
}

bool ShapeCircle::isInside(Point p_pt) const
{
	float xDistance = p_pt.x - x;
	float yDistance = p_pt.y - y;
	float distance = sqrt(xDistance*xDistance + yDistance*yDistance);
	if (distance<=radius) return true;
	return false;
}

Point ShapeCircle::getInsidePoint() const
{
	float angle = rand()%360;
	float distance = rand()%radius;
	return Point(x + cos(angle*PI/180)*distance, y + sin(angle*PI/180)*distance);
}


Point ShapeCircle::getOposittePosition(Point pt) const
{
	abort(); // not implemented
}


Point ShapeCircle::getClosestInsidePoint(Point p_pt) const
{
	return getInsidePoint(); /// NEET TO IMPLEMENT !!!!!!!!!!!
}

ShapeCircle::~ShapeCircle()
{

}

