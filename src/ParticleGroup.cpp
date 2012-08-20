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

ParticleGroup::ParticleGroup(const float p_spawnArea_X1, const float p_spawnArea_Y1, const float p_spawnAreaX2,
		const float p_spawnAreaY2)
{
	setSpawnArea(p_spawnArea_X1, p_spawnArea_Y1, p_spawnAreaX2, p_spawnAreaY2);
	setSpawnDirection(0, 360, +1);
	defFriction = 0;
	srand(time(NULL));
}

void ParticleGroup::pushSpawnparticles(int p_count)
{
	for (int i = 0; i < p_count; i++)
	{
		float newX = generate_spawnX();
		float newY = generate_spawnY();

		float newDirection = generate_spawnDirection();
		std::cout << "newx: " << newX << "   newy: " << newY << std::endl;
		pushObject(newX, newY, newDirection);
	}
}

float ParticleGroup::generate_spawnX()
{
	int xDispersion = spawn_Xmax - spawn_Xmin; /// accuracy loose was purpose to avoid trouble with floating unperfection
	if (xDispersion != 0)
		return (spawn_Xmin + rand() % xDispersion);
	else
		return (spawn_Xmin);
}

float ParticleGroup::generate_spawnY()
{
	int yDispersion = spawn_Ymax - spawn_Ymin;
	if (yDispersion != 0)
		return (spawn_Ymin + rand() % yDispersion);
	else
		return spawn_Ymin;
}

float ParticleGroup::generate_spawnDirection()
{
	if (spawn_directionFrom - spawn_directionTo == 0)
		return spawn_directionFrom;
	else
		return (rand() % (int) (spawn_directionFrom - spawn_directionTo));
}

void ParticleGroup::pushObject(float p_x, float p_y, float p_direction)
{
	Particle* newParticle = Particle::getParticle(p_x, p_y);
	newParticle->setFriction(0.1);
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
	for (tmpIt = beginIt; tmpIt != endIt; tmpIt++)
	{
		(*tmpIt)->processData(framerate);
	}
}

void ParticleGroup::setSpawnPoint(float p_x1, float p_y1)
{
	spawn_Xmin = p_x1;
	spawn_Xmax = p_x1;
	spawn_Ymin = p_y1;
	spawn_Ymax = p_y1;
}

void ParticleGroup::setSpawnArea(float p_x1, float p_y1, float p_x2, float p_y2)
{
	if (p_x1 <= p_x2)
	{
		spawn_Xmin = p_x1;
		spawn_Xmax = p_x2;
	}
	else
	{
		spawn_Xmin = p_x2;
		spawn_Xmax = p_x1;
	}

	if (p_y1 <= p_y2)
	{
		spawn_Ymin = p_y1;
		spawn_Ymax = p_y2;
	}
	else
	{
		spawn_Ymin = p_y2;
		spawn_Ymax = p_y1;
	}
}

void ParticleGroup::setSpawnDirection(float p_dirFrom, float p_dirTo, int orientation)
{
	spawn_directionFrom = p_dirFrom;
	spawn_directionTo = p_dirTo;
	spawn_directionOrientation = (orientation >= 0) ? 1 : -1;
}

ParticleGroup::~ParticleGroup()
{
}
