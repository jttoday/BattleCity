#ifndef MAPCOLLECTIONH_GUARD
#define MAPCOLLECTIONH_GUARD
#include <QString>
#include <QPoint>
#include <list>
#include "TankConst.h"
#include "MapObject.h"

class Blasts;
typedef std::list<MapObject*> obj_list;
typedef obj_list::iterator obj_it;
typedef obj_list::const_iterator const_obj_it;

class MapCollection {
public:
	MapCollection() {}
	virtual ~MapCollection();
	virtual bool hitAndErase(const MapObject& obj);
	virtual bool hit(const MapObject& obj) const;
	virtual bool hit(const MapCollection& mp) const;
	virtual bool hitAndRemove(MapCollection &mp) const;
	virtual bool hitAndErase(const MapCollection &mp);
	virtual bool hitAndEraseAndRemove(MapCollection &mp);

	virtual bool hitAndEraseAndRemove(MapCollection &mp, 
			Blasts& blasts);

	virtual bool checkInMap();

	int size()	{ return objs.size(); }
	virtual void clear();
protected:
	obj_list objs;
};


#endif
