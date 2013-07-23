#ifndef MISSILEH_GUARD
#define MISSILEH_GUARD

#include "Tank.h"
#include "TankWindow.h"
#include "MapObject.h"
#include <QPoint>
#include <QRect>

class Missile :public MapObject {
public:
	Missile(QPoint startPoint, Direction::Direction dir,
			Tank *tank);
	/* notice: missile cannot change direction */
	~Missile();
	void move();

	void draw(QPainter &painter);
private:
	QPoint position;
	Direction::Direction dir;

	TankWindow* tankWindow;
	Tank* tank;

};

#endif
