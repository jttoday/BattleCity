#ifndef MAPMOVABLEH_GUARD
#define MAPMOVABLEH_GUARD

class MapMovable {
public:
	MapMovable(TankWindow* tankWindow){
		this->tankWindow = tankWindow;
	}

protected:
	virtual bool hit(const MapElement& elements);
};

#endif

