#ifndef TANKH_GUARD
#define TANKH_GUARD

#include "TankConst.h"
#include "MapObject.h"
#include <QPoint>
#include <QString>
class QPainter;
class QKeyEvent;
class QRect;
class TankWindow;
class QImage;
class Blast;


class Tank :public MapObject
{
public:
	Tank(QPoint startPoint, TankWindow *tankWindow, 
			const TankType& type,Direction::Direction dir= Direction::up);
	virtual ~Tank();
	/* move	 */
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	/* shoot missiles */
	void shoot();  
	/* called when its missle died */
	void downMissile();
	/* is it alive? */
	bool isAlive();
	/* return true if killed */
	virtual bool kill();
	/* draw itself */
	virtual void drawTank(QPainter &painter);

	/*  if Tank is not allowed to move */
	void undo();
	/* set max_missile */
	void upgrade();

protected:
	/* move in certail direction
	 * return true if successfully moved
	 */
	virtual bool move(Direction::Direction dir);

	/* move in old direction */
	virtual bool move();

	/* helper method to draw Tank */
	void drawTankPict(QPainter &painter, QImage &tank);

	/* Is tank hit other tanks? */
	bool hitOtherTank();
	
	/* Tank direction */
	Direction::Direction dir;

	QPoint position;

	QString name;

	/* how many missiles can a tank have */
	int max_missile;
	/* missile  number */
	int missile_num;
private:
	QPoint old_position;
	TankWindow *tankWindow;


	int speed;
	bool hitBarrier();
	bool alive;
};

#endif
