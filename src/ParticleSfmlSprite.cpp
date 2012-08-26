/*
 * ParticleSFML.cpp
 *
 *  Created on: Aug 21, 2012
 *      Author: stashell
 */

#include "ParticleSfmlSprite.h"

ParticleSfmlSprite::ParticleSfmlSprite(float p_ax, float p_ay, float p_weight, sf::Sprite p_sprite, float p_scaledSize, Color p_color) :
		Particle(p_ax, p_ay, p_weight, p_scaledSize, p_color)
{
	sprite = p_sprite;
	sprite.setScale(scaledSize, scaledSize);
}

void ParticleSfmlSprite::setScaledSize(float p_scaledSize)
{
	scaledSize = p_scaledSize;
	sprite.setScale(scaledSize, scaledSize);
}

void ParticleSfmlSprite::paint(sf::RenderWindow* window)
{
	sprite.setColor(sf::Color(color.red, color.green, color.blue, color.alpha));
	sprite.setPosition(getAx(), getAy());
	window->draw(sprite);
}

ParticleSfmlSprite::~ParticleSfmlSprite()
{
	// TODO Auto-generated destructor stub
}

