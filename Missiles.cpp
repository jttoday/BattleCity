#include "Missiles.h"
#include "Missile.h"
#include "Tank.h"
#include <QPainter>

void Missiles::add(Missile* missile)
{
	objs.push_back(missile);
}

void Missiles::draw(QPainter &painter)
{
	for (obj_it it = objs.begin(); it != objs.end(); ++it)
	{
		Missile* missile = (Missile*) (*it);
		missile -> draw(painter);
	}
}

void Missiles::move()
{
	for (obj_it it = objs.begin(); it != objs.end(); ++it)
	{
		Missile* missile = (Missile*) (*it);
		missile -> move();
	}
}

bool Missiles::hitAndEraseTank(Tank& tank)
{
	for (obj_it it = objs.begin(); it!= objs.end(); ++it)
	{
		if ((*it) -> intersects(tank))
		{
			delete *it;
			objs.erase(it);

			return tank.kill();
		}
	}
	return false;
}
