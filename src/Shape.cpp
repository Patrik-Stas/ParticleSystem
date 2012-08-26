/*
 * Shape.cpp
 *
 *  Created on: Aug 20, 2012
 *      Author: stashell
 */

#include "Shape.h"

Shape::Shape(Point p_pt)
{
	setLocation(p_pt);
}

void Shape::setLocation(Point p_pt)
{
	x = p_pt.x;
	y = p_pt.y;
}

Shape::~Shape()
{
}

