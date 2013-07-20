#include "Missile.h"
#include "TankConst.h"
#include <QPainter>

Missile::Missile(QPoint startPoint, Direction::Direction dir,
			TankWindow *tankWindow)
{
	position = startPoint;
	this->dir = dir;
	this->tankWindow = tankWindow;
	alive = true;
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
}

bool Missile::isAlive()
{
	return alive;
}

void Missile::kill()
{
	alive = false;
}

bool Missile::hitRect(const QRect& rect)
{
	QRect missile_rect(position.x(), position.y(),
					missile_width, missile_height);
	return missile_rect.intersects(rect);

}

bool Missile::outOfMap()
{
	int left = position.x();
	int top = position.y();
	int right = left+ missile_width;
	int bottom = top+ missile_height;
	if (left < 0 || top < 0 || right > pic_width* map_width
			|| bottom > pic_height * map_height)
		return true;
	return false;
}


void Missile::drawMissile(QPainter &painter)
{
	if (!alive)
		return;
	QImage missile;
	missile.load(":/image/small/missile1.gif");
	painter.drawImage(position, missile);
}
