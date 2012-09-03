/*
 * Emitter.cpp
 *
 *  Created on: Aug 26, 2012
 *      Author: stashell
 */

#include "Emitter.h"

Emitter::Emitter(Shape* p_emitShape)
{
	emitShape = p_emitShape;

}

Point Emitter::emitPosition()
{
	return emitShape->getInsidePoint();
}

Point Emitter::emitVector()
{
	return Point(0, 70);
}


void Emitter::setEmitLocation(Point p_location)
{
	emitShape->setLocation(p_location);
}

Emitter::~Emitter()
{
	// TODO Auto-generated destructor stub
}

