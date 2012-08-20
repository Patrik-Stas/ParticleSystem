#ifndef GRADIENT_H
#define GRADIENT_H

#include <vector>
#include "Color.h"

class Gradient: public Color
{

public:
	Gradient(int p_red, int p_green, int p_blue);

	float speed; // 0-1
	float getSpeed() const;
	void setSpeed(float speed);

	void shiftColor();
	std::vector<Color> colors;

	friend ostream& operator<<(ostream& output, const Gradient& gradient);

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
