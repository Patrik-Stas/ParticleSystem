/*
 * Shape.h
 *
 *  Created on: Aug 20, 2012
 *      Author: stashell
 */

#ifndef SHAPE_H_
#define SHAPE_H_

class Shape
{
public:
	Shape();
	virtual bool isInside();
	virtual ~Shape();
};

#endif /* SHAPE_H_ */
