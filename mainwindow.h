#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTime>
#include <QSettings>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

private slots:
	void on_time_userTimeChanged(const QTime &time);

	void on_time_zone_h_textChanged(const QString &arg1);

	void on_time_zone_m_textChanged(const QString &arg1);

	void changed_time() ;

	void on_date_userDateChanged(const QDate &date);

	void on_longitude_textChanged(const QString &arg1);

	void on_set_time_clicked();

	void on_run_clicked();

	void on_stop_clicked();

	void on_pushButton_clicked();

	void LoadSettings() ;

	void on_latitude_textChanged(const QString &arg1);

	void on_altitude_textChanged(const QString &arg1);

private:
	Ui::MainWindow *ui;

	int year = 2020, month = 1, day = 1 ;
	int year_2, month_2, day_2 ;
	double hour, UT ;
	float tz, h ; // time zone
	double lo, la, al ; // longitude
	QTimer *timer ;
	int to ; // time offset from UTC in milis

};
#endif // MAINWINDOW_H
