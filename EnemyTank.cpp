#include "EnemyTank.h"
#include "Tank.h"
#include "TankConst.h"
#include <stdlib.h>
#include <time.h>
#include <QtGui>
#include <iostream>


EnemyTank::EnemyTank(QPoint startPoint, TankWindow *tankWindow, 
			Direction::Direction dir)
	/* Call base constructor first */
	:Tank(startPoint, tankWindow,dir),
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

void EnemyTank::drawTank(QPainter &painter)
{
	QImage tank;
	switch(dir)
	{
	case Direction::left:
		tank.load(":/image/small/enemy1L.gif");
		break;
	case Direction::right:
		tank.load(":/image/small/enemy1R.gif");
		break;
	case Direction::up:
		tank.load(":/image/small/enemy1U.gif");
		break;
	case Direction::down:
		tank.load(":/image/small/enemy1D.gif");
		break;
	default:
		return;
	}
	drawTankPict(painter, tank);
}


