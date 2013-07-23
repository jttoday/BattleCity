#ifndef MAPELEMENTH_GUARD
#define MAPELEMENTH_GUARD
#include <QPainter>
#include <QString>
#include "TankConst.h"
#include "MapCollection.h"


class MapElement {
public:
	MapElement(const QString& name){
		this->name = name;
	}

	void add(const QPoint& p) {
		QRect rect(p.x(), p.y(), pic_width, pic_height);
		rects.push_back(rect);
	}

	void clear() {
		rects.clear();
	}

	bool hit(const QRect& rect);
	
	bool hitAndErase(const QRect& rect);

	void draw(QPainter& painter);

	
private:
	QString name;
	rect_list rects;
};



#endif
