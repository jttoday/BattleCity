#ifndef TANKH_GUARD
#define TANKH_GUARD

#include "TankConst.h"
#include <QPoint>
class QPainter;
class QKeyEvent;
class QRect;
class TankWindow;
class Tank 
{
public:
	Tank(QPoint startPoint, TankWindow *tankWindow, 
			Direction::Direction dir= Direction::up);
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
	void drawTank(QPainter &painter);

	/* get the rect where tank is */
	QRect getTankRect();

	/*  if Tank is not allowed to move */
	void undo();

private:
	QPoint position;
	QPoint old_position;
	/* Tank direction */
	Direction::Direction dir;
	
	TankWindow *tankWindow;


	void move(Direction::Direction dir);
	bool hitBarrier();
	bool alive;
};

#endif
