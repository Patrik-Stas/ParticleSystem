/*
 * Particle.cpp
 *
 *  Created on: Aug 20, 2012
 *      Author: stashell
 */

#include "Particle.h"

#include "ParticleSfmlPrimitive.h"
#include "ParticleSfmlSprite.h"

Particle::Particle(float p_ax, float p_ay, float p_weight, float p_scaledSize, Color p_color)
{
	lastAX = ax = p_ax;
	lastAY = ay = p_ay;
	color = p_color;
	weight = p_weight;
	scaledSize = p_scaledSize;
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

Particle* Particle::getParticleSfmlPrimitive(float p_ax, float p_ay, float p_weight, int p_maximalRadius, float p_scaledSize, Color p_color)
{
	return new ParticleSfmlPrimitive(p_ax, p_ay, p_weight, p_maximalRadius, p_scaledSize, p_color );
}

Particle* Particle::getParticleSfmlSprite(float p_ax, float p_ay, float p_weight, sf::Sprite p_sprite, float p_scaledRadius, Color p_color)
{
	 return new ParticleSfmlSprite(p_ax, p_ay, p_weight, p_sprite, p_scaledRadius, p_color );
}




