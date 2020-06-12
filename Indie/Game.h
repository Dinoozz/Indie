#include <irrlicht.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <math.h>

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
 
typedef struct
{
	IrrlichtDevice* device;
	IVideoDriver* driver;
	ISceneManager* smgr;
	IGUIEnvironment* guienv;
	char **map2D;
} game_t;

char** map_gen(int size);
