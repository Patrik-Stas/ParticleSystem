 #ifndef MISC_H
#define MISC_H

#include <string>
#include <sstream>
#include <cstdio>
#include <ctime>
#include <string.h>


int maxValue(int m, int n);
std::string getString(int number);
std::string getString(float number);
std::string getActualTime();
int trimValue(int value, int min, int max);
float trimValue(float value, float min, float max);

#endif // MISC_H
