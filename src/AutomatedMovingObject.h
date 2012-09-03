/*
 * AutomatedMovingObject.h
 *
 *  Created on: Aug 28, 2012
 *      Author: stashell
 */

#ifndef AUTOMATEDMOVINGOBJECT_H_
#define AUTOMATEDMOVINGOBJECT_H_

#include "Point.h"
#include "ShapeRectangle.h"
#include "MovingObject.h"
#include <SFML/Graphics.hpp>

class AutomatedMovingObject
{
public:
	AutomatedMovingObject();
	Point getNextPosition(int framerate);
	Point getCurrentDestination();
	virtual ~AutomatedMovingObject();
	float getDynamics() const;
	void setDynamics(float dynamics);
	void setMoveableArea( Shape* moveableArea);
	float getSpeed() const;
	void setSpeed(float speed);
	float getDirection();
	void paint(sf::RenderWindow* appWindow);

private:
	Shape* moveableArea;
	MovingObject movingObject;
	Point destinationPoint;
	Point getCurrentPosition();
	int iterations;
	bool turningRight;
	bool heading;
	float speed;
	float dynamics;
};

#endif /* AUTOMATEDMOVINGOBJECT_H_ */
