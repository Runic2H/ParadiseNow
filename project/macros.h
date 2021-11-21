/* Header file for macros */

#include <stdio.h>

#include "cprocessing.h"

#include <conio.h>

#include <time.h>

#include "Enemy.h"

#include "character.h"

#include "interactives.h"

#include "projectiles.h"

#include <stdbool.h>

#include <math.h>

#include "collisions.h"

#define color_green CP_Color_Create(0,255,0,255)

#define color_black CP_Color_Create(0, 0, 0, 255)

#define color_red CP_Color_Create(255, 0, 0, 255)

#define color_blue CP_Color_Create(0,0,255,255)

#define color_white CP_Color_Create(255,255,255,255)

enum controlScheme { WASD, MOUSE };

enum skills 
{
	HEALTH = 1,
	ATTACK = 2
	//Add skills to list
};

/* Timer functions, timing is used as a global variable for 
use for any time related activities */

int timing;

void timer(clock_t begin);

void render_clock(double time_spent);

int getTimeSpent(int time);
