#include "Sculptor.h"
#include <QtWidgets/QApplication>
#include <qdesktopwidget.h>

int main(int argc, char *argv[])
{	
	QApplication a(argc, argv);
	QDesktopWidget* desktop = QApplication::desktop();
	Sculptor s;
	s.resize(desktop->width(),desktop->height());
	s.show();
	return a.exec();
}
