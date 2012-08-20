/*
 * ParticleGroupPainter.h
 *
 *  Created on: Aug 20, 2012
 *      Author: stashell
 */

#ifndef PARTICLEGROUPPAINTER_H_
#define PARTICLEGROUPPAINTER_H_

#include "ParticleGroup.h"
#include <SFML/Graphics.hpp>

class ParticleGroupPainter
{
public:
	ParticleGroupPainter(ParticleGroup* particleGroup, sf::RenderWindow* window);
	void paint();
private:
	ParticleGroup* particleGroup;
	sf::RenderWindow* window;

};

#endif /* PARTICLEGROUPPAINTER_H_ */
