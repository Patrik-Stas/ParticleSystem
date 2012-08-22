/*
 * ShapeCricle.h
 *
 *  Created on: Aug 21, 2012
 *      Author: stashell
 */

#ifndef SHAPECRICLE_H_
#define SHAPECRICLE_H_

#include "Shape.h"

class ShapeCricle: public Shape
{
public:
	ShapeCricle(float p_x, float p_y, int p_radius);
	bool isInside(Point p_pt) const;
	Point getInsidePoint() const;
	virtual ~ShapeCricle();

	float x;
	float y;
	int radius;
};

#endif /* SHAPECRICLE_H_ */
