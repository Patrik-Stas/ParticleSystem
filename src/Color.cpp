#include <iostream>

#include "Color.h"

Color::Color(int p_red, int p_green, int p_blue, int p_alpha)
{
	setRed(p_red);
	setGreen(p_green);
	setBlue(p_blue);
	setAlpha(p_alpha);
}

Color::Color()
{
	setRed(0);
	setGreen(255);
	setBlue(0);
	setAlpha(50);
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

void Color::setBlue(int p_blue)
{
	checkColorValue(p_blue);
	blue = p_blue;
}

float Color::getGreen() const
{
	return green;
}

void Color::setGreen(int p_green)
{
	checkColorValue(p_green);
	green = p_green;
}

float Color::getRed() const
{
	return red;
}

void Color::setRed(int p_red)
{
	checkColorValue(p_red);
	red = p_red;
}

void Color::setAlpha(int p_alpha)
{
	checkColorValue(p_alpha);
	alpha = p_alpha;
}

float Color::getAlpha() const
{
	return alpha;
}


void Color::checkColorValue(int& p_colorVal)
{
	p_colorVal = (p_colorVal > 255) ? 255 : p_colorVal;
	p_colorVal = (p_colorVal < 0) ? 0 : p_colorVal;
}

bool Color::operator==(Color& c1)
{
	if (	(int) red   == (int) c1.red   &&
			(int) green == (int) c1.green &&
			(int) blue  == (int) c1.blue  &&
			(int) alpha == (int) c1.alpha   )
		return true;
	else
		return false;
}

bool Color::operator!=(Color& c1)
{
	return !(*this == c1);
}

