#include "console.h"
#include <QtCore>
#include <QTextStream>
#include <string>
#include "astm.h"
#include "libtecla.h"
#include <stdio.h>
#include <locale.h>

console::console()
{

}

void console::run()
{

	qDebug("\n\tWelcome to Astro Time v1.0.1\n \
	You can either use GUI or console but console have bigger precision.\n \
	It's my first time to write console application for GUI so it's far from good. \
	\n\n\tIf you need anything to know type 'help'\n") ;

	command() ;

}

void console::command()
{

	QString com ;
	QTextStream cout(stdout) ;
	QTextStream cin(stdin) ;

	cout << ">> " ;
	cout.flush() ;

	com = cin.readLine() ;
	com = com.toLower() ;


	if (com == "help")
		help() ;

	else if ( (com == "quit") or (com == "exit") )
		QCoreApplication::quit() ;

	else if (com == "")
		command() ;

	else if (com == "jd")
		jd() ;

	else
		{
		qDebug() << "\nNo such command. Please type 'help'\n" ;
		command() ;
		}

}

void console::help()
{

	qDebug("\nhelp\t-print list of commands\nexit\t-quit the program\
	\njd\t-change date and time (gregorian calendar) to JD\n") ;

	command() ;

}

void console::jd()
{

	double jday ;
	int year = 2000, month, day, hour, min, pos ;
	double sec ;
	QString input ;
	QTextStream cin(stdin) ;

	qDebug("\nPlease input date (default is January 1'st 2000 12:00:00)\
	\nyear-month-day hour:min:sec\n") ;

	input = cin.readLine() ;

	pos = input.indexOf('-') ;

	// if no character is found then pos = -1

	year = input.leftRef(pos).toInt() ;
	input.remove(0, pos + 1) ;


	pos = input.indexOf('-') ;

	if (pos == -1)
		{

		month = 1 ;
		day = 1 ;
		hour = 12 ;
		min = 0 ;
		sec = 0 ;

		}

	else
		{
		month = input.left(pos).toInt() ;
		input.remove(0, pos + 1) ;
		}

	pos = input.indexOf('-') ;

	if (pos == -1)
		{
		day = 1 ;
		hour = 12 ;
		min = 0 ;
		sec = 0 ;
		}

	else
		{
		day = input.left(pos).toInt() ;
		input.remove(0, pos + 1) ;
		}

	pos = input.indexOf(':') ;

	if (pos == -1)
		{
		hour = 12 ;
		min = 0 ;
		sec = 0 ;
		}

	else
		{
		hour = input.left(pos).toInt() ;
		input.remove(0, pos + 1) ;

		pos = input.indexOf(':') ;

		min = input.left(pos).toInt() ;
		input.remove(0, pos + 1) ;

		sec = input.toInt() ;
		}

	qDebug("\nyear: %d\nmonth: %d\nday: %d\n%d:%d:%f\n", year, month, day, hour, min, sec) ;

	jday = JD(year, month, day, hour, min, sec) ;

	qDebug("JD: %7.10f\n", jday) ;

	command() ;
}
































