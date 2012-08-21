/*
 * Particle.cpp
 *
 *  Created on: Aug 20, 2012
 *      Author: stashell
 */

#include "Particle.h"

#include "ParticleSfmlPrimitive.h"
#include "ParticleSfmlSprite.h"

Particle::Particle(float p_ax, float p_ay)
{
	lastAX = ax = p_ax;
	lastAY = ay = p_ay;
}
Particle::~Particle()
{
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

Particle* Particle::getParticle(float p_ax, float p_ay, PARTICLE_TYPE p_type)
{
	if (p_type == SFML_PRIMITIVE ) return new ParticleSfmlPrimitive(p_ax, p_ay);
	else if (p_type == SFML_SPRITE) return new ParticleSfmlSprite(p_ax, p_ay);
	else abort();
}

Particle* Particle::getParticle(Point p_pt, PARTICLE_TYPE p_type)
{
	return getParticle(p_pt.x, p_pt.y, p_type);
}


