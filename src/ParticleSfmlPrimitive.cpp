/*
 * ParticleSfmlPrimitive.cpp
 *
 *  Created on: Aug 21, 2012
 *      Author: stashell
 */

#include "ParticleSfmlPrimitive.h"

ParticleSfmlPrimitive::ParticleSfmlPrimitive(float p_ax, float p_ay) : Particle(p_ax, p_ay)
{
	// TODO Auto-generated constructor stub
}

void ParticleSfmlPrimitive::paint(sf::RenderWindow* window)
{
	window->Draw(sf::Shape::Circle(this->getAx(),getAy(), 1, sf::Color::Yellow));
}

ParticleSfmlPrimitive::~ParticleSfmlPrimitive()
{
	// TODO Auto-generated destructor stub
}

