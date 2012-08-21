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

Particle* Particle::getParticleSfmlPrimitive(float p_ax, float p_ay)
{
	return new ParticleSfmlPrimitive(p_ax, p_ay);
}

Particle* Particle::getParticleSfmlSprite(float p_ax, float p_ay, sf::Sprite p_sprite)
{
	 return new ParticleSfmlSprite(p_ax, p_ay, p_sprite );
}




