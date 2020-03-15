#include "astm.h"
#include <ctime>
#include <math.h>

double JD(int y, int m, int d, int h, int mi, double s)
	{

	double jd, dd ;

	dd = d_d(2000, 1, 1, 12, 0, 0, y, m, d, h, mi, s) ;

	jd = 2451545.0 + dd ;

	return jd ;

	}

double d_d(int y0, int m0, int d0, int h0, int mi0, float s0, int y, int m, int d, int h, int mi, double s)
	{

	struct std::tm a = { s0, mi0, h0, d0, m0 - 1, y0 - 1900 } ;

	struct std::tm b = { s, mi, h, d, m - 1, y - 1900 } ;

	std::time_t x = std::mktime(&a);

	std::time_t z = std::mktime(&b);

	long double difference = std::difftime(z, x) * 0.000011574074074074073 ;

	return difference ;

	}

double GMST(int y, int m, int d, int h, int mi, double s)
	{

	double D, T, gmst ;

	D = JD(y, m, d, 0, 0, 0) - 2451545 ;
	T = D / 36525 ;

	gmst = 24110.54841 + 8640184.812866 * T + 0.093104 * T * T
		- 0.00000632 * T * T * T ;

	gmst *= 0.0002777777777777778 ;
	gmst += ( h + mi * 0.0166666666666 + s * 0.0002777777777777 ) * 1.0027379093382884 ;
	gmst = fmod(gmst, 24.0) ;

	return gmst ;

	}

