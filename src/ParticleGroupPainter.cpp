/*
 * ParticleGroupPainter.cpp
 *
 *  Created on: Aug 20, 2012
 *      Author: stashell
 */

#include "ParticleGroupPainter.h"
#include <iostream>

ParticleGroupPainter::ParticleGroupPainter(ParticleGroup* particleGroup, sf::RenderWindow* window)
{
	this->particleGroup = particleGroup;
	this->window = window;
}

void ParticleGroupPainter::paint()
{
	std::list<Particle*>::iterator beginIt = particleGroup->particles.begin();
	std::list<Particle*>::iterator endIt = particleGroup->particles.end();
	std::list<Particle*>::iterator particle;
	for (particle = beginIt; particle != endIt; particle++)
	{
		(*particle)->paint(window);
	}
}

