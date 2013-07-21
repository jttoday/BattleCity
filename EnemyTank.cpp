#include "EnemyTank.h"
#include "Tank.h"
#include "TankConst.h"
#include <stdlib.h>
#include <time.h>
#include <QtGui>
#include <iostream>


EnemyTank::EnemyTank(QPoint startPoint, TankWindow *tankWindow, 
			const TankType& name, Direction::Direction dir)
	/* Call base constructor first */
	:Tank(startPoint, tankWindow,name, dir),
	 steps(max_enemy_step)
{
	srand(time(NULL));
}

void EnemyTank::randomMove()
{
	if (steps == 0)
	{
		changeDir();
		steps = max_enemy_step;
	}
	while (!move())
	{
		changeDir();
	}
	--steps;
}

void EnemyTank::changeDir()
{
	int t = rand() %5;
	switch(t)
	{
	case 0:
		dir = Direction::up;
		break;
	case 1: case 4: 
		dir = Direction::down;
		break;
	case 2:
		dir = Direction::left;
		break;
	case 3:
		dir = Direction::right;
		break;
	default:
		break;
	}
}



