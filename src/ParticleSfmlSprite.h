/*
 * ParticleSFML.h
 *
 *  Created on: Aug 21, 2012
 *      Author: stashell
 */

#ifndef PARTICLESFML_H_
#define PARTICLESFML_H_

#include "Particle.h"

class ParticleSfmlSprite : public Particle
{
public:
	ParticleSfmlSprite(float p_ax, float p_ay, float p_weight, sf::Sprite p_sprite, float p_scaledRadius, Color p_color);
	void setScaledSize(float p_scaledSize);
	void paint(sf::RenderWindow* window);
	virtual ~ParticleSfmlSprite();
private:
	sf::Sprite sprite;
};

#endif /* PARTICLESFML_H_ */
