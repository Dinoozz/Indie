#pragma once

#include <irrlicht.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <ctime>

#include "event.h"

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#endif

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;
 
class Bomb;
class Node;

typedef struct
{
	IrrlichtDevice* device;
	IVideoDriver* driver;
	ISceneManager* smgr;
	IGUIEnvironment* guienv;
	char **map2D;
	std::vector <Bomb> bombs;
	std::vector <Node> bonus;
	int nb_player;
	bool is_loading;
} game_t;

typedef struct
{
	int speed;
	int power;
	int nb_bomb;
	bool wall_pass;
	bool is_alive;
} character_t;

typedef struct
{
	int nb_player;
	char **map2D;
	std::vector <character_t> List_Charact;
} data_t;

char** map_gen(int size);
