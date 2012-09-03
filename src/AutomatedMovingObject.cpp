/*
 * AutomatedMovingObject.cpp
 *
 *  Created on: Aug 28, 2012
 *      Author: stashell
 */

#include "AutomatedMovingObject.h"

AutomatedMovingObject::AutomatedMovingObject()
{
	dynamics = speed = 0;
	iterations = 40;
	destinationPoint = Point(225.f, 123.f);
}

Point AutomatedMovingObject::getNextPosition(int framerate)
{
	int angleDifference;
	if ((angleDifference = movingObject.angleDifference(destinationPoint)) > 40)
	{
		movingObject.turnLeft(130);
		if (!iterations--)
		{
			iterations = 40;
			destinationPoint = moveableArea->getInsidePoint();
		}
	}
	else
	{
		movingObject.setSpeed(220);
	}
	if (movingObject.getPosition().isCloserThan(destinationPoint, 10))
	{
		destinationPoint = moveableArea->getInsidePoint();
		iterations=50;
	}
	movingObject.processData(framerate);
	return movingObject.getPosition();
}

Point AutomatedMovingObject::getCurrentPosition()
{
	return movingObject.getPosition();
}

float AutomatedMovingObject::getDirection()
{
	return movingObject.getDirection();
}

void AutomatedMovingObject::paint(sf::RenderWindow* appWindow)
{
	Point position = getCurrentPosition();
	Point destination = getCurrentDestination();

	sf::CircleShape destinationCircle(10,40);
	sf::RectangleShape movingRectangle = sf::RectangleShape(sf::Vector2f(15,6));

	movingRectangle.setRotation(movingObject.getDirection());
	movingRectangle.setPosition(sf::Vector2f(position.x, position.y));
	appWindow->draw(movingRectangle);

	destinationCircle.setPosition(destination.x,destination.y);
	destinationCircle.setFillColor(sf::Color(200,200,200,200));
	destinationCircle.setPosition(destination.x, destination.y);
	destinationCircle.setFillColor(sf::Color(230, 0, 0));
	appWindow->draw(destinationCircle);
}

Point AutomatedMovingObject::getCurrentDestination()
{
	return destinationPoint;
}

AutomatedMovingObject::~AutomatedMovingObject()
{
	// TODO Auto-generated destructor stub
}

float AutomatedMovingObject::getDynamics() const
{
	return dynamics;
}

void AutomatedMovingObject::setDynamics(float dynamics)
{
	this->dynamics = dynamics;
}

void AutomatedMovingObject::setMoveableArea(Shape* moveableArea)
{
	this->moveableArea = moveableArea;
}

float AutomatedMovingObject::getSpeed() const
{
	return speed;
}

void AutomatedMovingObject::setSpeed(float speed)
{
	this->speed = speed;
}
