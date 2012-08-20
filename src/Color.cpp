#include "Color.h"
#include <iostream>

Color::Color(int p_red, int p_green, int p_blue)
{
	setRed(p_red);
	setGreen(p_green);
	setBlue(p_blue);
}

std::ostream& operator<<(ostream& output, const Color& color)
{
	output << "Color (" << color.red << ", " << color.green << "," << color.blue << ")";
	return output;
}

Color::~Color()
{
}

float Color::getBlue() const
{
	return blue;
}

void Color::setBlue(float blue)
{
	blue = (blue > 255) ? 255 : blue;
	blue = (blue < 0) ? 0 : blue;
	this->blue = blue;
}

float Color::getGreen() const
{
	return green;
}

void Color::setGreen(float green)
{

	green = (green > 255) ? 255 : green;
	green = (green < 0) ? 0 : green;
	this->green = green;
}

float Color::getRed() const
{
	return red;
}

void Color::setRed(float red)
{
	red = (red > 255) ? 255 : red;
	red = (red < 0) ? 0 : red;
	this->red = red;
}

bool Color::operator==(Color& c1)
{
	if ((int) red == (int) c1.red && (int) green == (int) c1.green && (int) blue == (int) c1.blue)
		return true;
	else
		return false;
}

bool Color::operator!=(Color& c1)
{
	return !(*this == c1);
}
