#ifndef MAPOBJECTH_GUARD
#define MAPOBJECTH_GUARD
#include <QRect>
#include <QPoint>

class MapObject 
{
public:
	MapObject(const QPoint& p, int w, int h)
		:rect(p.x(),p.y(), w, h) {}

	virtual const QRect getRect() const {
		return rect;
	}
	

	bool intersects(const MapObject& obj) const{
		return getRect().intersects(obj.getRect());
	}
protected:
	QRect rect;

};

#endif
