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

std::string getActualTime()
{
	  time_t rawtime;
	  struct tm * timeinfo;
	  char buffer [80];
	  time ( &rawtime );
	  timeinfo = localtime ( &rawtime );
	  strftime (buffer,80,"%Y-%m-%d-%H-%M-%S",timeinfo);
	  return std::string (buffer, strlen(buffer));
}
