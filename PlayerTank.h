#ifndef PLAYERTANKH_GUARD
#define PLAYERTANKH_GUARD
#include "Tank.h"
#include "Animation.h"

class PlayerTank :public Tank{
public:
	PlayerTank(QPoint startPoint, TankWindow *tankWindow, 
			const TankType& type,
			Direction::Direction dir= Direction::up);
	bool kill();

	bool isStrong();
	void setStrong(bool strong);

	void drawTank(QPainter &painter);
private:
	bool strong; 
	Animation armor;
};


#endif
