/*
 * Emitter.h
 *
 *  Created on: Aug 26, 2012
 *      Author: stashell
 */

#ifndef EMITTER_H_
#define EMITTER_H_

#include "Shape.h"

class Emitter
{
public:
	Emitter(Shape* p_emitShape);
	Point emitPosition();
	Point emitVector();
	void  setEmitLocation(Point p_location);
	virtual ~Emitter();
private:
	Shape* emitShape;

};

#endif /* EMITTER_H_ */
