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
	ParticleSfmlSprite(float p_ax, float p_ay);
	void paint(sf::RenderWindow* window) const;
	virtual ~ParticleSfmlSprite();
};

#endif /* PARTICLESFML_H_ */
