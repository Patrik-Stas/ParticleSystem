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

ParticleGroup::ParticleGroup(ParticlePhysics* p_particlePhysics, Shape* p_moveableArea, BOUND_ACTION p_boundAction,
		Emitter* p_emitter, float p_defaultWeight, float p_defaultScaledSize, sf::Sprite p_defaultParticleSprite)
{
	emitter = p_emitter;
	particlePhysics = p_particlePhysics;
	moveableArea = p_moveableArea;
	particleSprite = p_defaultParticleSprite;
	defaultWeight = p_defaultWeight;
	defaultScaledSize = p_defaultScaledSize;
	boundAction = p_boundAction;
	srand(time(NULL));
}

void ParticleGroup::setParticlesCount(int p_newSize)
{
	int actualSize = particles.size();
	(p_newSize > actualSize) ? addParticles(p_newSize - actualSize) : removeParticles(actualSize - p_newSize);
}

void ParticleGroup::addParticles(int p_count)
{
	for (int i = 0; i < p_count; i++)
	{
		Point pt = emitter->emitPosition();
		addParticleAt(pt);
	}
}

void ParticleGroup::removeParticles(int p_count)
{
	for (int i = 0; i < p_count; i++)
	{
		particles.pop_back();
	}
	//particles.resize(p_count);
}

void ParticleGroup::addParticleAt(Point p_spawnPoint)
{
	//Particle* newParticle = Particle::getParticleSfmlPrimitive(p_spawnPoint.x,p_spawnPoint.y, defaultWeight, 1, 1 );
	Particle* newParticle = Particle::getParticleSfmlSprite(p_spawnPoint.x, p_spawnPoint.y, defaultWeight,
			particleSprite, defaultScaledSize);
	particles.push_back(newParticle);
}

void ParticleGroup::addParticle(Particle* object)
{
	particles.push_back(object);
}

void ParticleGroup::setScaledSize(float p_scaledSize)
{
	std::for_each(particles.begin(), particles.end(),
			std::bind2nd(std::mem_fun(&Particle::setScaledSize), p_scaledSize));
	defaultScaledSize = p_scaledSize;
}

void ParticleGroup::setAlpha(int p_alpha)
{
	std::for_each(particles.begin(), particles.end(),
			std::bind2nd(std::mem_fun(&Particle::setAlpha), p_alpha));
}

void ParticleGroup::setBoundAction(BOUND_ACTION p_boundAction)
{
	boundAction = p_boundAction;
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
	std::for_each(particles.begin(), particles.end(), std::bind2nd(std::mem_fun(&Particle::processData), framerate));
}

void ParticleGroup::respawn(std::list<Particle*>::iterator particle)
{
	Point respawnPos = emitter->emitPosition();
	(*particle)->setPosition(respawnPos);
	(*particle)->setVectorXY(emitter->emitVector());
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
		particlePhysics->applyGravityPoint(particle);
		particlePhysics->applyDownForce(particle);
	}
}

void ParticleGroup::checkBounds()
{
	std::list<Particle*>::iterator beginIt = particles.begin();
	std::list<Particle*>::iterator endIt = particles.end();
	std::list<Particle*>::iterator tmpIt;
	Particle* particle = NULL;
	for (tmpIt = beginIt; tmpIt != endIt; tmpIt++)
	{
		particle = (*tmpIt);
		Point particlePosition = (*tmpIt)->getPosition();
		Point closesInsidePosition = moveableArea->getClosestInsidePoint(particlePosition);
		if (particlePosition != closesInsidePosition)
		{
			switch (boundAction)
			{
			case bound_stop:
			{
				particle->stop();
				particle->setPosition(closesInsidePosition);
				break;
			}
			case bound_mirror_port:
			{
				//		moveableArea->getMirroredPosition();
				break;
			}
			case bound_respawn:
			{
				respawn(tmpIt);
				break;
			}
			case bound_kill:
			{
				tmpIt = particles.erase(tmpIt);
				break;
			}
			}
		}
	}
}

void ParticleGroup::paint(sf::RenderWindow* window)
{
	std::for_each(particles.begin(), particles.end(), std::bind2nd(std::mem_fun(&Particle::paint), window));
}

int ParticleGroup::getParticleCount()
{
	return particles.size();
}

ParticleGroup::~ParticleGroup()
{
}
