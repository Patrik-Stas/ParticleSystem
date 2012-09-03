/*
 * ParticlePhysics.h
 *
 *  Created on: Aug 26, 2012
 *      Author: stashell
 */

#ifndef PARTICLEPHYSICS_H_
#define PARTICLEPHYSICS_H_

#include "Particle.h"
#include "GravityPoint.h"


class ParticlePhysics
{
public:
	ParticlePhysics();
	void applyDownForce(Particle* particle);
	void applyGravityPoint(Particle* particle);
	bool isDownForce() const;
	void setDownForce(bool downForce);
	float getGravitation() const;
	void setGravitation(float gravitation);
	const GravityPoint* getGravityPoint() const;
	void setGravityPoint( GravityPoint** gravityPoint);
	bool isGravityPointForce() const;
	void setGravityPointForce(bool gravityPointForce);

	void fileDump(const char * filename);
	friend std::ostream& operator<<( std::ostream& ostr, const ParticlePhysics& pt);

protected:
	GravityPoint** gravityPoint;
	float gravitation;
	bool downForce;
	bool gravityPointForce;
};

#endif /* PARTICLEPHYSICS_H_ */
