 #include "Misc.h"

int maxValue(int n, int m)
{
    return ( n>m ) ? n : m;
}

std::string getString(int number)
{
	std::stringstream sstr;
	sstr << number;
	return sstr.str();
}

std::string getString(float number)
{
	std::stringstream sstr;
	sstr << number;
	return sstr.str();
}
