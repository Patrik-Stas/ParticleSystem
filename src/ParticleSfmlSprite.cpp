/*
 * ParticleSFML.cpp
 *
 *  Created on: Aug 21, 2012
 *      Author: stashell
 */

#include "ParticleSfmlSprite.h"

ParticleSfmlSprite::ParticleSfmlSprite(float p_ax, float p_ay) : Particle(p_ax, p_ay)
{

}

void ParticleSfmlSprite::paint(sf::RenderWindow* window) const
{
	window->Draw(sf::Shape::Circle(this->getAx(),getAy(), 1, sf::Color::Yellow));
}

ParticleSfmlSprite::~ParticleSfmlSprite()
{
	// TODO Auto-generated destructor stub
}

