#include "GUIMusicEqualiser.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	GUIMusicEqualiser w;
	QObject::connect(&w.music_file, SIGNAL(ProgressChanged(size_t)), &w, SLOT(ShowProgress(size_t)));
	w.show();
	return a.exec();
}
