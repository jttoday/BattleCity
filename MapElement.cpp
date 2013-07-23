#include "MapElement.h"

void MapElement::add(const QPoint& p)
{
	objs.push_back(new MapObject(p, 
				pic_width, pic_height));
}

void MapElement::draw(QPainter& painter)
{
	QString url = QString(":image/small/%1.gif").arg(name);
	QImage image(url);
	for (obj_it it = objs.begin(); it!= objs.end();++it)
	{
		painter.fillRect((*it)->getRect(), image);
	}
}

