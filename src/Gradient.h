#ifndef GRADIENT_H
#define GRADIENT_H

#include <vector>
#include "Color.h"

class Gradient: public Color
{

public:


	Gradient(int p_red, int p_green, int p_blue);
	void shiftColor();
	std::vector<Color> colors;
	float speed; // 0-1
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
