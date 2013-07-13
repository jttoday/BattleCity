#include "Tank.h"
#include "TankWindow.h"
#include "Missile.h"
#include <QtGui>
#include <iostream>
using namespace std;

extern Map::map firstMap;

Tank::Tank(QPoint startPoint, TankWindow *tankWindow,
		Direction::Direction dir)
{
	position = startPoint;
	this -> dir= dir;
	this -> tankWindow = tankWindow;
	alive = true;
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

void Tank::move(Direction::Direction dir)
{
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
	if (hitBarrier())
		undo();
}

/*
 * shoot missiles
 */
void Tank::shoot()
{
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

bool Tank::hitBarrier()
{
	QRect tank_rect = getTankRect();
	if (tank_rect.left() < 0 
			|| tank_rect.right() > pic_width*map_width   
			|| tank_rect.top() < 0
			|| tank_rect.bottom() > pic_width*map_width)
		return true;
	int left	= tank_rect.left()	/ pic_width;
	int right	= tank_rect.right() / pic_width;
	int top		= tank_rect.top()	/ pic_height;
	int bottom	= tank_rect.bottom()/ pic_height;
	bool verticleMeet = (bottom * pic_height == tank_rect.bottom());
	bool horrizalMeet = (right * pic_width == tank_rect.right());
	int a11 = tankWindow->getMap(left, top);
	int a12 = tankWindow->getMap(right, top);
	int a21 = tankWindow->getMap(left, bottom);
	int a22 = tankWindow->getMap(right, bottom);
	if	((!verticleMeet && !horrizalMeet && 
				(	a11 !=0  || a12 !=0
				||	a21 !=0	||  a22 !=0))
		||(verticleMeet && !horrizalMeet &&
				(	a11 !=0 || a12 !=0))
		||(!verticleMeet && horrizalMeet &&
				(	a11 !=0 || a21 != 0))
		||(verticleMeet && horrizalMeet	&&
				(	a11 !=0 )))
	{
		
		/*
		cout << "----------" << endl;
		cout << verticleMeet << horrizalMeet << endl;
		cout << tank_rect.left() << ' ' << tank_rect.right() << ' ' 
			<< tank_rect.top() << ' ' << tank_rect.bottom() << endl;
		cout << left << ' ' << top << ',' << right << ' ' << top << endl;
		cout << left << ' ' << bottom << ',' << right << ' ' << bottom << endl;
		cout << a11 << a12 << endl;
		cout << a21 << a22 << endl;
		*/
		return true;
	}
	return false;

}

bool Tank::isAlive()
{
	return alive;
}

void Tank::kill()
{
	alive = false;
}


void Tank::drawTank(QPainter &painter)
{
	if (!alive)
		return;
	QImage tank;
	switch(dir)
	{
	case Direction::left:
		tank.load(":/image/small/p1tankL.gif");
		break;
	case Direction::right:
		tank.load(":/image/small/p1tankR.gif");
		break;
	case Direction::up:
		tank.load(":/image/small/p1tankU.gif");
		break;
	case Direction::down:
		tank.load(":/image/small/p1tankD.gif");
		break;
	default:
		return;
	}
	painter.drawImage(position, tank);
}
	
QRect Tank::getTankRect()
{
	return QRect(position.x(), position.y(), pic_width, pic_height);
}

void Tank::undo()
{
	position = old_position;
}




