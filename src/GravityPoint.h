/*
 * GravityPoint.h
 *
 *  Created on: Aug 29, 2012
 *      Author: stashell
 */

#ifndef GRAVITYPOINT_H_
#define GRAVITYPOINT_H_

#include <SFML/Graphics.hpp>

#include "Point.h"

class GravityPoint
{
public:
	GravityPoint();
	virtual void calcNextPosition(float p_framerate) = 0;
	virtual Point getPosition() = 0;
	virtual float getX() = 0;
	virtual float getY() = 0;
	virtual void paint(sf::RenderWindow* p_appWindow) = 0;
	virtual bool isActive() = 0;
	virtual void setActive(bool p_active) = 0;
	virtual ~GravityPoint();
	float getWeight() const;
	void setWeight(float p_weight);
	void setForceActive(bool forceActive);
	bool isForceActive() const;

protected:
	float weight;
	bool forceActive;
};

#endif /* GRAVITYPOINT_H_ */
