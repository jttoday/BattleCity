#include "MapCollection.h"

MapCollection::~MapCollection()
{
	for (obj_it it = objs.begin(); it!= objs.end(); ++it)
	{
		delete *it;
	}
}

bool MapCollection::hit(const MapObject& rect) const
{
	for (const_obj_it it = objs.begin(); 
			it!= objs.end(); ++it)
	{
		if ((*it) -> intersects(rect))
			return true;
	}
	return false;
}

bool MapCollection::hitAndErase(const MapObject& rect)
{
	for (obj_it it = objs.begin(); it!= objs.end(); ++it)
	{
		if ((*it) -> intersects(rect))
		{
			delete *it;
			objs.erase(it);
			return true;
		}
	}
	return false;
}

bool MapCollection::hit(const MapCollection& mp) const
{
	for (const_obj_it it = objs.begin();
			it != objs.end(); ++it)
	{
		if (mp.hit(**it))
		{
			return true;
		}
	}
	return false;
}

bool MapCollection::hitAndRemove(MapCollection& mp) const
{
	bool hitted = false;
	for (const_obj_it it = objs.begin(); 
			it != objs.end(); ++it)
	{
		if (mp.hitAndErase(**it))
		{
			hitted = true;
		}
	}
	return hitted;
}

bool MapCollection::hitAndErase(const MapCollection& mp)
{
	obj_it it = objs.begin();
	bool hitted = false;
	while (it != objs.end())
	{
		if (mp.hit(**it))
		{
			delete *it;
			it = objs.erase(it);
			hitted = true;
		}
		else
		{
			++it;
		}
	}
	return hitted;
}

bool MapCollection::hitAndEraseAndRemove(MapCollection &mp)
{
	obj_it it = objs.begin();
	bool hitted = false;
	while (it != objs.end())
	{
		if (mp.hitAndErase(**it))
		{
			delete *it;
			it = objs.erase(it);
			hitted = true;
		}
		else
		{
			++it;
		}
	}
	return hitted;
}

bool MapCollection::checkInMap()
{
	bool hitted = false;
	obj_it it = objs.begin();
    while (it!= objs.end())
	{
		if ((*it) -> outOfMap())
		{
			delete *it;
			it = objs.erase(it);
			hitted = true;
		}
		else 
		{
			it ++;
		}
	}
	return hitted;
}

void MapCollection::clear()
{
	for (obj_it it = objs.begin(); it!= objs.end(); ++it)
	{
		delete *it;
	}
	objs.clear();
}
