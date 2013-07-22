#ifndef TANKTYPEH_GUARD
#define TANKTYPEH_GUARD

#include <QString>
struct TankType
{
	TankType(const QString& name, int speed, int missile)
	{
		this->speed = speed;
		this->name = name;
		this->missile = missile;
	}
	int speed;
	QString name;
	int missile;

};


#endif
