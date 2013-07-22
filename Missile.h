#ifndef MISSILEH_GUARD
#define MISSILEH_GUARD

#include "Tank.h"
#include "TankWindow.h"
#include <QPoint>
#include <QRect>

class Missile {
public:
	Missile(QPoint startPoint, Direction::Direction dir,
			TankWindow *tankWindow);
	/* notice: missile cannot change direction */
	void move();

	bool isAlive();
	void kill();

	bool hitRect(const QRect& rect);

	bool outOfMap();

	QRect& getRect();


	void drawMissile(QPainter &painter);
private:
	QPoint position;
	QRect missile_rect;
	Direction::Direction dir;

	TankWindow* tankWindow;

	bool alive;
};

#endif
