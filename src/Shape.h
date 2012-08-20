/*
 * Shape.h
 *
 *  Created on: Aug 20, 2012
 *      Author: stashell
 */

#ifndef SHAPE_H_
#define SHAPE_H_

#include "Point.h"

class Shape
{
public:
	Shape();
	virtual bool isInside(Point p_pt) const = 0;
	virtual Point getInsidePoint() const = 0;
	virtual ~Shape();
};

#endif /* SHAPE_H_ */
