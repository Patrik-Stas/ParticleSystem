/*
 * AutomatedGravityPoint.cpp
 *
 *  Created on: Aug 29, 2012
 *      Author: stashell
 */

#include "AutomatedGravityPoint.h"

AutomatedGravityPoint::AutomatedGravityPoint()
{
	automatedMovingObject = 0L;
	active = true;
}

void AutomatedGravityPoint::setAutomatedMovingObject(AutomatedMovingObject* p_automatedMovingObject)
{
	automatedMovingObject = p_automatedMovingObject;
}

void AutomatedGravityPoint::calcNextPosition(float p_framerate)
{
	position =  automatedMovingObject->getNextPosition(p_framerate);
}

Point AutomatedGravityPoint::getPosition()
{
	return position;
}

float AutomatedGravityPoint::getX()
{
	return position.x;
}

float AutomatedGravityPoint::getY()
{
	return position.y;
}

bool AutomatedGravityPoint::isActive()
{
	if (forceActive) return true;
	else return active;
}

void AutomatedGravityPoint::setActive(bool p_active)
{
	active = p_active;
}

void AutomatedGravityPoint::paint(sf::RenderWindow* p_appWindow)
{
	automatedMovingObject->paint(p_appWindow);
}

AutomatedGravityPoint::~AutomatedGravityPoint()
{
	// TODO Auto-generated destructor stub
}

