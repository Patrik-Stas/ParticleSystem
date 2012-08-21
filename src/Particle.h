/*
 * Particle.h
 *
 *  Created on: Aug 20, 2012
 *      Author: stashell
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_

#include <math.h>
#include <climits>
#include <SFML/Graphics.hpp>

#include "Point.h"

#define PI 3.14159265

enum PARTICLE_TYPE
{
	SFML_SPRITE,
	SFML_PRIMITIVE
};

class Particle
{
public:
	Particle (float p_ax, float p_ay);
	virtual ~Particle();

    void setPosition(float p_ax, float p_ay) {ax=p_ax; ay=p_ay;};

    void setFriction   (float p_friction)    {friction = p_friction;};
    void setVectorX    (float p_vectorX)     {vectorX = p_vectorX;};
    void setVectorY    (float p_vectorY)     {vectorY = p_vectorY;};
    void setVectorXY   (float p_vectorX, float p_vectorY);

    void pushX(float p_vectorX) { vectorX+=p_vectorX; }
    void pushY(float p_vectorY) { vectorY+=p_vectorY; }
    void pushXY(float p_vectorX, float p_vectorY) { pushX(p_vectorX); pushY(p_vectorY); }

    void invertVectorX   ()    {setVectorX(-getVectorX());};
    void invertVectorY   ()    {setVectorY(-getVectorY());};
    void invertVectorXY  ()    {invertVectorX(); invertVectorY();};

    float getAx() const        {return ax;};
    float getAy() const        {return ay;};
    float getLastAx() const    {return lastAX;};
    float getLastAy() const    {return lastAY;};

    float getFriction() const {return friction;};
    float getVectorX() const  {return vectorX;};
    float getVectorY() const  {return vectorY;};

    void processData(float framerate);
    virtual void paint(sf::RenderWindow* window) const = 0;

    static Particle* getParticle(float p_ax, float p_ay, PARTICLE_TYPE type);
    static Particle* getParticle(Point p_pt, PARTICLE_TYPE type);

    static void fixDirection ();


private:
    float ax;
    float ay;
    float lastAX;
    float lastAY;

    float vectorX;
    float vectorY;
    float friction;
    float weight;
};

#endif /* PARTICLE_H_ */
