#ifndef _TANKCONSTH_GUARD
#define _TANKCONSTH_GUARD
#include <list>
#include <QPoint>
#include <vector>
#include <QRect>
#include <QDebug>
#include <QSound>
#include "TankType.h"
#include "Consts.h"
#include "Config.h"

class QRect;
class EnemyTank;
class Missile;

typedef std::list<QRect> rect_list;
typedef rect_list::iterator rect_it;
typedef std::list<Missile*> missile_list;
typedef missile_list::iterator missile_it;
typedef std::vector<QPoint> point_vector;


namespace Direction {
	enum Direction{ up, left, down, right };
}

namespace Map{
	const int plain = 0;
	const int wall  = 1;
	const int steel = 2;
	const int grass = 3;
	const int water = 4;
	const int startPoint = 8;
	const int symbol = 9;

typedef int map[13][13];

const map firstMap = {
	// 1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13
	{  8,  0,  0,  1,  0,  0,  8,  0,  0,  0,  0,  0,  8},	//1 
	{  0,  3,  3,  1,  0,  1,  0,  0,  1,  3,  3,  0,  0},	//2
	{  2,  3,  3,  0,  0,  0,  3,  1,  0,  3,  0,  1,  3},	//3
	{  3,  3,  3,  2,  0,  0,  1,  1,  0,  1,  4,  1,  1},	//4
	{  3,  3,  3,  0,  0,  3,  3,  1,  0,  1,  0,  1,  1},	//5
	{  3,  4,  4,  1,  1,  0,  0,  0,  0,  4,  4,  0,  0},	//6
	{  1,  0,  0,  0,  4,  3,  2,  0,  0,  0,  0,  3,  2},	//7
	{  1,  3,  0,  3,  3,  1,  1,  1,  0,  1,  4,  0,  1},	//8
	{  0,  0,  3,  0,  0,  1,  0,  1,  0,  1,  3,  3,  0},	//9
	{  0,  1,  3,  1,  0,  0,  3,  3,  0,  1,  3,  1,  0},	//10
	{  3,  1,  3,  1,  0,  0,  0,  0,  0,  1,  4,  1,  0},	//11
	{  3,  0,  0,  0,  0,  1,  1,  1,  0,  0,  0,  0,  0},	//12
	{  0,  3,  0,  0,  8,  1,  9,  1,  8,  0,  0,  0,  0},	//13
};

}

#endif
