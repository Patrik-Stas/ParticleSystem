/*
 * Point.cpp
 *
 *  Created on: Aug 20, 2012
 *      Author: stashell
 */

#include "Point.h"

Point::Point(float p_x, float p_y)
{
	x = p_x;
	y = p_y;
}

bool Point::operator==(const Point& pt) const
{
	if ((int)x == (int)pt.x && (int)y == (int)pt.y ) return true;
	return false;
}

bool Point::operator!=(const Point& pt) const
{
	return !((*this) == pt );
}
