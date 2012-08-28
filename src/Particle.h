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
#include "Color.h"
#include "Constants.h"

enum PARTICLE_TYPE
{
	SFML_SPRITE,
	SFML_PRIMITIVE
};

class Particle
{
public:
	Particle (float p_ax, float p_ay, float p_weight, float scaledRadius, Color p_color);
	virtual ~Particle();

    void setPosition(float p_ax, float p_ay) {ax=p_ax; ay=p_ay;};

    void setVectorX    (float p_vectorX)     {vectorX = p_vectorX;};
    void setVectorY    (float p_vectorY)     {vectorY = p_vectorY;};
    void setVectorXY   (float p_vectorX, float p_vectorY);
    void setVectorXY   (Point pt) {vectorX = pt.x; vectorY = pt.y;};

    void pushX(float p_vectorX) { vectorX+=p_vectorX; }
    void pushY(float p_vectorY) { vectorY+=p_vectorY; }
    void pushXY(float p_vectorX, float p_vectorY) { pushX(p_vectorX); pushY(p_vectorY); }

    void invertVectorX   ()    {setVectorX(-getVectorX());};
    void invertVectorY   ()    {setVectorY(-getVectorY());};
    void invertVectorXY  ()    {invertVectorX(); invertVectorY();};

    void adjustSpeed(float multiplicator) {vectorX *= multiplicator; vectorY *= multiplicator;};
    float getSpeed();
    float getAngle();

    float getAx() const        {return ax;};
    float getAy() const        {return ay;};
    float getWeight() const    {return weight;};
    void  setWeight(float p_weight)    {weight = p_weight;};

    float getVectorX()  const  {return vectorX;};
    float getVectorY()  const  {return vectorY;};
    Point getPosition() 	   {return Point(ax, ay);};
    void  setPosition(const Point& position) {ax = position.x; ay = position.y; };
    void  stop() 			   {vectorX=0; vectorY=0;};

    void processData(float framerate);
    virtual void paint(sf::RenderWindow* window) = 0;
    virtual void setScaledSize(float p_scaledSize) = 0;
    float getScale() {return scaledSize;};

    static Particle* getParticleSfmlPrimitive(float p_ax, float p_ay, float p_weight, int maximalRadius, float scaledRadius, Color p_color = Color());
    static Particle* getParticleSfmlSprite(float p_ax, float p_ay, float p_weight,  sf::Sprite p_sprite, float scaledRadius, Color p_color = Color());

    static void fixDirection ();

    Color color;

private:
    float ax;
    float ay;

    float vectorX;
    float vectorY;
    float weight;

protected:
    float scaledSize; // 1 = normal size
};

#endif /* PARTICLE_H_ */
