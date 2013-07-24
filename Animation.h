#ifndef ANIMATIONH_GUARD
#define ANIMATIONH_GUARD
#include "TankConst.h"
#include "MapObject.h"
#include <QString>
#include <QPoint>
class QPainter;

class Animation :public MapObject
{
public:
	Animation(const QPoint& p, const QString& name, 
			int max, bool repeat = false);

	Animation(const MapObject& mp, const QString& name,
		int max, bool repeat = false);

	void draw(QPainter& painter);


private:
	QString name;
	int step;
	int max;
	bool repeat;
};

#endif
