#ifndef TANKWINDOW_H
#define TANKWINDOW_H
#include <QMainWindow>
#include <list>
#include <vector>
#include "TankConst.h"
#include "Blast.h"


class Missile;
class Tank;
class QRect;
class EnemyTank;
class QPoint;

typedef std::list<EnemyTank*> enemy_list;
typedef enemy_list::iterator enemy_it;
typedef std::list<Missile*> missile_list;
typedef missile_list::iterator missile_it;
typedef std::list<Blast> blast_list;
typedef blast_list::iterator blast_it;
typedef std::vector<QPoint> point_vector;

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
	void loadMap();
	/* user lose game */
	void userLose();
	
	void addWall(QPoint p);
	void addSteel(QPoint p);
	void addEnemy();

	void drawMap(QPainter &painter);

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

	Map::map current_map;
	Tank *player;

	/* timers */
	int missileTimer;
	int enemyTimer;
	int produceTimer;
	/* Is player lose the game ? */
	bool lose;

	/* live enemy tanks */
	enemy_list enemies;
	/* all live missiles */
	missile_list missiles;
	/* list of walls and steels */
	std::list<QRect> walls;
	std::list<QRect> steels;
	/* vector of enemy start points */
	point_vector startPoints;

	/* where Symbol lies */
	QRect symbolRect;
};

#endif
