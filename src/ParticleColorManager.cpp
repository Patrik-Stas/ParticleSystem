/*
 * ParticleColorManager.cpp
 *
 *  Created on: Aug 31, 2012
 *      Author: stashell
 */

#include <iostream>
#include "ParticleColorManager.h"

ParticleColorManager::ParticleColorManager()
{
	trasitionLength = 1;
	trasitionRunnedSeconds = trasitionLength;
}

bool ParticleColorManager::isTransiting()
{
	if (trasitionRunnedSeconds < trasitionLength)
		return true;
	return false;
}

ParticleColorManager::~ParticleColorManager()
{
	// TODO Auto-generated destructor stub
}

void ParticleColorManager::updateColors(ParticleGroup* particleGroup, int framerate)
{

	for (std::list<Particle*>::iterator tmpIt = particleGroup->particles.begin();
			tmpIt != particleGroup->particles.end(); tmpIt++)
	{
		(*tmpIt)->color = getNewColor(*tmpIt);
	}
	if (trasitionRunnedSeconds < trasitionLength)
		trasitionRunnedSeconds += (float) 1 / framerate;
}

void ParticleColorManager::changeColorScheme()
{
	if (isTransiting())
		return;
	previousRedColorCalculation = redColorCalculation;
	previousGreenColorCalculation = greenColorCalculation;
	previousBlueColorCalculation = blueColorCalculation;

	previousRedColorConstant = redColorConstant;
	previousGreenColorConstant = greenColorConstant;
	previousBlueColorConstant = blueColorConstant;

	trasitionRunnedSeconds = 0;

	int redFunctionId = rand() % 3;
	int greenFunctionId = rand() % 3;
	int blueFunctionId = rand() % 3;

	switch (redFunctionId)
	{
	case 0:
	{
		redColorCalculation = VECTORX;
		break;
	}
	case 1:
	{
		redColorCalculation = VECTORY;
		break;
	}
	case 2:
	{
		redColorCalculation = RED_CONSTANT;
		redColorConstant = rand() % 205 + 50;
		break;
	}
	}
	switch (greenFunctionId)
	{
	case 0:
	{
		greenColorCalculation = VECTORX;
		break;
	}
	case 1:
	{
		greenColorCalculation = VECTORY;
		break;
	}
	case 2:
	{
		greenColorCalculation = GREEN_CONSTANT;
		redColorConstant = rand() % 205 + 50;
		break;
	}
	}
	switch (blueFunctionId)
	{
	case 0:
	{
		blueColorCalculation = VECTORX;
		break;
	}
	case 1:
	{
		blueColorCalculation = VECTORY;
		break;
	}
	case 2:
	{
		blueColorCalculation = BLUE_CONSTANT;
		redColorConstant = rand() % 205 + 50;
		break;
	}
	}
}

void ParticleColorManager::setColorScheme(COLOR_CALCULATION_BY p_redColorCalculation,
		COLOR_CALCULATION_BY p_greenColorCalculation, COLOR_CALCULATION_BY p_blueColorCalculation)
{
	redColorCalculation = p_redColorCalculation;
	greenColorCalculation = p_greenColorCalculation;
	blueColorCalculation = p_blueColorCalculation;
}

Color ParticleColorManager::getNewColor(Particle* particle)
{

	Color newColor(calculateColor(redColorCalculation, particle), calculateColor(greenColorCalculation, particle),
			calculateColor(blueColorCalculation, particle), particle->color.getAlpha());
	if (trasitionRunnedSeconds < trasitionLength)
	{
		Color previousColor(calculateColor(previousRedColorCalculation, particle),
				calculateColor(previousGreenColorCalculation, particle),
				calculateColor(previousBlueColorCalculation, particle), particle->color.getAlpha());
		return Gradient::getColorBetween(previousColor, newColor, trasitionLength, trasitionRunnedSeconds);
	}
	else
		return newColor;

}

int ParticleColorManager::calculateColor(COLOR_CALCULATION_BY& calculateBy, Particle*& particle)
{
	if (calculateBy == VECTORX)
	{
		return abs(particle->getVectorX()) + 80;
	}
	else if (calculateBy == VECTORY)
	{
		return abs(particle->getVectorY()) + 80;
	}
	else if (calculateBy == RED_CONSTANT)
	{
		return redColorConstant;
	}
	else if (calculateBy == GREEN_CONSTANT)
	{
		return greenColorConstant;
	}
	else if (calculateBy == BLUE_CONSTANT)
	{
		return blueColorConstant;
	}
	else if (calculateBy == PREVIOUS_RED_CONSTANT)
	{
		return previousRedColorConstant;
	}
	else if (calculateBy == PREVIOUS_GREEN_CONSTANT)
	{
		return previousGreenColorConstant;
	}
	else //if (calculateBy==PREVIOUS_BLUE_CONSTANT)
	{
		return previousBlueColorConstant;
	}

}



std::ostream& operator<<(std::ostream& ostr, const COLOR_CALCULATION_BY& colorCalculation)
{
	if (colorCalculation == VECTORX)
		ostr << "VECTORX";
	else if (colorCalculation == VECTORY)
		ostr << "VECTORY";
	else if (colorCalculation == RED_CONSTANT)
		ostr << "RED_CONSTANT";
	else if (colorCalculation == GREEN_CONSTANT)
		ostr << "GREEN_CONSTANT";
	else if (colorCalculation == BLUE_CONSTANT)
		ostr << "BLUE_CONSTANT";
	return ostr;
}

float ParticleColorManager::getTrasitionLength() const
{
	return trasitionLength;
}

void ParticleColorManager::setTrasitionLength(float p_trasitionLength)
{
	if (p_trasitionLength >= 0)
		trasitionLength = p_trasitionLength;
}
