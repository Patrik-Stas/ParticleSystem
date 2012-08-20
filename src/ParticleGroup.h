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

using std::list;

class ParticleGroup
{
public:
	ParticleGroup();
	list<Particle*> particles;

	ParticleGroup(const float p_spawnArea_X1, const float p_spawnArea_Y1, const float p_spawnAreaX2,
			const float p_spawnAreaY2 );
	~ParticleGroup();

	float generate_spawnX();
	float generate_spawnY();
	float generate_spawnDirection();

	void pushSpawnparticles(int p_count);
	void pushObject(float p_x, float p_y, float p_direction);
	void pushObject(Particle* object);
	void setRandVect();
	void processData(float framerate);
	void setSpawnPoint(float p_x1, float p_y1);
	void setSpawnArea(float p_x1, float p_y1, float p_x2, float p_y2);
	void setSpawnDirection(float p_dirFrom, float p_dirTo, int orientation);

private:
	int spawn_directionFrom;
	int spawn_directionTo;
	int spawn_directionOrientation;
	int spawn_Xmax;
	int spawn_Xmin;
	int spawn_Ymax;
	int spawn_Ymin;
	int defFriction;
};

#endif /* PARTICLEGROUP_H_ */
