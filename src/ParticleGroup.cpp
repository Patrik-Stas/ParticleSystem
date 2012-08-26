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

ParticleGroup::ParticleGroup(ParticlePhysics* p_particlePhysics, ShapeRectangle p_spawnArea, ShapeRectangle p_moveableArea, float p_defaultWeight,
		sf::Sprite p_defaultParticleSprite)
{
	particlePhysics = p_particlePhysics;
	moveableArea = p_moveableArea;
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
	//Particle* newParticle = Particle::getParticleSfmlPrimitive(p_spawnPoint.x,p_spawnPoint.y, defaultWeight, 1, 1 );
	Particle* newParticle = Particle::getParticleSfmlSprite(p_spawnPoint.x, p_spawnPoint.y, defaultWeight,
			particleSprite, 0.1);
	particles.push_back(newParticle);
}

void ParticleGroup::pushObject(Particle* object)
{
	particles.push_back(object);
}


void ParticleGroup::setScaledSize()
{

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
	 std::for_each(particles.begin(), particles.end(),
			    std::bind2nd(std::mem_fun(&Particle::processData), framerate));
}

void ParticleGroup::respawn(std::list<Particle*>::iterator particle, Shape* shape)
{
	(*particle)->setPosition(shape->getInsidePoint());
	(*particle)->stop();
}

void ParticleGroup::applyPhysics()
{
	std::list<Particle*>::iterator beginIt = particles.begin();
	std::list<Particle*>::iterator endIt = particles.end();
	std::list<Particle*>::iterator tmpIt;
	Particle * particle = NULL;
	for (tmpIt = beginIt; tmpIt != endIt; tmpIt++)
	{
		particle = *tmpIt;
		particlePhysics->apply(particle);
		Point particlePosition = particle->getPosition();
		Point closesInsidePosition = moveableArea.getClosestInsidePoint(particlePosition);
			if (particlePosition != closesInsidePosition)
		 {
		 particle->stop();
		 particle->setPosition(closesInsidePosition);
		 }
	/*	if (particlePosition != closesInsidePosition)
		{
			//tmpIt = particles.erase(tmpIt);
			respawn(tmpIt, &spawnArea);
		}*/
	}
}

int ParticleGroup::getParticleCount()
{
	return particles.size();
}

ParticleGroup::~ParticleGroup()
{
}
