#ifndef PLAYERTANKH_GUARD
#define PLAYERTANKH_GUARD
#include "Tank.h"

class PlayerTank :public Tank{
public:
	PlayerTank(QPoint startPoint, TankWindow *tankWindow, 
			const TankType& type,int maxlife = max_life, 
			Direction::Direction dir= Direction::up);
	void kill();
	int getLife();
private:
	int life;
};


#endif
