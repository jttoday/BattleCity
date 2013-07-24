#include "Blasts.h"
#include <QPainter>
#include "Animation.h"
#include "MapObject.h"

void Blasts::draw(QPainter& painter)
{
	for (blast_it  it = blasts.begin(); it != blasts.end(); ++it)
	{
		it->draw(painter);
	}
}

void Blasts::add(const MapObject& mp)
{
	blasts.push_back(Animation(mp, "blast", 8));
}
