#ifndef TANKTYPEH_GUARD
#define TANKTYPEH_GUARD

#include <QString>
struct TankType
{
	TankType(const QString& name, int speed)
	{
		this->speed = speed;
		this->name = name;
	}
	int speed;
	QString name;

};


#endif
