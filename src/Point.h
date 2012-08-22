/*
 * Point.h
 *
 *  Created on: Aug 20, 2012
 *      Author: stashell
 */

#ifndef POINT_H_
#define POINT_H_

class Point
{
public:
	Point(float p_x, float p_y);
	float x;
	float y;
	bool operator==(const Point& pt) const;
	bool operator!=(const Point& pt) const;
};

#endif /* POINT_H_ */
