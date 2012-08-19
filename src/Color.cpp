#include "Color.h"
#include <iostream>

Color::Color(int p_red, int p_green, int p_blue)
{
	red = p_red;
	green = p_green;
	blue = p_blue;
}

std::ostream& operator<<(ostream& output, const Color& color)
{
	output << "Color (" << color.red << ", " << color.green << "," << color.blue
			<< ")";
	return output;
}

Color::~Color()
{
	//dtor
}

float Color::getBlue() const
{
	return blue;
}

void Color::setBlue(float blue)
{
	this->blue = blue;
}

float Color::getGreen() const
{
	return green;
}

void Color::setGreen(float green)
{
	this->green = green;
}

float Color::getRed() const
{
	return red;
}

void Color::setRed(float red)
{
	this->red = red;
}
