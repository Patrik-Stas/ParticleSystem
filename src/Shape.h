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
	Shape(Point pt);
    void setLocation(Point pt);
	virtual bool isInside(Point p_pt) const = 0;
	virtual Point getInsidePoint() const = 0;
	virtual Point getClosestInsidePoint(Point p_pt) const = 0;
	virtual ~Shape();
protected:
	float x;
	float y;
};

#endif /* SHAPE_H_ */
