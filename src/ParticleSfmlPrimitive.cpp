/*
 * ParticleSfmlPrimitive.cpp
 *
 *  Created on: Aug 21, 2012
 *      Author: stashell
 */

#include "ParticleSfmlPrimitive.h"

ParticleSfmlPrimitive::ParticleSfmlPrimitive(float p_ax, float p_ay, float p_weight, int p_radius,
		float p_scaledRadius, Color p_color) :
		Particle(p_ax, p_ay, p_weight, p_scaledRadius, p_color)
{
	radius = p_radius;
	scaledSize = p_scaledRadius;
	circle.setPointCount(30);
	circle.setRadius(p_radius*p_scaledRadius);
	circle.setFillColor(sf::Color(color.red, color.green, color.blue, color.alpha));
}

void ParticleSfmlPrimitive::setScaledSize(float p_scaledSize)
{
	scaledSize = p_scaledSize;
	circle.setRadius(p_scaledSize*radius);
}

void ParticleSfmlPrimitive::paint(sf::RenderWindow* window)
{
	circle.setPosition(getAx(), getAy());
	window->draw(circle);
}

ParticleSfmlPrimitive::~ParticleSfmlPrimitive()
{
	// TODO Auto-generated destructor stub
}

