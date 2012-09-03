/*
 * ParticleColorManager.h
 *
 *  Created on: Aug 31, 2012
 *      Author: stashell
 */

#ifndef PARTICLECOLORMANAGER_H_
#define PARTICLECOLORMANAGER_H_

#include "ParticleGroup.h"
#include "Color.h"
#include "Gradient.h"

enum COLOR_CALCULATION_BY
{
	RED_CONSTANT,
	GREEN_CONSTANT,
	BLUE_CONSTANT,
	PREVIOUS_RED_CONSTANT,
	PREVIOUS_GREEN_CONSTANT,
	PREVIOUS_BLUE_CONSTANT,
	VECTORX,
	VECTORY
};

std::ostream& operator<<( std::ostream& ostr, const COLOR_CALCULATION_BY& pt);

class ParticleColorManager
{
public:
	ParticleColorManager();
	void updateColors(ParticleGroup* particleGroup, int framerate );
	void changeColorScheme();
	void setColorScheme(COLOR_CALCULATION_BY p_redColorCalculation,
			COLOR_CALCULATION_BY p_greenColorCalculation, COLOR_CALCULATION_BY p_blueColorCalculation);
	int calculateColor(COLOR_CALCULATION_BY& calculateBy, Particle*& particle);
	Color getNewColor(Particle* particle);
	virtual ~ParticleColorManager();
	bool isTransiting();
	float getTrasitionLength() const;
	void setTrasitionLength(float trasitionLength);

protected:
	COLOR_CALCULATION_BY redColorCalculation;
	COLOR_CALCULATION_BY greenColorCalculation;
	COLOR_CALCULATION_BY blueColorCalculation;

	COLOR_CALCULATION_BY previousRedColorCalculation;
	COLOR_CALCULATION_BY previousGreenColorCalculation;
	COLOR_CALCULATION_BY previousBlueColorCalculation;

	float trasitionRunnedSeconds;
	float trasitionLength;

	int redColorConstant;
	int greenColorConstant;
	int blueColorConstant;

	int previousRedColorConstant;
	int previousGreenColorConstant;
	int previousBlueColorConstant;
};

#endif /* PARTICLECOLORMANAGER_H_ */
