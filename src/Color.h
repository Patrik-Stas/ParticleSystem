#ifndef COLOR_H
#define COLOR_H

#include <iostream>
using std::ostream;
using std::endl;

class Color
{
public:
	Color(int p_red, int p_green, int p_blue, int alpha=255);
	Color();
	virtual ~Color();
	bool operator==(Color& c1);
	bool operator!=(Color& c1);
	friend ostream& operator<<(ostream& output, const Color& color);

	float getBlue() const;
	void setBlue(int blue);
	float getGreen() const;
	void setGreen(int green);
	void setRed(int red);
	float getRed() const;
	void setAlpha(int red);
	float getAlpha() const;

protected:
	void checkColorValue(int& p_colorVal);
	float red;
	float green;
	float blue;
	float alpha;


};

#endif // COLOR_H
