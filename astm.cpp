#include "astm.h"
#include <math.h>
#include <stdio.h>

//	  year   month  day    hour   minute  second
double JD(int y, int m, int d, int h, int mi, double s)
	{

	double jd, dd ;

	dd = d_d(2000, 1, 1, 12, 0, 0, y, m, d, h, mi, s) ;

	jd = 2451545.0 + dd ;

	return jd ;

	}


//	   year 0  month 0 day 0   hour 0  minute 0 sec 0     year   month  day    hour   minute  second
double d_d(int y0, int m0, int d0, int h0, int mi0, double s0, int y, int m, int d, int h, int mi, double s)
	{

	int month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31} ;

	int year ;
	double diff = 0 ; // day difference

	if (y0 < y)
		{

		year = y0 + 1 ;

		if ( ( (y0 % 4) == 0 ) && ( ( (y0 % 100) != 0) || ( (y0 % 400) == 0) ) )
			month[1] = 29 ;

		diff += month[m0 - 1] - d0 + 1 ;
		diff += - double(h0) / 24 - double(mi0) / 1440 - s0 / 86400 ; // hour in day

		for (int c = m0; c < 12; c++)
			diff += month[c] ;

		// that was days to the end of year y0
		// now we will have days since y
		// because all years between are calulated later

		diff += d - 1 ;
		diff += double(h) / 24 + double(mi) / 1440 + s / 86400 ;


		if ( ( (y % 4) == 0 ) && ( ( (y % 100) != 0) || ( (y % 400) == 0) ) )
			month[1] = 29 ;

		else
			month[1] = 28 ;
	
		for(int i = 0; i < (m - 1); i++)
			diff += month[i] ;

		}


	else if (y < y0)
		{

		year = y + 1 ;

		if ( ( (y % 4) == 0 ) && ( ( (y % 100) != 0) || ( (y % 400) == 0) ) )
			month[1] = 29 ;

		diff += month[m - 1] - d + 1 ;
		diff += - double(h) / 24 - double(mi) / 1440 - s / 86400 ; // hour in day

		for (int c = m; c < 12; c++)
			diff += month[c] ;

		// that was days to the end of year y
		// now we will have days since y0
		// because all years between are calulated later

		diff += d0 - 1 ;
		diff += double(h0) / 24 + double(mi0) / 1440 + s0 / 86400 ;


		if ( ( (y0 % 4) == 0 ) && ( ( (y0 % 100) != 0) || ( (y0 % 400) == 0) ) )
			month[1] = 29 ;

		else
			month[1] = 28 ;
	
		for(int i = 0; i < (m0 - 1); i++)
			diff += month[i] ;

		}

	else // if y0 == y
		{

		if ( ( (y0 % 4) == 0 ) && ( ( (y0 % 100) != 0) || ( (y0 % 400) == 0) ) )
			month[1] = 29 ;

		if (m0 < m)
			{

			diff += month[m0 - 1] - d0 + 1 ;
			diff += -double(h0) / 24 - double(mi0) / 1440 - s0 / 86400 ;

			diff += d - 1 ;
			diff += double(h) / 24 + double(mi) / 1440 + s / 86400 ;
			
			for (int i = m0; i < m - 1; i++)
				diff += month[i] ;

			}

		else if (m0 > m)
			{

			diff += month[m - 1] - d + 1 ;
			diff += -double(h) / 24 - double(mi) / 1440 - s / 86400 ;

			diff += d0 - 1 ;
			diff += double(h0) / 24 + double(mi0) / 1440 + s0 / 86400 ;
			
			for (int i = m; i < m0 - 1; i++)
				diff += month[i] ;

			// printf("lol\n") ;
			diff = -diff ;

			}

		else
			{

			diff += d - d0 ;
			diff += double(h) / 24 + double(mi) / 1440 + s / 86400 ;	
			diff += -double(h0) / 24 - double(mi0) / 1440 - s0 / 86400 ;

			}

		}


	for (int i = 1; i < abs(y0 - y); i++)
		{

		if ( ( (year % 4) == 0 ) && ( ( (year % 100) != 0) || ( (year % 400) == 0) ) ) // leap?
			diff += 366 ;

		else
			diff += 365 ;

		year++ ;

		}

	if (y < y0)
		diff = -diff ;	

	return diff ;

	}

double GMST(int y, int m, int d, int h, int mi, double s)
	{

	double D, T, gmst ;

	D = JD(y, m, d, 0, 0, 0) - 2451545 ;
	T = D / 36525 ;

	gmst = 24110.54841 + 8640184.812866 * T + 0.093104 * T * T
		- 0.00000632 * T * T * T ;

	gmst *= 0.0002777777777777778 ;
	gmst += ( h + mi * 0.01666666666667 + s * 0.0002777777777777 ) * 1.0027379093382884 ;
	gmst = fmod(gmst, 24.0) ;

	return gmst ;

	}



double TAI(int y, int m, int d, int h, int mi, double s)
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



double GPS(int y, int m, int d, int h, int mi, double s)
	{

	double gps ;

	gps = TAI(y, m, d, h, mi, s) - 5.27777777777777777778e-3 ;
	
	if (gps < 0)
		gps += 24 ;

	return gps ;

	}


double TT(int y, int m, int d, int h, int mi, double s)
	{

	double tt ;

	tt = fmod( TAI(y, m, d, h, mi, s) + 8.94e-3, 24 ) ;

	return tt ;

	}
