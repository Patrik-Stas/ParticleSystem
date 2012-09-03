/*
 * AutomatedGravityPoint.h
 *
 *  Created on: Aug 29, 2012
 *      Author: stashell
 */

#ifndef AUTOMATEDGRAVITYPOINT_H_
#define AUTOMATEDGRAVITYPOINT_H_

#include "GravityPoint.h"
#include "AutomatedMovingObject.h"

class AutomatedGravityPoint : public GravityPoint
{
public:
	AutomatedGravityPoint();
	void calcNextPosition(float p_framerate);
	Point getPosition();
	float getX();
	float getY();
	bool isActive();
	void setActive(bool p_active);
	void setAutomatedMovingObject(AutomatedMovingObject* p_automatedMovingObject);
	void paint(sf::RenderWindow* p_appWindow);
	virtual ~AutomatedGravityPoint();
private:
	AutomatedMovingObject* automatedMovingObject;
	Point position;
	bool active;
};

#endif /* AUTOMATEDGRAVITYPOINT_H_ */
