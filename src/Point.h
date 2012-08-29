/*
 * Point.h
 *
 *  Created on: Aug 20, 2012
 *      Author: stashell
 */

#ifndef POINT_H_
#define POINT_H_

#include <iostream>

class Point
{
public:
	Point();
	Point(float p_x, float p_y);
	float x;
	float y;
	bool operator==(const Point& pt) const;
	bool operator!=(const Point& pt) const;
	bool isCloserThan( Point p2, int limit);

	friend std::ostream& operator<<( std::ostream& ostr, const Point& pt);
};

#endif /* POINT_H_ */
