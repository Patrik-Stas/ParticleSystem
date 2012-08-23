/*
 * ParticleSfmlPrimitive.cpp
 *
 *  Created on: Aug 21, 2012
 *      Author: stashell
 */

#include "ParticleSfmlPrimitive.h"

ParticleSfmlPrimitive::ParticleSfmlPrimitive(float p_ax, float p_ay, float p_weight, Color p_color) : Particle(p_ax, p_ay, p_weight, p_color)
{
	 circle.setPointCount(30);
	 circle.setRadius(10);
	 circle.setFillColor( sf::Color(color.red, color.green, color.blue, color.alpha));
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

