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
{
	this->name = type.name;
	position = startPoint;
	this -> dir= dir;
	this -> tankWindow = tankWindow;
	alive = true;
}

Tank::~Tank()
{
	if (!alive)
		delete blast;
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
		position.setY(position.y() - tank_speed);
		break;
	case Direction::down:
		position.setY(position.y() + tank_speed);
		break;
	case Direction::left:
		position.setX(position.x() - tank_speed);
		break;
	case Direction::right:
		position.setX(position.x() + tank_speed);
		break;
	default:
		break;
	}
	this->dir = dir;

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
	if (!alive)
		return;
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
			dir, tankWindow);
	tankWindow->addMissile(missile);
}

bool Tank::hitRect(const QRect& rect)
{

	return getTankRect().intersects(rect);
}

bool Tank::hitBarrier()
{
	rect_list walls = tankWindow->getWalls();

	for (rect_it it = walls.begin();it != walls.end();++it)
	{
		if (this->hitRect(*it))
			return true;
	}
	rect_list steels = tankWindow->getSteels();
	for (rect_it it = steels.begin();it != steels.end();++it)
	{
		if (this->hitRect(*it))
			return true;
	}
	return false;

}

bool Tank::hitOtherTank()
{
#ifdef NO_HIT_OTHER
	return false;
#endif
	enemy_list enemies = tankWindow->getEnemies();
	for (enemy_it it = enemies.begin();it != enemies.end();++it)
	{
		if (*it != this && (*it)-> isAlive()
				&& (*it)->hitRect(getTankRect()))
			return true;
	}
	return false;
}

bool Tank::outOfMap()
{
	return getTankRect().left()<0 ||
		getTankRect().right() > pic_width* map_width ||
		getTankRect().top() <0 ||
		getTankRect().bottom() > pic_height * map_height;
}

bool Tank::isAlive()
{
	return alive;
}

void Tank::kill()
{
	alive = false;
	blast = new Blast(getTankRect());
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
	if (!alive)
	{
		blast->drawBlast(painter);
	}
	else
	{
		painter.drawImage(position, tank);
	}
}
	
QRect Tank::getTankRect()
{
	return QRect(position.x(), position.y(), pic_width-1, pic_height-1);
}

void Tank::undo()
{
	position = old_position;
}




