/*
 * MovingObject.cpp
 *
 *  Created on: Aug 28, 2012
 *      Author: stashell
 */

#include "MovingObject.h"
#include <iostream>
#include <math.h>
#include <algorithm>


MovingObject::MovingObject()
{
    lastX=x=220;
    lastY=y=220;
    speed=0;
    direction=0;
    cmdUp=cmdDown=cmdLeft=cmdRight=0;
    minSpeed = 0;
    maxSpeed = 100;
}

void MovingObject::setVectMoveXY(float p_vectorX, float p_vectorY)
{
    speed=sqrt(p_vectorX*p_vectorX + p_vectorY*p_vectorY);
    direction=atan2(p_vectorY,p_vectorX)*180 / PI;
}

void MovingObject::processData(float framerate)
{
    float fpsRatio=1/framerate;

    speed+=fpsRatio*(cmdUp-cmdDown);

    if      (speed>=0)   direction-=fpsRatio*(cmdLeft-cmdRight);
    else if (speed<0)    direction-=fpsRatio*(cmdRight-cmdLeft);

    fixDirection(direction);

    lastX=x;
    lastY=y;

    x+=fpsRatio*speed*cos(direction*M_PI/180); // -direction, because of [0,0] point in computer cartesian system is in top left point
    y+=fpsRatio*speed*sin(direction*M_PI/180);

    cmdUp=0;
    cmdDown=0;
    cmdLeft=0;
    cmdRight=0;
}

void MovingObject::fixDirection (float& p_direction)
{
    while (p_direction>360)
        {p_direction-=360;}
    while (p_direction<0)
        {p_direction+=360;}
}

int MovingObject::angleDifference(Point pt)
{
	int lenghtX = pt.x - x;
	int lenghtY = pt.y - y;
	float directionToPoint = atan2(lenghtY,lenghtX)*180 / PI;
	fixDirection(directionToPoint);
	int angleDifference = std::min(abs(direction-directionToPoint), 360 - abs(direction-directionToPoint));
	if (angleDifference<0)
	{
		 std::cout << "ANGLE: " << 360 - abs(direction-directionToPoint) << std::endl ;
		 std::cout << "ABS VAL: " <<  abs(direction-directionToPoint) << std::endl;
		 std::cout << "directionOfObject: " << direction << std::endl;
		 std::cout << "directionToPoint: " << directionToPoint << std::endl;
	}
	return angleDifference;
}
