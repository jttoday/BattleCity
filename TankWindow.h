#ifndef TANKWINDOW_H
#define TANKWINDOW_H
#include <QMainWindow>
#include <list>
#include <vector>
#include <QPainter>
#include <QImage>
#include "TankConst.h"
#include "MapObject.h"
#include "MapElement.h"
#include "Missiles.h"
#include "Enemies.h"
#include "Blasts.h"
#include "PowerUp.h"


class Missile;
class Tank;
class QRect;
class EnemyTank;
class PlayerTank;
class QPoint;

class TankWindow :public QMainWindow
{
	Q_OBJECT

public:
	TankWindow();
	int getMap(int x, int y);
	void addMissile(Missile * missile);
	bool hitBarrier(const Tank& tank);
protected:
	void paintEvent(QPaintEvent *event);
	void keyPressEvent(QKeyEvent *event);
	void timerEvent(QTimerEvent *);

private slots:
	void onEatingPowerUp(int powerUpId, PlayerTank* player);
	void onPlayerWin();

signals:
	void eatingPowerUp(int , PlayerTank*);
	void playerWin();
private:

	void startGame(); 

	void loadMap();
	/* user lose game */
	void userLose();
	
	void addEnemy();
	/* draw start menu */
	void drawChoose(QPainter &painter);

	/* draw info board */
	void drawInfo(QPainter &painter);


	/* draw Symbol */
	void drawSymbol(QPainter& painter);


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
	/* kill a player */
	PlayerTank* killPlayer(PlayerTank* player, int n);
	

	bool isChoosing();

	Map::map current_map;
	PlayerTank *player1, *player2;

	/* timers */
	int missileTimer;
	int enemyTimer;
	int produceTimer;
	int strongTimer;
	int powerUpTimer;
	/* Is player lose or win the game ? */
	bool lose;
	bool win;
	/* Is in the select window? */
	bool choosing;
	/* 1p or 2p */
	int playerNumber;
	/* player's life */
	int p1life;
	int p2life;

	/* Map Elements */
	MapElement walls;
	MapElement steels;
	MapElement grasses;
	MapElement waters;

	/* live enemy tanks */
	Enemies enemies;
	int enemyNumber;
	/* all live missiles */
	Missiles missiles;
	/* blasts is what shows when tanks die */
	Blasts blasts;
	/* power up */
	PowerUp* powerUp;
	/* vector of enemy start points */
	point_vector startPoints;

	/* where Symbol lies */
	QRect symbolRect;

};

#endif
