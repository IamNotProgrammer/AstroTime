#include "mainwindow.h"
#include <QApplication>
#include <console.h>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;
	w.show();

    console() ;

	return a.exec();
}
