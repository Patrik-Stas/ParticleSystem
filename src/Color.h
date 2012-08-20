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
	bool operator==(Color& c1);
	bool operator!=(Color& c1);
	friend ostream& operator<<(ostream& output, const Color& color);

	float getBlue() const;
	void setBlue(float blue);
	float getGreen() const;
	void setGreen(float green);
	void setRed(float red);
	float getRed() const;

	float red;
	float green;
	float blue;

};

#endif // COLOR_H
