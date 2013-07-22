#include "MapElement.h"


void MapElement::draw(QPainter& painter)
{
	QString url = QString(":image/small/%1.gif").arg(name);
	QImage image(url);
	for (rect_it it = rects.begin(); it!= rects.end();++it)
	{
		painter.fillRect(*it, image);
	}
}

bool MapElement::hit(const QRect& rect)
{
	for (rect_it it = rects.begin(); it!= rects.end(); ++it)
	{
		if (it -> intersects(rect))
			return true;
	}
	return false;
}

bool MapElement::hitAndErase(const QRect& rect)
{
	for (rect_it it = rects.begin(); it!= rects.end(); ++it)
	{
		if (it -> intersects(rect))
		{
			rects.erase(it);
			return true;
		}
	}
	return false;
}

