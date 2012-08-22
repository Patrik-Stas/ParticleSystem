/*
 * ParticlePhysics.h
 *
 *  Created on: Aug 22, 2012
 *      Author: stashell
 */

#ifndef PARTICLEPHYSICS_H_
#define PARTICLEPHYSICS_H_

#include "ParticleGroup.h"
#include "Point.h"
#include "ShapeRectangle.h"

class ParticlePhysics
{
public:
	ParticlePhysics(int p_gravitation, ShapeRectangle p_moveableArea);
	void apply(ParticleGroup* particleGroup, const Particle& gravityPoint);
	virtual ~ParticlePhysics();

	float gravitation;
private:
	ShapeRectangle moveableArea;
};

#endif /* PARTICLEPHYSICS_H_ */
