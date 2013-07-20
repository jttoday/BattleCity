#ifndef _TANKCONSTH_GUARD
#define _TANKCONSTH_GUARD
#include <list>
class QRect;
const int map_width = 13;
const int map_height = 13;
const int tank_speed = 15;
const int missile_speed = 5;
const int pic_width = 30;
const int pic_height = 30;
const int tank_width = 30;
const int tank_height = 30;
const int missile_width = 8;
const int missile_height = 8;
const int max_enemy_step = 9; 
const int max_enemy = 50;

typedef std::list<QRect> rect_list;
typedef rect_list::iterator rect_it;

namespace Direction {
	enum Direction{ up, left, down, right };
}

namespace Map{
	const int plain = 0;
	const int wall  = 1;
	const int steel = 2;
	const int grass = 3;
	const int startPoint = 8;
	const int symbol = 9;

typedef int map[map_width][map_height];

const map firstMap = {
	// 1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13
	{  8,  0,  0,  0,  0,  0,  8,  0,  0,  0,  0,  0,  8},	//1 
	{  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0},	//2
	{  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0},	//3
	{  0,  1,  0,  1,  0,  1,  2,  1,  0,  1,  0,  1,  0},	//4
	{  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0},	//5
	{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},	//6
	{  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  2},	//7
	{  1,  0,  1,  0,  0,  1,  1,  1,  0,  0,  1,  0,  1},	//8
	{  0,  0,  0,  0,  0,  1,  0,  1,  0,  0,  0,  0,  0},	//9
	{  0,  1,  0,  1,  0,  0,  0,  0,  0,  1,  0,  1,  0},	//10
	{  0,  1,  0,  1,  0,  1,  1,  1,  0,  1,  0,  1,  0},	//11
	{  0,  0,  0,  0,  0,  1,  0,  1,  0,  0,  0,  0,  0},	//12
	{  0,  0,  0,  0,  8,  1,  9,  1,  0,  0,  0,  0,  0},	//13
};

}

#endif
