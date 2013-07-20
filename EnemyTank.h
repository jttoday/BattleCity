#ifndef ENEMYTANKH_GUARD
#define ENEMYTANKH_GUARD

#include "Tank.h"


class EnemyTank :public Tank 
{
public:
	EnemyTank(QPoint startPoint, TankWindow *tankWindow, 
			Direction::Direction dir= Direction::down);

	void randomMove();
	virtual void drawTank(QPainter &painter);

protected:
//	virtual void move(Direction::Direction dir);
private:
	int steps;

	/* enemy tank has different types */
	int types;

	/* different type has different speed */
	int speed;

	void changeDir();
};

#endif
