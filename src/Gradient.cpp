 #include "Gradient.h"

#include "Misc.h"
#include "stdlib.h"

Gradient::Gradient(int p_red, int p_green, int p_blue) : Color(p_red, p_green, p_blue)
{
    shiftsLeft=0;
    speed=1;
}

void Gradient::shiftColor()
{
    if (shiftsLeft == 0) setShifts();
    else
    {
        red += redShift;
        green += greenShift;
        blue += blueShift;
        shiftsLeft--;
    }
}

float Gradient::setShifts()
{
    Color nextColor = getNextColor();
    redShift   = (nextColor.red - red ) * speed;
    greenShift = (nextColor.green - green ) * speed;
    blueShift  = (nextColor.blue - blue ) * speed;
    shiftsLeft = (nextColor.red - red)/redShift;
}

Color Gradient::getNextColor()
{
    return Color(rand()%255, rand()%255, rand()%255);
}

ostream& operator<<(ostream& output, const Gradient& gradient) {
    output << "shifts left:" << gradient.shiftsLeft << endl << "   Gradient speed:" << gradient.speed  << endl;
    output << "Color " << (Color)gradient;
    return output;  // for multiple << operators.
}
