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

	void changeDir();
};

#endif
