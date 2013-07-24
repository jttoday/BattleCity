#include "PlayerTank.h"
#include <QDebug>

PlayerTank::PlayerTank(QPoint startPoint, TankWindow *tankWindow, 
			const TankType& type,Direction::Direction dir)
	:Tank(startPoint, tankWindow, type, dir),
	strong(true),
	armor(rect, "protect", 6, true)
{

}

bool PlayerTank::kill()
{
	if (strong) 
	{
		return false;
	}
	return Tank::kill();
}

bool PlayerTank::isStrong()
{
	return strong;
}

void PlayerTank::setStrong(bool strong)
{
	this->strong = strong;
}

void PlayerTank::drawTank(QPainter& painter)
{
	Tank::drawTank(painter);
	if (isStrong())
	{
		armor.moveTo(position);
		armor.draw(painter);
	}
}



	
