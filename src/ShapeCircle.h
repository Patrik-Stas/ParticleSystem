/*
 * ShapeCricle.h
 *
 *  Created on: Aug 21, 2012
 *      Author: stashell
 */

#ifndef SHAPECRICLE_H_
#define SHAPECRICLE_H_

#include "Shape.h"

class ShapeCircle: public Shape
{
public:
	ShapeCircle(Point p_pt, int p_radius);
	bool isInside(Point p_pt) const;
	Point getInsidePoint() const;
	Point getClosestInsidePoint(Point p_pt) const;
	virtual ~ShapeCircle();
private:
	int radius;
};

#endif /* SHAPECRICLE_H_ */

