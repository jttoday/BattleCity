#ifndef MISSILESH_GUARD
#define MISSILESH_GUARD

#include "MapCollection.h"
class QPainter;
class Missile;
class Tank;

class Missiles :public MapCollection {
public:
	void add(Missile *missile); 

	void draw(QPainter &painter);

	void move();

	bool hitAndEraseTank(Tank& tank);

};

#endif
