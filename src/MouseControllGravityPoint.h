/*
 * MouseControllGravityPoint.h
 *
 *  Created on: Aug 29, 2012
 *      Author: stashell
 */

#ifndef MOUSECONTROLLGRAVITYPOINT_H_
#define MOUSECONTROLLGRAVITYPOINT_H_

#include <SFML/Graphics.hpp>

#include "GravityPoint.h"

class MouseControllGravityPoint: public GravityPoint
{
public:
	MouseControllGravityPoint();
	void calcNextPosition(float p_framerate);
	Point getPosition();
	void setMouseVariables(int* p_mouseX, int* p_mouseY, bool* p_active);
	float getX();
	float getY();
	bool isActive();
	void setActive(bool p_active);
	void paint(sf::RenderWindow* p_appWindow);
	~MouseControllGravityPoint();
private:
	int* c_mouseX;
	int* c_mouseY;
	bool* c_active;
};

#endif /* MOUSECONTROLLGRAVITYPOINT_H_ */
