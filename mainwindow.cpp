#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "astm.h"
#include <string>
#include <math.h>
#include <ctime>
#include <chrono>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	timer = new QTimer(this) ;
	connect( timer, SIGNAL( timeout() ), this, SLOT( on_set_time_clicked() ) ) ;

	std::time_t now = std::time(NULL) ;
	std::time_t local = std::mktime(std::localtime(&now)) ;
	std::time_t gmt = std::mktime(std::gmtime(&now)) ;

	to = static_cast<int> (local - gmt) * 1000 ;

	float h = to * 2.7777777777e-7 ;

	ui -> time_zone_h -> setText(QString::number(h)) ;

}

MainWindow::~MainWindow()
{
	delete ui;
}


void MainWindow::changed_time()
	{

	int UT_h, UT_m, gm_h, gm_m, LST_h, LST_m ;
	double UT_s, seconds, jd, gmst, gm_s, LST, LST_s ;

	UT = hour - tz ;

	if (UT < 0)
		{

		UT += 24 ;

		seconds = int( d_d(1970, 1, 1, 0, 0, 0, year, month, day, 0, 0, 0) * 86400 - 86400 ) ;
		time_t now = (time_t)seconds ;
		struct tm *t = localtime(&now);

		year_2 = t -> tm_year + 1900 ;
		month_2 = t -> tm_mon + 1 ;
		day_2 = t -> tm_mday ;

		}

	else if (UT > 24)
		{

		UT -= 24 ;

		seconds = int( d_d(1970, 1, 1, 0, 0, 0, year, month, day, 0, 0, 0) * 86400 + 86400 ) ;
		time_t now = (time_t)seconds ;
		struct tm *t = localtime(&now);

		year_2 = t -> tm_year + 1900 ;
		month_2 = t -> tm_mon + 1 ;
		day_2 = t -> tm_mday ;

		}

	else
		{

		year_2 = year ;
		month_2 = month ;
		day_2 = day ;

		}

	UT = ceil(UT * 1e7) * 1e-7 ;

	UT_h = int(UT) ;
	UT_m = int( (UT - UT_h) * 60 ) ;
	UT_s = (UT - UT_h) * 3600 - UT_m * 60 ;

	ui -> uth -> setText( QString::number(UT_h) ) ;
	ui -> utm -> setText( QString::number(UT_m) ) ;
	ui -> uts -> setText( QString::number(UT_s, 'f', 3) ) ;

	jd = JD(year_2, month_2, day_2, UT_h, UT_m, UT_s) ;
	ui -> j_day -> setText( QString::number(jd, 'f', 8) ) ;



	gmst = GMST(year_2, month_2, day_2, UT_h, UT_m, UT_s) ;

	gm_h = int(gmst) ;
	gm_m = int( (gmst - gm_h) * 60) ;
	gm_s = (gmst - gm_h) * 3600 - gm_m * 60 ;

	ui -> g_h -> setText(QString::number(gm_h)) ;
	ui -> g_m -> setText(QString::number(gm_m)) ;
	ui -> g_s -> setText(QString::number(gm_s, 'f', 3)) ;

	LST = fmod(gmst + lo, 24) ;

	if (LST < 0)
		LST += 24 ;

	LST_h = int(LST) ;
	LST_m = int( (LST - LST_h) * 60) ;
	LST_s = (LST - LST_h) * 3600 - LST_m * 60 ;

	ui -> lst_h -> setText(QString::number(LST_h)) ;
	ui -> lst_m -> setText(QString::number(LST_m)) ;
	ui -> lst_s -> setText(QString::number(LST_s, 'f', 3)) ;

	}

void MainWindow::on_time_userTimeChanged(const QTime &time)
{
	hour = time.hour() + double(time.minute()) / 60 + double(time.second()) / 3600 + double(time.msec()) / 3600000 ;

	changed_time() ;
}

void MainWindow::on_time_zone_h_textChanged(const QString &arg1)
{
	if (arg1[0] == "-")
		tz = -abs( arg1.toDouble() ) - ( ui -> time_zone_m -> text().toDouble() ) / 60 ;
	else
		tz = abs( arg1.toDouble() ) + ( ui -> time_zone_m -> text().toDouble() ) / 60 ;

	changed_time() ;
}

void MainWindow::on_time_zone_m_textChanged(const QString &arg1)
{
	if (ui -> time_zone_h -> text()[0] == "-")
		tz = -abs( ui -> time_zone_h -> text().toDouble() ) - ( arg1.toDouble() ) / 60 ;
	else
		tz = abs( ui -> time_zone_h -> text().toDouble() ) + ( arg1.toDouble() ) / 60 ;

	changed_time() ;
}

void MainWindow::on_date_userDateChanged(const QDate &date)
{

	day = date.day() ;
	month = date.month() ;
	year = date.year() ;

	changed_time() ;

}

void MainWindow::on_longitude_textChanged(const QString &arg1)
{
	lo = arg1.toDouble() * 0.066666666666666 ; // degrees to hours
}

void MainWindow::on_set_time_clicked()
{

	using namespace std::chrono ;

	auto now = high_resolution_clock::now() ;
	auto millis = duration_cast<milliseconds>(now.time_since_epoch()).count() ;

	int s = fmod(millis + to, 864e5) ;

	ui -> date -> setDate( QDate::currentDate() ) ;
	ui -> time -> setTime( QTime::fromMSecsSinceStartOfDay(s) ) ;

}

void MainWindow::on_run_clicked()
{
	timer -> start(55) ;
}

void MainWindow::on_stop_clicked()
{
	timer -> stop() ;
}
