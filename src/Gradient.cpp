#include "Gradient.h"

#include "Misc.h"
#include "stdlib.h"

#include <iostream>
using std::cout;
using std::endl;

// not sure what happens if two same colors next to each other
Gradient::Gradient() :
		Color(0, 255, 0)
{
	shiftsLeft = 0;
	speed = 0.03;
}

void Gradient::shiftColor()
{
	if (shiftsLeft <= 0)
		setShifts();
	else
	{
		red += redShift;
		green += greenShift;
		blue += blueShift;
		shiftsLeft--;
	}
}

void Gradient::setShifts()
{
	Color nextColor = getNextColor();
	redShift = (nextColor.getRed() - red) * speed;
	greenShift = (nextColor.getGreen() - green) * speed;
	blueShift = (nextColor.getBlue() - blue) * speed;
	shiftsLeft = (nextColor.getRed() - red) / redShift;
}

Color Gradient::getNextColor()
{
	if (colors.size() == 0)
	{
		std::cerr << "Gradient does not contain any colors";
		return Color(red, green, blue);
	}
	if ((++this->colorIndex) >= colors.size())
		colorIndex = 0;
	return Color(colors[colorIndex]);
}

float Gradient::getSpeed() const
{
	return speed;
}

void Gradient::setSpeed(float speed)
{
	this->speed = speed;
}

std::ostream& operator<<(std::ostream& output, const Gradient& gradient)
{
	output << "shifts left:" << gradient.shiftsLeft << endl << "   Gradient speed:" << gradient.speed << endl;
	output << "Color " << (Color) gradient;
	return output;  // for multiple << operators.
}

Color Gradient::getColorBetween(Color startColor, Color endColor, float partsTotal, float partFromStart)
{
	float redShift = (endColor.getRed() - startColor.getRed() ) / partsTotal;
	float greenShift = (endColor.getGreen() - startColor.getGreen()) / partsTotal;
	float blueShift = (endColor.getBlue() - startColor.getBlue()) / partsTotal;
	float alphaShift = (endColor.getAlpha() - startColor.getAlpha()) / partsTotal;
	int newRed =  startColor.getRed() + partFromStart * redShift;
	int newGreen =  startColor.getGreen() + partFromStart * greenShift;
	int newBlue =  startColor.getBlue() + partFromStart * blueShift;
	Color returnColor (abs(newRed), abs(newGreen), abs(newBlue), startColor.getAlpha());
/*	cout << "redshift :" << redShift << endl;
	cout << "addition :" <<  partFromStart * redShift << endl;
	cout << "oldRed :" << startColor.getRed() << "    returnRed : " << returnColor.getRed() << endl;
	cout << "PARTS TOTAL : " << partsTotal << endl;
	cout << "Part returned" << partFromStart << endl;
	cout << "start color " << startColor << endl;
	cout << " endColor " << endColor << endl;
	cout << "returning color" << returnColor << endl;*/
	return returnColor;
}
