#include "Tank.h"
#include "EnemyTank.h"
#include "TankWindow.h"
#include "Missile.h"
#include <QtGui>
#include <iostream>
#define NO_HIT_OTHER

using namespace std;

extern Map::map firstMap;

Tank::Tank(QPoint startPoint, TankWindow *tankWindow, 
		const TankType& type, Direction::Direction dir)
	:MapObject(startPoint, pic_width, pic_height)
{
	this->name = type.name;
	this->speed = type.speed;
	this->max_missile = type.missile;
	position = startPoint;
	this -> dir= dir;
	this -> tankWindow = tankWindow;
	alive = true;
	missile_num = 0;
}

Tank::~Tank()
{
}

void Tank::moveUp()
{
	move(Direction::up);
}

void Tank::moveDown()
{
	move(Direction::down);
}

void Tank::moveLeft()
{
	move(Direction::left);
}

void Tank::moveRight()
{
	move(Direction::right);
}

bool Tank::move(Direction::Direction dir)
{
	if (!alive)
		return true;
	old_position = position;
	switch (dir)
	{
	case Direction::up:
		position.setY(position.y() - speed);
		break;
	case Direction::down:
		position.setY(position.y() + speed);
		break;
	case Direction::left:
		position.setX(position.x() - speed);
		break;
	case Direction::right:
		position.setX(position.x() + speed);
		break;
	default:
		break;
	}
	this->dir = dir;
	rect.moveTo(position);


	/* if cannot move to there */
	if (outOfMap() || hitBarrier() || hitOtherTank())
	{
		undo();
		return false;
	}
	return true;
}


bool Tank::move()
{
	return move(dir);
}


/*
 * shoot missiles
 */
void Tank::shoot()
{
	if (!alive || missile_num >= max_missile)
		return;
	missile_num++;
	QPoint missilePoint;
	int x = position.x();
	int y = position.y();
	int offset = (tank_width - missile_width) / 2;
	switch (dir)
	{
	case Direction::up:
		missilePoint.setX(x+offset);
		missilePoint.setY(y-missile_height);
		break;
	case Direction::down:
		missilePoint.setX(x+offset);
		missilePoint.setY(y+tank_height);
		break;
	case Direction::right:
		missilePoint.setX(x+tank_width);
		missilePoint.setY(y+offset);
		break;
	case Direction::left:
		missilePoint.setX(x-missile_width);
		missilePoint.setY(y+offset);
		break;
	default:
		break;
	}
	Missile *missile = new Missile(missilePoint, 
			dir, this);
	tankWindow->addMissile(missile);
}

void Tank::downMissile()
{
	missile_num -- ;
}

bool Tank::hitBarrier()
{
	return tankWindow->hitBarrier(*this);
}

bool Tank::hitOtherTank()
{
#ifdef NO_HIT_OTHER
	return false;
#endif
}

bool Tank::isAlive()
{
	return alive;
}

bool Tank::kill()
{
	alive = false;
	return true;
}


void Tank::drawTank(QPainter &painter)
{
	QImage tank;
	switch(dir)
	{
	case Direction::left:
		tank.load(QString(":/image/small/%1L.gif").arg(name));
		break;
	case Direction::right:
		tank.load(QString(":/image/small/%1R.gif").arg(name));
		break;
	case Direction::up:
		tank.load(QString(":/image/small/%1U.gif").arg(name));
		break;
	case Direction::down:
		tank.load(QString(":/image/small/%1D.gif").arg(name));
		break;
	default:
		return;
	}
	drawTankPict(painter, tank);
}

void Tank::drawTankPict(QPainter &painter, QImage& tank)
{
	painter.drawImage(position, tank);
}
	
void Tank::undo()
{
	position = old_position;
	rect.moveTo(old_position);
}

void Tank::upgrade()
{
	max_missile *= 1.5;
}




