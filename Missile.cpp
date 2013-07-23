#include "Missile.h"
#include "TankConst.h"
#include <QPainter>
#include <QDebug>

Missile::Missile(QPoint startPoint, Direction::Direction dir,
			Tank* tank)
    : MapObject(position,	missile_width, missile_height)
	
{
	this->position = startPoint;
	this->dir = dir;
	this->tank = tank;
}

Missile::~Missile()
{
	tank->downMissile();
}

void Missile::move()
{
	switch (dir)
	{
	case Direction::up:
		position.setY(position.y() - missile_speed);
		break;
	case Direction::down:
		position.setY(position.y() + missile_speed);
		break;
	case Direction::left:
		position.setX(position.x() - missile_speed);
		break;
	case Direction::right:
		position.setX(position.x() + missile_speed);
		break;
	default:
		break;
	}
	rect.moveTo(position);
}


void Missile::draw(QPainter &painter)
{
	QImage missile;
	missile.load(":/image/small/missile1.gif");
	painter.drawImage(position, missile);
}
