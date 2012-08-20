/*
 * Particle.cpp
 *
 *  Created on: Aug 20, 2012
 *      Author: stashell
 */

#include "Particle.h"

Particle::Particle(float p_ax, float p_ay)
{
	lastAX = ax = p_ax;
	lastAY = ay = p_ay;
}

void Particle::processData(float framerate)
{
    float fpsRatio=1/framerate;

    lastAX=ax;
    lastAY=ay;

    ax+=fpsRatio*vectorX; // -direction, because of [0,0] point in computer cartesian system is in top left point
    ay+=fpsRatio*vectorY;
}

void Particle::setVectorXY(float p_vectorX, float p_vectorY)
{
	vectorX = p_vectorX;
	vectorY = p_vectorY;
}

Particle* Particle::getParticle(float p_ax, float p_ay)
{
	return new Particle(p_ax, p_ay);
}

