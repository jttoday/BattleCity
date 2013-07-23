#ifndef ENEMIESH_GUARD
#define ENEMIESH_GUARD
#include "MapCollection.h"
class EnemyTank;
class QPainter;

class Enemies :public MapCollection
{
public:
	void add(EnemyTank* tank);
	void randomMove();
	void randomShoot();
	void draw(QPainter& painter);

};

#endif
