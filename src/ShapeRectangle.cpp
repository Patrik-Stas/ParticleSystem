/*
 * ShapeRectangle.cpp
 *
 *  Created on: Aug 20, 2012
 *      Author: stashell
 */

#include "ShapeRectangle.h"
#include <stdlib.h>



ShapeRectangle::ShapeRectangle(Point p_pt, int p_width, int p_height) : Shape(p_pt)
{
	width = p_width;
	height = p_height;
}


ShapeRectangle::~ShapeRectangle()
{
}

bool ShapeRectangle::isInsideX(float p_x) const
{
	if (p_x >= x && p_x <= (x + width) )
		return true;
	else
		return false;
}

bool ShapeRectangle::isInsideY(float p_y) const
{
	if ( p_y >= y && p_y < (y + height))
		return true;
	else
		return false;
}

bool ShapeRectangle::isInside(Point p_pt) const
{
	if ( isInsideX(p_pt.x) && isInsideY(p_pt.y) )
		return true;
	else
		return false;
}

Point ShapeRectangle::getInsidePoint() const
{
	return Point(x + rand() % width, y + rand() % height);
}


Point ShapeRectangle::getClosestInsidePoint(Point p_pt) const
{
	Point retPt(p_pt);
	if (p_pt.y <= y)  retPt.y = y + 5;
	else if (p_pt.y > (y + height)) retPt.y = (y + height) - 5;
	if (p_pt.x <= x)  retPt.x = x + 5;
	else if (p_pt.x > (x + width)) retPt.x = (x + width) - 5 ;
	return retPt;
}


