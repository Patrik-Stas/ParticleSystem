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

#define PI 3.14159265

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
	}
}

void ParticleGroup::pushObject(Point p_spawnPoint)
{
	Particle* newParticle = Particle::getParticle(p_spawnPoint, SFML_PRIMITIVE);
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
		int xVect = (rand() % 1000 / 30) * xPole;
		int yVect = (rand() % 1000 / 30) * yPole;
		(*tmpIt)->setVectorXY(xVect, yVect);
	}
}

void ParticleGroup::processData(float framerate, Point gravityPoint )
{
	std::list<Particle*>::iterator beginIt = particles.begin();
	std::list<Particle*>::iterator endIt = particles.end();
	std::list<Particle*>::iterator tmpIt;
	Particle * particle = NULL;
	for (tmpIt = beginIt; tmpIt != endIt; tmpIt++)
	{
		particle = *tmpIt;
		particle->processData(framerate);
		float distX = particle->getAx() - gravityPoint.x;
		float distY = particle->getAy() - gravityPoint.y;
		float distance = sqrt(distX*distX + distY*distY);
		float particleMass = 1;
		float mouseMass = 1000	;
		float gravitation = 2;
		float force = gravitation * ( (particleMass * mouseMass) / (distance*distance) );
		float angle = atan2(distY, distX) * 180 / PI;
		float pushX = cos(angle*PI/180) * force;
		float pushY = sin(angle*PI/180) * force;
		particle->pushXY(-pushX, -pushY);
		//if (!moveableArea.isInsideX(particle->getAx())) particle->invertVectorX();
		//if (!moveableArea.isInsideY(particle->getAy())) particle->invertVectorY();
	}
}

ParticleGroup::~ParticleGroup()
{
}
