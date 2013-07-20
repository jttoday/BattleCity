#include "Blast.h"
#include "TankConst.h"
#include <QRect>
#include <QPainter>
#include <QString>
#include <iostream>


Blast::Blast(const QRect& rect)
{
	this->rect = rect;
	step = 3;
}

void Blast::drawBlast(QPainter& painter)
{
	if (step /3 >8) 
		return;
	QImage blast;
	int n = step / 3;
	QString location = QString(":/image/small/blast%1.gif")
							.arg(n);
	blast.load(location);
	blast.scaled(pic_width, pic_height);
	painter.fillRect(rect, blast);
	++step;
}
