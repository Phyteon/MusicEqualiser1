#include "GUIMusicEqualiser.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	GUIMusicEqualiser w;
	
	w.show();
	return a.exec();
}
