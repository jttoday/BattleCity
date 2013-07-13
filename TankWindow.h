#ifndef TANKWINDOW_H
#define TANKWINDOW_H
#include <QMainWindow>
#include <list>
#include "TankConst.h"

class Missile;
class Tank;
class QRect;

class TankWindow :public QMainWindow
{
	Q_OBJECT

public:
	TankWindow();
	int getMap(int x, int y);
	void addMissile(Missile * missile);
	

protected:
	void paintEvent(QPaintEvent *event);
	void keyPressEvent(QKeyEvent *event);
	void timerEvent(QTimerEvent *);
private:

	void startGame(); 
	void loadMap();
	/* user lose game */
	void userLose();
	
	void addWall(QPoint p);
	void addSteel(QPoint p);

	void drawMap(QPainter &painter);
	/* is tank valid to move here? */

	Map::map current_map;
	Tank *player;
	
	/* all live missiles */
	std::list<Missile*> missiles;
	/* list of walls and steels */
	std::list<QRect> walls;
	std::list<QRect> steels;
	/* where Symbol lies */
	QRect symbolRect;
};

#endif
