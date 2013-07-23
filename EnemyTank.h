#ifndef ENEMYTANKH_GUARD
#define ENEMYTANKH_GUARD

#include "Tank.h"


class EnemyTank :public Tank 
{
public:
	EnemyTank(QPoint startPoint, TankWindow *tankWindow, 
			const TankType& name,Direction::Direction dir= Direction::down);

	void randomMove();

private:
	int steps;

	/* enemy tank has different types */
	int types;

	/* different type has different speed */
	int speed;

	void changeDir();
};

#endif
