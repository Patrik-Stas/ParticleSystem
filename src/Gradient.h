 #ifndef GRADIENT_H
#define GRADIENT_H

#include <vector>
#include "Color.h"

class Gradient : public Color
{

    public:

        enum STATUS
        {
            ON_MILESTONE,
            BETWEEN_MILESTONE
        };

        Gradient(int p_red, int p_green, int p_blue);
        void shiftColor();
        std::vector<Color> milestones;
        int milestonePos;
        float speed; // 0-1
        STATUS status;
        friend ostream& operator<<(ostream& output, const Gradient& gradient);

    protected:
        float setShifts();
        Color getNextColor();

        float redShift;
        float greenShift;
        float blueShift;

        int shiftsLeft;
};

#endif // GRADIENT_H
