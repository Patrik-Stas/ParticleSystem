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
	ParticleSfmlPrimitive(float p_ax, float p_ay,float p_weight, int p_radius, float p_scaledRadius, Color p_color);
	void paint(sf::RenderWindow* window);
    void setScaledSize(float p_scaledSize);
	virtual ~ParticleSfmlPrimitive();

private:
	sf::ConvexShape polygon;
	sf::CircleShape circle;
	int radius;
};

#endif /* PARTCILESFMLPRIMITIVE_H_ */
