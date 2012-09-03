/*
 * MouseControllGravityPoint.cpp
 *
 *  Created on: Aug 29, 2012
 *      Author: stashell
 */

#include "MouseControllGravityPoint.h"

MouseControllGravityPoint::MouseControllGravityPoint()
{
	c_mouseX = c_mouseY = 0;
}

void MouseControllGravityPoint::setMouseVariables(int* p_mouseX, int* p_mouseY, bool* p_active)
{
	c_mouseX = p_mouseX;
	c_mouseY = p_mouseY;
	c_active = p_active;
}

float MouseControllGravityPoint::getX()
{
	return *c_mouseX;
}

float MouseControllGravityPoint::getY()
{
	return *c_mouseY;
}

void MouseControllGravityPoint::calcNextPosition(float p_framerate)
{
	return;
}

Point MouseControllGravityPoint::getPosition()
{
	return Point(*c_mouseX, *c_mouseY);
}

void MouseControllGravityPoint::paint(sf::RenderWindow* p_appWindow)
{
	sf::CircleShape circle(4, 20);
	circle.setPosition((float) *c_mouseX, (float) *c_mouseY);
	circle.setFillColor(sf::Color(0,255,0));
	p_appWindow->draw(circle);
}

bool MouseControllGravityPoint::isActive()
{
	if (forceActive) return true;
	return *c_active;
}

void MouseControllGravityPoint::setActive(bool p_active)
{
	// nope ! MouseControllGP is controlled just by pointer given in setMouseVariables. That should represent
	// some button on mouse, or key if you wish...
}

MouseControllGravityPoint::~MouseControllGravityPoint()
{
	// TODO Auto-generated destructor stub
}

