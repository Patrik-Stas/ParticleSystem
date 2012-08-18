 #include "Color.h"

Color::Color(int p_red, int p_green, int p_blue)
{
    red = p_red;
    green = p_green;
    blue = p_blue;
}

ostream& operator<<(ostream& output, const Color& color) {
    output << "Color (" <<  color.red << ", " << color.green << "," << color.blue << ")";
    return output;
}

Color::~Color()
{
    //dtor
}
