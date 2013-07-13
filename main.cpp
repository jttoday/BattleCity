#include "TankWindow.h"
#include <QApplication>

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	TankWindow tankWindow;
	tankWindow.show();
	return app.exec();
}

