#ifndef TANKWINDOW_H
#define TANKWINDOW_H
#include <QMainWindow>
#include <list>
#include <vector>
#include <QPainter>
#include <QImage>
#include "TankConst.h"
#include "Blast.h"


class Missile;
class Tank;
class QRect;
class EnemyTank;
class QPoint;

class TankWindow :public QMainWindow
{
	Q_OBJECT

public:
	TankWindow();
	int getMap(int x, int y);
	void addMissile(Missile * missile);
	rect_list& getWalls();
	rect_list& getSteels();
	enemy_list& getEnemies();
protected:
	void paintEvent(QPaintEvent *event);
	void keyPressEvent(QKeyEvent *event);
	void timerEvent(QTimerEvent *);
private:

	void startGame(); 
	/* choose game type ie:1p or 2p */
	int chooseType();

	void loadMap();
	/* user lose game */
	void userLose();
	
	void addWall(QPoint p);
	void addSteel(QPoint p);
	void addGrass(QPoint p);
	void addEnemy();
	/* draw start menu */
	void drawChoose(QPainter &painter);

	/* draw wall, steel, and grass */
	void drawWall(QPainter &painter);
	void drawSteel(QPainter &painter);
	void drawGrass(QPainter &painter);

	void drawSymbol(QPainter& painter);


	/* helper method to draw */
	void drawRects(QPainter &painter, const QImage& image, 
						 rect_list& rects);

	/* move enemies */
	void moveEnemy();

	/* move missiles */
	void moveMissile();
	
	/* delete all missiles */
	void clearMissile();
	/* delete all enemies */
	void clearEnemy();
	/* delte walls and steels */
	void clearMap();
	/* kill a tank */
	void killTank(Tank* tank);
	

	bool isChoosing();

	Map::map current_map;
	Tank *player1, *player2;

	/* timers */
	int missileTimer;
	int enemyTimer;
	int produceTimer;
	/* Is player lose the game ? */
	bool lose;
	/* Is in the select window? */
	bool choosing;
	/* 1p or 2p */
	int playerNumber;

	/* live enemy tanks */
	enemy_list enemies;
	/* all live missiles */
	missile_list missiles;
	/* list of walls and steels and grass */
	rect_list walls;
	rect_list steels;
	rect_list grasses;
	/* vector of enemy start points */
	point_vector startPoints;

	/* where Symbol lies */
	QRect symbolRect;
};

#endif
