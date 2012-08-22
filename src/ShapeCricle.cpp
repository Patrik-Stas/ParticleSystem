/*
 * ShapeCricle.cpp
 *
 *  Created on: Aug 21, 2012
 *      Author: stashell
 */
#include <math.h>
#include <stdlib.h>

#include "ShapeCricle.h"
#include "Constants.h"

ShapeCricle::ShapeCricle(float p_x, float p_y, int p_radius)
{
	x = p_x;
	y = p_y;
	radius = p_radius;
}

bool ShapeCricle::isInside(Point p_pt) const
{
	float xDistance = p_pt.x - x;
	float yDistance = p_pt.y - y;
	float distance = sqrt(xDistance*xDistance + yDistance*yDistance);
	if (distance<=radius) return true;
	return false;
}

Point ShapeCricle::getInsidePoint() const
{
	float angle = rand()%360;
	float distance = rand()%radius;
	return Point(cos(angle*PI/180)*distance, sin(angle*PI/180)*distance);
}

ShapeCricle::~ShapeCricle()
{

}

