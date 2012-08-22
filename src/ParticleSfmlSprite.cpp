/*
 * ParticleSFML.cpp
 *
 *  Created on: Aug 21, 2012
 *      Author: stashell
 */

#include "ParticleSfmlSprite.h"

ParticleSfmlSprite::ParticleSfmlSprite(float p_ax, float p_ay, float p_weight, sf::Sprite p_sprite, Color p_color) :
		Particle(p_ax, p_ay, p_weight, p_color)
{
	sprite = p_sprite;
}

void ParticleSfmlSprite::paint(sf::RenderWindow* window)
{
	sprite.SetColor(sf::Color(color.red, color.green, color.blue, color.alpha));
	sprite.SetPosition(getAx(), getAy());
	window->Draw(sprite);
}

ParticleSfmlSprite::~ParticleSfmlSprite()
{
	// TODO Auto-generated destructor stub
}

