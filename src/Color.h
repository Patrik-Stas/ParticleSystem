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

        int getRed() {return red;}
        int getGreen() {return green;}
        int getBlue() {return blue;}

        float red;
        float green;
        float blue;

        friend ostream& operator<<(ostream& output, const Color& color);
};

#endif // COLOR_H
