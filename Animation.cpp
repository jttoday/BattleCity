#include "Animation.h"
#include <QPainter>

Animation::Animation(const QPoint& p, const QString& name, 
		int max, bool repeat)
	:MapObject(p, pic_width, pic_height)
{
	this->name = name;
	this->max = max;
	this-> repeat = repeat;
	this-> step = 0;
}

Animation::Animation(const MapObject& mp, const QString& name,
		int max, bool repeat)
	:MapObject(mp)
{
	this->name = name;
	this->max = max*4;
	this-> repeat = repeat;
	this-> step = 0;
}


void Animation::draw(QPainter& painter)
{

	if (step == max-1)
	{
		if (repeat == true)
			step = 0;
		else
			return;
	}
	step++;
	QString url = QString(":/image/small/%1%2.gif").arg(name)
					.arg(step/4+1);
	QImage img(url);
	img.scaled(rect.width(), rect.height());
	painter.drawImage(rect, img);
}
