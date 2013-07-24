#ifndef BLASTSH_GUARD
#define BLASTSH_GUARD
#include <list>
#include "Animation.h"
class QPainter;
class MapObject;

typedef std::list<Animation> blast_list;
typedef blast_list::iterator blast_it;

class Blasts {
public:

	void draw(QPainter& painter);
	void add(const MapObject& mp);

private:
	blast_list blasts;
};

#endif
