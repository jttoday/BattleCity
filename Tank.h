#ifndef TANKH_GUARD
#define TANKH_GUARD

#include "TankConst.h"
#include <QPoint>
class QPainter;
class QKeyEvent;
class QRect;
class TankWindow;
class QImage;
class Blast;


class Tank 
{
public:
	Tank(QPoint startPoint, TankWindow *tankWindow, 
			Direction::Direction dir= Direction::up);
	virtual ~Tank();
	/* move	 */
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	/* shoot missiles */
	void shoot();  
	/* is it alive? */
	bool isAlive();
	void kill();
	/* draw itself */
	virtual	void drawTank(QPainter &painter);

	/* get the rect where tank is */
	QRect getTankRect();

	/*  if Tank is not allowed to move */
	void undo();

	bool hitRect(const QRect& rect);

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
private:
	
	QPoint position;
	QPoint old_position;
	TankWindow *tankWindow;
	Blast* blast;


	bool hitBarrier();
	bool outOfMap();
	bool alive;
};

#endif
