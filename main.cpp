#include "TankWindow.h"
#include "Config.h"
#include <QApplication>

int map_width;
int map_height;
int tank_speed;
int missile_speed;
int pic_width;
int pic_height;
int tank_width;
int tank_height;
int missile_width;
int missile_height;
int max_enemy_step; 
int max_enemy;
int max_life;




int main(int argc, char* argv[])
{
	Config::readConfig();
	QApplication app(argc, argv);
	TankWindow tankWindow;
	tankWindow.show();
	return app.exec();
}

