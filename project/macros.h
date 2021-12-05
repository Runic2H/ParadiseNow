/* Header file for macros */
/*---------------------------------------------------------
 * file:	macros.h

 * author:	ELTON TEO ZHE WEI
			LOUIS MINEO @ LINN MIN HTOO
			RICHMOND CHOO TZE YONG
			ABDUL HADI

 * email:	e.teo@digipen.edu
			louismineo.l@digipen.edu
			r.choo@digipen.edu
			abdulhadi.b@digipen.edu

 * brief:	This file contains all preprocessor declarations
 *			required for the game to run. Any other #define
 *			functions required is also placed here as well
 *			as a global variable for time, several static
 *			functions for easein animations and all struct
 *			objects declared


 * Copyright © 2021 DigiPen, All rights reserved.
* ---------------------------------------------------------*/

/*-------------------------FUNCTION HEADER-----------------------*//*
	Preprocessor declarations
	#include...

*//*---------------------------------------------------------------*/
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

/*-------------------------FUNCTION HEADER-----------------------*//*
	All #define operations

*//*---------------------------------------------------------------*/
#define color_green CP_Color_Create(0,255,0,255)

#define color_black CP_Color_Create(0, 0, 0, 255)

#define color_red CP_Color_Create(255, 0, 0, 255)

#define color_blue CP_Color_Create(0,0,255,255)

#define color_white CP_Color_Create(255,255,255,255)

#define color_pause CP_Color_Create(0,0,0,100)

#define button_box CP_Color_Create(255,255,255,100)

#define color_buttons CP_Color_Create(200,63,0,255)

#define color_background CP_Color_Create(123,63,0,255)

#define color_yellow CP_Color_Create(215,215,0,255)

#define MAX_ENEMIES 100

#define EnemyInitCount 20

#define bosscount 2

#define MAX_BOSS 20

#define BossInitCount 2

#define enemyAlive 1

#define enemyDead 0

#define chestCount 2

#define chestSize 100.f

#define c_defaultSize 20.f

#define PI 3.14159265358979323846f  /* pi */

#define SWAP(type, lhs, rhs) { \
	type temp = lhs; \
	lhs = rhs; \
    rhs = temp; \
}

#define s_windowWidth CP_System_GetWindowWidth()

#define s_windowHeight CP_System_GetWindowHeight()

bool pause;
void menu_init(void);
void menu_update(void);
void menu_exit(void);

/*-------------------------FUNCTION HEADER-----------------------*//*
	enum lists for controlScheme and skills

*//*---------------------------------------------------------------*/
enum controlScheme { WASD, MOUSE };

enum skills 
{
	HEALTH,
	ATTACK,
	MULTISHOT,
	HEAL,
	SHIELD
	//Add skills to list
};


/*-------------------------FUNCTION HEADER-----------------------*//*
	Timer functions, timing is used as a global variable for 
	use for any time related activities   

*//*---------------------------------------------------------------*/
int global_timing;

void timer(clock_t begin);
void render_clock(double time_spent);
int getTimeSpent(int time);
void render_pause_menu(void);

/*-------------------------FUNCTION HEADER-----------------------*//*
	Struct Initialisation

*//*---------------------------------------------------------------*/
struct c_CharacterStats player;
struct Enemy Enemies[MAX_ENEMIES];
struct Boss Boss[MAX_BOSS];
struct upgrades chest;
struct Projectile Projectiles[MAX_PROJECTILE];

/*-------------------------FUNCTION HEADER-----------------------*//*
	Timer functions, timing is used as a global variable for
	use for any time related activities

*//*---------------------------------------------------------------*/
float timerStart;
float duration;
float min_y;
float max_y;
float min_size;
float max_size;

/*-------------------------FUNCTION HEADER-----------------------*//*
	Easein functions

*//*---------------------------------------------------------------*/
static float EaseInSine(float start, float end, float value)
{
	end -= start;
	return -end * cosf(value * (PI * 0.5f)) + end + start;
}

static float EaseInOutQuad(float start, float end, float value)
{
	value /= .5f;
	end -= start;
	if (value < 1) return end * 0.5f * value * value + start;
	value--;
	return -end * 0.5f * (value * (value - 2) - 1) + start;
}

static float Linear(float start, float end, float value)
{
	return (1.f - value) * start + value * end;
}
