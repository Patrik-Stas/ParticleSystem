/*
 * ParticleGroup.h
 *
 *  Created on: Aug 20, 2012
 *      Author: stashell
 */

#ifndef PARTICLEGROUP_H_
#define PARTICLEGROUP_H_

#include <list>
#include "Particle.h"
#include "ShapeRectangle.h"
#include "ParticlePhysics.h"

using std::list;

class ParticleGroup
{
public:
	ParticleGroup();
	list<Particle*> particles;

	ParticleGroup(ParticlePhysics* p_particlePhysics, ShapeRectangle p_spawnArea, ShapeRectangle p_moveableArea, float p_defaultWeight,
			float p_defaultScaledSize, sf::Sprite p_defaultSprite);
	~ParticleGroup();
	void setParticlesCount(int p_count);
	void addParticles(int p_count);
	void removeParticles(int p_count);
	void addParticleAt(Point p_spawnPoint);
	void addParticle(Particle* object);
	void setRandVect();
	void processData(float framerate);
	void applyPhysics();
	void respawn(std::list<Particle*>::iterator particle, Shape* shape);
	int getParticleCount();
	void setScaledSize(float p_scaledSize);

private:
	ParticlePhysics* particlePhysics;
	ShapeRectangle spawnArea;
	ShapeRectangle moveableArea;
	float defaultWeight;
	sf::Sprite particleSprite;
	float defaultScaledSize;
};

#endif /* PARTICLEGROUP_H_ */
