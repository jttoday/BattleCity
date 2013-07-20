#ifndef MAPELEMENTH_GUARD
#define MAPELEMENTH_GUARD


class MapElement{
public:
	



	void add(const QPoint& p) {
		QRect rect(p.x(), p.y(), pic_width, pic_height);
		rects.push_back(rect);
	}

	void clear() {
		rects.clear();
	}

	rect_list& getRects() {
		return rects;
	}
	
private:
	QString name;
	rect_list rects;
};



#endif
