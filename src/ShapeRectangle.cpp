/*
 * ShapeRectangle.cpp
 *
 *  Created on: Aug 20, 2012
 *      Author: stashell
 */

#include "ShapeRectangle.h"
#include <stdlib.h>

ShapeRectangle::ShapeRectangle()
{
}

ShapeRectangle::ShapeRectangle(int p_rx, int p_ry, int p_width, int p_height)
{
	initialize(p_rx, p_ry, p_width, p_height);
}

void ShapeRectangle::initialize(int p_rx, int p_ry, int p_width, int p_height)
{
	rx = p_rx;
	ry = p_ry;
	width = p_width;
	height = p_height;
}

ShapeRectangle::~ShapeRectangle()
{
}

bool ShapeRectangle::isInsideX(float p_x) const
{
	if (p_x >= rx && p_x <= (rx + width) )
		return true;
	else
		return false;
}

bool ShapeRectangle::isInsideY(float p_y) const
{
	if ( p_y >= ry && p_y < (ry + height))
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
	return Point(rx + rand() % width, ry + rand() % height);
}


Point ShapeRectangle::getClosestInsidePoint(Point p_pt) const
{
	Point retPt(p_pt);
	if (p_pt.y <= ry)  retPt.y = ry + 5;
	else if (p_pt.y > (ry + height)) retPt.y = (ry + height) - 5;
	if (p_pt.x <= rx)  retPt.x = rx + 5;
	else if (p_pt.x > (rx + width)) retPt.x = (rx + width) - 5 ;
	return retPt;
}
