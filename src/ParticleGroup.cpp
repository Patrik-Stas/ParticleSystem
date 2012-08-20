/*
 * ParticleGroup.cpp
 *
 *  Created on: Aug 20, 2012
 *      Author: stashell
 */

#include <stdlib.h>
#include <time.h>
#include <iostream>

#include "ParticleGroup.h"

ParticleGroup::ParticleGroup(ShapeRectangle p_moveableArea)
{
	moveableArea = p_moveableArea;
	defFriction = 0;
	srand(time(NULL));
}

void ParticleGroup::pushSpawnparticles(int p_count)
{
	for (int i = 0; i < p_count; i++)
	{
		Point pt = moveableArea.getInsidePoint();
		pushObject(pt);
		std::cout << "get inside point:   x:" << pt.x << "   y:" << pt.y << std::endl;
	}
}

void ParticleGroup::pushObject(Point p_spawnPoint)
{
	Particle* newParticle = Particle::getParticle(p_spawnPoint);
	newParticle->setFriction(defFriction);
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
		int xVect = (rand() % 10000 / 10) * xPole;
		int yVect = (rand() % 10000 / 10) * yPole;
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
		if (!moveableArea.isInsideX(particle->getAx())) particle->invertVectorX();
		if (!moveableArea.isInsideY(particle->getAy())) particle->invertVectorY();
	}
}

ParticleGroup::~ParticleGroup()
{
}
