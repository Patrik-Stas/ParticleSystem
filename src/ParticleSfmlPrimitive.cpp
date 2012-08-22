/*
 * ParticleSfmlPrimitive.cpp
 *
 *  Created on: Aug 21, 2012
 *      Author: stashell
 */

#include "ParticleSfmlPrimitive.h"

ParticleSfmlPrimitive::ParticleSfmlPrimitive(float p_ax, float p_ay, float p_weight, Color p_color) : Particle(p_ax, p_ay, p_weight, p_color)
{
	// TODO Auto-generated constructor stub
}

void ParticleSfmlPrimitive::paint(sf::RenderWindow* window)
{
	window->Draw(sf::Shape::Circle(getAx(),getAy(), 3, sf::Color(color.red, color.green, color.blue, color.alpha)));
//	window->Draw(sf::Shape::Rectangle(getAx(),getAy(),getAx()+1,getAy()+1, sf::Color::Yellow));
}

ParticleSfmlPrimitive::~ParticleSfmlPrimitive()
{
	// TODO Auto-generated destructor stub
}

