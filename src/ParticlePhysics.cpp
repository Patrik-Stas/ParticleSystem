/*
 * ParticlePhysics.cpp
 *
 *  Created on: Aug 22, 2012
 *      Author: stashell
 */

#include <math.h>

#include "ParticlePhysics.h"
#include "Constants.h"

ParticlePhysics::ParticlePhysics(int p_gravitation, ShapeRectangle p_moveableArea)
{
	gravitation = p_gravitation;
	moveableArea =  p_moveableArea;
}

void ParticlePhysics::apply(ParticleGroup* particleGroup, const Particle& gravityPoint)
{
	std::list<Particle*>::iterator beginIt = particleGroup->particles.begin();
	std::list<Particle*>::iterator endIt = particleGroup->particles.end();
	std::list<Particle*>::iterator tmpIt;
	Particle * particle = NULL;
	for (tmpIt = beginIt; tmpIt != endIt; tmpIt++)
	{
		particle = *tmpIt;
		float distX = particle->getAx() - gravityPoint.getAx();
		float distY = particle->getAy() - gravityPoint.getAy();
		float distance = sqrt(distX * distX + distY * distY);
		float force = gravitation * ((particle->getWeight() * gravityPoint.getWeight()) / (distance * distance));
		float angle = atan2(distY, distX) * 180 / PI;
		float pushX = cos(angle * PI / 180) * force;
		float pushY = sin(angle * PI / 180) * force - 1*gravitation;
		particle->pushXY(-pushX, -pushY);
		Point particlePosition = particle->getPosition();
		Point closesInsidePosition = moveableArea.getClosestInsidePoint(particlePosition);
		if (particlePosition != closesInsidePosition)
		{
			particle->stop();
			particle->setPosition(closesInsidePosition);
		}
	}
}

ParticlePhysics::~ParticlePhysics()
{
	// TODO Auto-generated destructor stub
}

