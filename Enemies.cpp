#include "Enemies.h"
#include "EnemyTank.h"
#include <QPainter>
#include <stdlib.h>

void Enemies::add(EnemyTank* tank)
{
	objs.push_back(tank);
}

void Enemies::randomMove()
{
	for (obj_it it= objs.begin(); it != objs.end(); ++it)
	{
		EnemyTank* enemy = (EnemyTank*) (*it);
		enemy->randomMove();
	}
}

void Enemies::randomShoot()
{
	for (obj_it it= objs.begin(); it != objs.end(); ++it)
	{
		EnemyTank* enemy = (EnemyTank*) (*it);
		if (rand() % 12 == 0)
			enemy->shoot();
	}
}

void Enemies::draw(QPainter& painter)
{
	for (obj_it it= objs.begin(); it != objs.end(); ++it)
	{
		EnemyTank* enemy = (EnemyTank*) (*it);
		enemy->drawTank(painter);
	}
}
