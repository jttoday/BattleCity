#include "Missiles.h"
#include "Missile.h"
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
