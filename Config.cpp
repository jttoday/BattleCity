#include "Consts.h"
#include "Config.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <algorithm>
#include <iterator>

using namespace std;



typedef map<string, string> cfg_map;

static const string file_url("BattleCity.cfg");

static
void copy_to_sstream(ifstream& ifile, 
		stringstream& is_file)
{
	copy(istreambuf_iterator<char>(ifile),
     istreambuf_iterator<char>(),
     ostreambuf_iterator<char>(is_file)); 
}

static 
void parse_file(stringstream& is_file,
		cfg_map& cfg)
{
	string line;
	while (getline(is_file, line))
	{
		istringstream is_line(line);
		string key;
		if( getline(is_line, key, '=') )
		{
			string value;
			if(getline(is_line, value)) 
				cfg[key] = value;	
		}
	}
}

static
int to_int(const string& s)
{
	istringstream is(s);
	int n;
	is >> n;
	return n;
}



void Config::readConfig()
{
	cfg_map cfg;
	ifstream ifile(file_url.c_str());
	stringstream is_file;
	copy_to_sstream(ifile, is_file);
	parse_file(is_file, cfg);
	map_width		=	to_int(cfg["map_width"]		);
	map_height		=	to_int(cfg["map_height"]	);
	tank_speed		=	to_int(cfg["tank_speed"]	);
	missile_speed	=	to_int(cfg["missile_speed"]	);
	pic_width     	=	to_int(cfg["pic_width"]		);
	pic_height    	=	to_int(cfg["pic_height"]	);
	tank_width    	=	to_int(cfg["tank_width"]	);
	tank_height   	=	to_int(cfg["tank_height"]	);
	missile_width 	=	to_int(cfg["missile_width"]	);
	missile_height	=	to_int(cfg["missile_height"]);
	max_enemy_step	=	to_int(cfg["max_enemy_step"]);
	max_enemy		=	to_int(cfg["max_enemy"]		);
	max_life		=	to_int(cfg["max_life"]		);	
}
