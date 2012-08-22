/*
 * ParticleGroup.cpp
 *
 *  Created on: Aug 20, 2012
 *      Author: stashell
 */

#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <math.h>

#include "ParticleGroup.h"
#include "Constants.h"

ParticleGroup::ParticleGroup(ShapeRectangle p_spawnArea, float p_defaultWeight, sf::Sprite p_defaultParticleSprite)
{
	spawnArea = p_spawnArea;
	particleSprite = p_defaultParticleSprite;
	defaultWeight = p_defaultWeight;
	srand(time(NULL));
}

void ParticleGroup::pushSpawnparticles(int p_count)
{
	for (int i = 0; i < p_count; i++)
	{
		Point pt = spawnArea.getInsidePoint();
		pushObject(pt);
	}
}

void ParticleGroup::pushObject(Point p_spawnPoint)
{
//	Particle* newParticle = Particle::getParticleSfmlPrimitive(p_spawnPoint.x,p_spawnPoint.y, defaultWeight );
	Particle* newParticle = Particle::getParticleSfmlSprite(p_spawnPoint.x, p_spawnPoint.y, defaultWeight,
			particleSprite);
	particles.push_back(newParticle);
}

void ParticleGroup::pushObject(Particle* object)
{
	particles.push_back(object);
}

void ParticleGroup::setRandVect()
{
	std::list<Particle*>::iterator beginIt = particles.begin();
	std::list<Particle*>::iterator endIt = particles.end();
	std::list<Particle*>::iterator tmpIt;
	for (tmpIt = beginIt; tmpIt != endIt; tmpIt++)
	{
		int xPole = (rand() % 2) ? 1 : -1;
		int yPole = (rand() % 2) ? 1 : -1;
		int xVect = (rand() % 1000 / 30) * xPole;
		int yVect = (rand() % 1000 / 30) * yPole;
		(*tmpIt)->setVectorXY(xVect, yVect);
	}
}

void ParticleGroup::processData(float framerate)
{
	std::list<Particle*>::iterator beginIt = particles.begin();
	std::list<Particle*>::iterator endIt = particles.end();
	std::list<Particle*>::iterator tmpIt;
	Particle * particle = NULL;
	for (tmpIt = beginIt; tmpIt != endIt; tmpIt++)
	{
		particle = *tmpIt;
		particle->processData(framerate);
	}
}

ParticleGroup::~ParticleGroup()
{
}
