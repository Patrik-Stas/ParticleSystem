/*
 * MovingObject.h
 *
 *  Created on: Aug 28, 2012
 *      Author: stashell
 */

#ifndef MOVINGOBJECT_H_
#define MOVINGOBJECT_H_
/*
StaEn[Stacho Engine] 0.2 - simple 2d movement engine

StaEn object is defined by
    - Position (available relative and absolute coordinates)

        (relative coordinates - top left point of object)

            xy_ _ _ _ _ _ _
            |       width
            |
            |height
            |

        (absolute coordinates - center of the object)

    - Size (width, height)
    - Speed
    - Direction (0-360)
     --------------------
     -\
     - \
     -  \
     -   \ (Direction 60)

Provide functions for instant object reinitialization
Object movement handling
    - speed and angle by speeding, breaking, turning fuctions
    - speed and angle by vectors

StaEn is using pixel metric system
    - speed 1 == 1 pixel per second
    - angle 45 == move in angle of 45 degrees eg. same as [1,1] vector orientation
    - speed up (10)   == if called every iteration in 1 second, object increase its speed by 10
    - break down (10) == if called every iteration in 1 second, object decrease its speed by 10
    - turn left(90)  ==  in 1 second, object makes 90 degree left turn  (+90)
    - turn right(90) ==  in 1 second, object makes 90 degree right turn (-90)
As long these functions depends on time and fps, we have to send framerate to processing function as parameter

StaEn moves same with any FPS (so processing is framerate dependent)

Object restrictions
    - maximal/minimal speed (recommend set set min speed to 0 if not necessary (er. vehicle driving backwards))
    - allowed move space (you can set how object behaves when cross the bounds by boundAction (ACTION enum) )
*/


#include <math.h>
#include <climits>
#include "Constants.h"
#include "Point.h"

class MovingObject
{
    public:
        MovingObject();

        void turnRight    (float p_cmdRight)     {cmdRight += p_cmdRight;};
        void turnLeft     (float p_cmdLeft)      {cmdLeft  += p_cmdLeft;};
        void speedUp      (float p_cmdUp)        {cmdUp    += p_cmdUp;};
        void breakDown    (float p_cmdDown)      {cmdDown  += p_cmdDown;};

        void setPosition(float p_x, float p_y) {x=p_x; y=p_y;};
        void setX       (float p_x)             {x=p_x;};
        void setY       (float p_y)             {y=p_y;};

        void setDirection  (float p_direction)   {direction= p_direction;};
        void setSpeed      (float p_speed)       {speed    = p_speed;};
        void setVectMoveX  (float p_vectorX)     {setVectMoveXY(p_vectorX, getVectMoveY());};
        void setVectMoveY  (float p_vectorY)     {setVectMoveXY(getVectMoveX(), p_vectorY);};
        void setVectMoveXY (float p_vectorX, float p_vectorY);
        void invertVectX   ()                    {setVectMoveX(-getVectMoveX());};
        void invertVectY   ()                    {setVectMoveY(-getVectMoveY());};
        void invertVectXY  ()                    {invertVectX(); invertVectY();};

        void set_maxSpeed   (int p_max=INT_MAX)   {maxSpeed=p_max;};
        void set_minSpeed   (int p_min=INT_MIN)   {minSpeed=p_min;};

        float getX()         {return x;};
        float getY()         {return y;};
        float getLastX()     {return lastX;};
        float getLastY()     {return lastY;};

        float getDirection()  {return direction;};
        float getSpeed()      {return speed;};
        float getVectMoveX()  {return (cos(direction*M_PI/180) * speed);};
        float getVectMoveY()  {return (sin(direction*M_PI/180) * speed);};

        void processData(float framerate);
        Point getPosition() {return Point(x, y);};

        static void fixDirection (float& direction);

        int angleDifference(Point pt);
        void adjustSpeed();
        void adjustAngleTo(Point p_destination);

    private:
        float x;
        float y;
        float lastX;
        float lastY;

        float direction;
        float speed;

        float cmdLeft;
        float cmdRight;
        float cmdUp;
        float cmdDown;

        int maxSpeed;
        int minSpeed;
};

#endif /* MOVINGOBJECT_H_ */
