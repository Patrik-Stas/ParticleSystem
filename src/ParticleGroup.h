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

using std::list;

class ParticleGroup
{
public:
	ParticleGroup();
	list<Particle*> particles;

	ParticleGroup(ShapeRectangle p_moveableArea, sf::Sprite p_defaultSprite );
	~ParticleGroup();

	void pushSpawnparticles(int p_count);
	void pushObject(Point p_spawnPoint);
	void pushObject(Particle* object);
	void setRandVect();
	void processData(float framerate, Point gravityPoint );

private:
	ShapeRectangle moveableArea;
	int defFriction;
	sf::Sprite particleSprite;
};

#endif /* PARTICLEGROUP_H_ */
