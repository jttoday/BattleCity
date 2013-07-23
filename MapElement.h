#ifndef MAPELEMENTH_GUARD
#define MAPELEMENTH_GUARD
#include <QPainter>
#include <QString>
#include "TankConst.h"
#include "MapCollection.h"


class MapElement :public MapCollection{
public:
	MapElement(const QString& name){
		this->name = name;
	}

	void add(const QPoint& p);

	void draw(QPainter& painter);

	
private:
	QString name;
};



#endif
