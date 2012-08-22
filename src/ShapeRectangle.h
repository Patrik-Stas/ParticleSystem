/*
 * ShapeRectangle.h
 *
 *  Created on: Aug 20, 2012
 *      Author: stashell
 */

#ifndef SHAPERECTANGLE_H_
#define SHAPERECTANGLE_H_

#include "Shape.h"

class ShapeRectangle: public Shape
{
public:

	ShapeRectangle();
	ShapeRectangle(int p_rx, int p_ry, int p_width, int p_height);
	void initialize(int p_rx, int p_ry, int p_width, int p_height);
	bool isInside(Point p_pt) const;
	bool isInsideX(float p_x) const;
	bool isInsideY(float p_y) const;
	Point getInsidePoint() const;
	Point getClosestInsidePoint(Point p_pt) const;
	virtual ~ShapeRectangle();
	int rx;
	int ry;
	int width;
	int height;
};

#endif /* SHAPERECTANGLE_H_ */
