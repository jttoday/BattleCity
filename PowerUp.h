#ifndef POWERUPH_GUARD
#define POWERUPH_GUARD
#include "MapObject.h"
#include <QPoint>
#include <QString>
#include <QDebug>


class PowerUp :public MapObject {
public:
	enum { bomb = 1, strong, fast, stopper };
	
	PowerUp(const QPoint& point, int n)
		:MapObject(point, 20, 20)
	{
		powerUpId = n;
	}
			
	int powerUpId;

	void draw(QPainter& painter)
	{
		QImage pic;
		if (powerUpId == bomb)
			pic.load(":/image/small/bomb.gif");
		else if (powerUpId == strong)
			pic.load(":/image/small/strong.gif");
		else if (powerUpId == fast)
			pic.load(":/image/small/fast.gif");
		pic.scaled(rect.width(),rect.height());
		painter.drawImage(rect, pic);
	}
};


#endif
