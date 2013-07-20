#ifndef BLASTH_GUARD
#define BLASTH_GUARD
#include <QRect>
#include <QPainter>

class Blast{
public:
	Blast(const QRect& rect);
	void drawBlast(QPainter& painter);
private:
	int step;
	QRect rect;
};

#endif
