#ifndef COLOR_H
#define COLOR_H

#include <iostream>
using std::ostream;
using std::endl;

class Color
{
public:
	Color(int p_red, int p_green, int p_blue);
	virtual ~Color();
	friend ostream& operator<<(ostream& output, const Color& color);

	float red;
	float green;
	float blue;

	float getBlue() const;
	void setBlue(float blue);
	float getGreen() const;
	void setGreen(float green);
	void setRed(float red);
	float getRed() const;

};

#endif // COLOR_H
