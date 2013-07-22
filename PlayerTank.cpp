#include "PlayerTank.h"

PlayerTank::PlayerTank(QPoint startPoint, TankWindow *tankWindow, 
			const TankType& type,int maxlife,
			Direction::Direction dir)
	:Tank(startPoint, tankWindow, type, dir),
	 life(maxlife)
{

}

void PlayerTank::kill()
{
	Tank::kill();
	
}

int PlayerTank::getLife()
{
	return life;
}

	
