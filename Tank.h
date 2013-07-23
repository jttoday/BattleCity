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
	virtual void kill();
	/* draw itself */
	void drawTank(QPainter &painter);

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

	QString name;

	/* how many missiles can a tank have */
	int max_missile;
	/* missile  number */
	int missile_num;
private:
	QPoint position;
	QPoint old_position;
	TankWindow *tankWindow;
	Blast* blast;


	int speed;
	bool hitBarrier();
	bool outOfMap();
	bool alive;
};

#endif
