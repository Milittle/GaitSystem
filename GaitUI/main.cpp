#include "GaitUI.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	GaitUI w;
	w.show();
	return a.exec();
}
