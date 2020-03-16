#include "astm.h"
#include <ctime>
#include <math.h>

//	  year   month  day    hour   minute  second
double JD(int y, int m, int d, int h, int mi, float s)
	{

	double jd, dd ;

	dd = d_d(2000, 1, 1, 12, 0, 0, y, m, d, h, mi, s) ;

	jd = 2451545.0 + dd ;

	return jd ;

	}


//	   year 0  month 0 day 0   hour 0  minute 0 sec 0     year   month  day    hour   minute  second
double d_d(int y0, int m0, int d0, int h0, int mi0, float s0, int y, int m, int d, int h, int mi, float s)
	{

	struct std::tm a = { s0, mi0, h0, d0, m0 - 1, y0 - 1900 } ;

	struct std::tm b = { s, mi, h, d, m - 1, y - 1900 } ;

	std::time_t x = std::mktime(&a);

	std::time_t z = std::mktime(&b);

	long double difference = std::difftime(z, x) * 0.000011574074074074073 ;

	return difference ;

	}

double GMST(int y, int m, int d, int h, int mi, float s)
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



double UTC2TAI(int y, int m, int d, int h, int mi, double s)
	{

	int n = 2020 - 1972 + 1 ; // limit array
	double TAI ;

	int leap[n][2]	= { {1,1}, {0,1}, {0,1}, {0,1}, {0,1}, {0,1}, {0,1}, {0,1}, {0,0}, {1,0},
			    {1,0}, {1,0}, {0,0}, {1,0}, {0,0}, {0,1}, {0,0}, {0,1}, {0,1}, {0,0},
			    {1,0}, {1,0}, {1,0}, {0,1}, {0,0}, {1,0}, {0,1}, {0,0}, {0,0}, {0,0},
			    {0,0}, {0,0}, {0,0}, {0,1}, {0,0}, {0,0}, {0,1}, {0,0}, {0,0}, {0,0},
			    {1,0}, {0,0}, {0,0}, {1,0}, {0,1}, {0,0}, {0,0}, {0,0}, {0,0} } ; // leap seconds each year since 1972.
										// Yes, I am masochist
	int l = 10 ; // leap seconds
	
	for (int i = 0; i < (y - 1972); i++)
		{

		if (i == n)
			break ;

		l += leap[i][0] + leap[i][1] ;

		}

	if ( ( (y - 1972) < n ) and (m > 6) )	
		l += leap[y - 1972][0] ;

	TAI = h + double(mi) * 0.01666666666666666 + (s + double(l)) * 2.777777777777777777e-4 ;

	return TAI ;

	}
