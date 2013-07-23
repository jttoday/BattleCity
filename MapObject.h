#ifndef MAPOBJECTH_GUARD
#define MAPOBJECTH_GUARD
#include <QRect>
#include <QPoint>

class MapObject 
{
public:
	MapObject(const QPoint& p, int w, int h)
		:rect(p.x(),p.y(), w, h) {}


	MapObject(const QRect& rect) {
		this->rect = rect;
	}

	virtual ~MapObject() {}

	virtual const QRect getRect() const {
		return rect;
	}
	

	bool intersects(const MapObject& obj) const{
		return getRect().intersects(obj.getRect());
	}

	bool outOfMap() const {
		int left = rect.left();
		int top = rect.top();
		int right = rect.right();
		int bottom = rect.bottom();
		if (left < 0 || top < 0 || right > pic_width* map_width
				|| bottom > pic_height * map_height)
			return true;
		return false;
	}
protected:
	QRect rect;

};

#endif
