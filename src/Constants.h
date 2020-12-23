#ifndef CONSTANTS_H
#define CONSTANTS_H
#include "Colors.h"

const unsigned int WINDOW_WIDTH = 800;// x
const unsigned int WINDOW_HEIGHT = 600; // y

const unsigned int TARGET_FPS = 60;
const unsigned int FRAME_TARGET_TIME = 1000 / TARGET_FPS; //Target miliseconds to next frame

enum LayerType {
	TILEMAP_LAYER = 0,
	VEGETATION_LAYER = 1,
	ENEMY_LAYER = 2,
	PLAYER_LAYER = 3,
	PROJECTILE_LAYER = 4,
	UI_LAYER = 5,
	NUM_LAYERS
};


#endif