#include "mainwindow.h"
#include "console.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;
	w.show();

	console cons ;
	cons.start(QThread::LowPriority) ;


	return a.exec();
}
