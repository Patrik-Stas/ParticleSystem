/*
 * ParticleSFML.cpp
 *
 *  Created on: Aug 21, 2012
 *      Author: stashell
 */

#include "ParticleSfmlSprite.h"

ParticleSfmlSprite::ParticleSfmlSprite(float p_ax, float p_ay, sf::Sprite p_sprite ) : Particle(p_ax, p_ay)
{
	sprite = p_sprite;
}

void ParticleSfmlSprite::paint(sf::RenderWindow* window)
{
	sprite.SetColor(sf::Color(0, 255, 255, 128));
	sprite.SetPosition(getAx(), getAy());
	window->Draw(sprite);
}

ParticleSfmlSprite::~ParticleSfmlSprite()
{
	// TODO Auto-generated destructor stub
}

