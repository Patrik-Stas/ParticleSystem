/*
 * PartcileSfmlPrimitive.h
 *
 *  Created on: Aug 21, 2012
 *      Author: stashell
 */

#ifndef PARTICLESFMLPRIMITIVE_H_
#define PARTICLESFMLPRIMITIVE_H_

#include <SFML/Graphics.hpp>

#include "Particle.h"

class ParticleSfmlPrimitive : public Particle
{
public:
	ParticleSfmlPrimitive(float p_ax, float p_ay);
	void paint(sf::RenderWindow* window) const;
	virtual ~ParticleSfmlPrimitive();
};

#endif /* PARTCILESFMLPRIMITIVE_H_ */
