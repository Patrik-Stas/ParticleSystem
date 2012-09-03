/*
 * GravityPoint.cpp
 *
 *  Created on: Aug 29, 2012
 *      Author: stashell
 */

#include "GravityPoint.h"

GravityPoint::GravityPoint()
{
	forceActive = false;
	weight = 0;
}

GravityPoint::~GravityPoint()
{
}

float GravityPoint::getWeight() const
{
	return weight;
}

void GravityPoint::setWeight(float p_weight)
{
	weight = p_weight;
}

void GravityPoint::setForceActive(bool forceActive)
{
	this->forceActive = forceActive;
}

bool GravityPoint::isForceActive() const
{
	return forceActive;
}
