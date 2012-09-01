#ifndef GRADIENT_H
#define GRADIENT_H

#include <vector>
#include "Color.h"

class Gradient: public Color
{

public:
	Gradient();
	float speed; // 0-1
	float getSpeed() const;
	void setSpeed(float speed);
	void shiftColor();
	std::vector<Color> colors;

	friend ostream& operator<<(ostream& output, const Gradient& gradient);

	static Color getColorBetween(Color startColor, Color endColor, float partsTotal, float partFromStart);

protected:
	void setShifts();
	Color getNextColor();

	int colorIndex;

	float redShift;
	float greenShift;
	float blueShift;

	int shiftsLeft;
};

#endif // GRADIENT_H
