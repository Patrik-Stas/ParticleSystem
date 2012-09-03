/*
 * ParticlePhysics.cpp
 *
 *  Created on: Aug 26, 2012
 *      Author: stashell
 */

#include <iostream>
#include <fstream>

#include "ParticlePhysics.h"
#include "Constants.h"


ParticlePhysics::ParticlePhysics()
{
	gravityPointForce = false;
}

void ParticlePhysics::applyGravityPoint(Particle* particle)
{
	if ((*gravityPoint)->isActive())
	{
		float distX = particle->getAx() - (*gravityPoint)->getX();
		float distY = particle->getAy() - (*gravityPoint)->getY();
		float distance = sqrt(distX * distX + distY * distY);
		float force = gravitation * ((particle->getWeight() * (*gravityPoint)->getWeight()) / (distance * distance));
		float angle = atan2(distY, distX) * 180 / PI;
		float pushX = cos(angle * PI / 180) * force;
		float pushY = sin(angle * PI / 180) * force;
		if (downForce)
			pushY -= gravitation;
		if (distance > 30)
			particle->pushXY(-pushX, -pushY);
		if (distance < 1)
		{
			particle->invertVectorXY();
			particle->adjustSpeed(0.5);
		}
		if (distance > 60)
			if (particle->getSpeed() > distance)
				particle->adjustSpeed(0.6);
	}
	/*
	 if (distance>30) particle->pushXY(-pushX, -pushY);
	 if (distance<5)
	 {
	 	 particle->invertVectorXY();
	 }
	 if (distance>80) if(particle->getSpeed()>distance*3) particle->adjustSpeed(0.1);
	*/
}


void ParticlePhysics::applyDownForce(Particle* particle)
{
	if (downForce)
		particle->pushY(gravitation);
}

bool ParticlePhysics::isDownForce() const
{
	return downForce;
}

void ParticlePhysics::setDownForce(bool downForce)
{
	this->downForce = downForce;
}

float ParticlePhysics::getGravitation() const
{
	return gravitation;
}

void ParticlePhysics::setGravitation(float gravitation)
{
	this->gravitation = gravitation;
}

bool ParticlePhysics::isGravityPointForce() const
{
	return gravityPointForce;
}

void ParticlePhysics::setGravityPoint(GravityPoint** p_gravityPoint)
{
	gravityPoint = p_gravityPoint;
}

void ParticlePhysics::setGravityPointForce(bool gravityPointForce)
{
	this->gravityPointForce = gravityPointForce;
}



std::ostream& operator<<(std::ostream& ostr, const ParticlePhysics& physics)
{
//	ostr << "Gravitation: " << physics.getGravitation() << endl;
//	ostr << "GravityPointForce: " << physics.gravityPointForce << endl;
//	ostr << "DownForce: " << physics.downForce << endl;
/*	ostr << "RedCalc: " << physics.redColorCalculation << endl;
	ostr << "GreenCalc: " << physics.greenColorCalculation << endl;
	ostr << "BlueCalc: " << physics.blueColorCalculation << endl;*/
	return ostr;
}
