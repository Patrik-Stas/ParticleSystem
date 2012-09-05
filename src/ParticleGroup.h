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
#include "Emitter.h"
#include "ParticleActionEnum.h"

using std::list;

/// represents
class ParticleGroup
{
public:
	ParticleGroup();
	list<Particle*> particles;
	~ParticleGroup();
	void setBoundAction(PARTICLE_ACTION boundAction);
	void setParticlesCount(int p_count);
	void addParticles(int p_count);
	void removeParticles(int p_count);
	void addParticleAt(Point p_spawnPoint);
	void addParticle(Particle* object);
	void setRandVect();
	void processData(float framerate);
	void applyPhysics( ParticlePhysics* particlePhysics, GravityPoint* gravityPoint);
	void checkBounds();
	void respawn(std::list<Particle*>::iterator particle);
	int getParticleCount();
	void setScaledSize(float p_scaledSize);
	float getScaledSize();
	void setAlpha(int p_alpha);
	float getAlpha();
	void paint(sf::RenderWindow* window);
	void setDefaultScaledSize(float defaultScaledSize);
	void setDefaultWeight(float defaultWeight);
	void setEmitter( Emitter* emitter);
	void setMoveableArea( Shape* moveableArea);
	void setParticleSprite( sf::Sprite particleSprite);

private:
	ParticlePhysics* particlePhysics;
	Shape* moveableArea;
	Emitter* emitter;
	PARTICLE_ACTION boundAction;
	float defaultWeight;
	sf::Sprite particleSprite;
	float defaultScaledSize;
};

#endif /* PARTICLEGROUP_H_ */
