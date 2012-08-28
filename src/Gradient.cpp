#include "Gradient.h"

#include "Misc.h"
#include "stdlib.h"

#include <iostream>
using std::cout;
using std::endl;


// not sure what happens if two same colors next to each other
Gradient::Gradient(int p_red, int p_green, int p_blue) :
		Color(p_red, p_green, p_blue)
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
		return Color(red,green,blue);
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
