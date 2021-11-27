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

#define color_pause CP_Color_Create(0,0,0,100)

#define button_box CP_Color_Create(255,255,255,100)

#define color_buttons CP_Color_Create(200,63,0,255)

#define color_background CP_Color_Create(123,63,0,255)

bool pause;
void menu_init(void);
void menu_update(void);
void menu_exit(void);

#define enemycount 20

#define bosscount 2

#define enemyAlive 1

#define enemyDead 0

#define chestCount 2

#define chestSize 30.f

enum controlScheme { WASD, MOUSE };

enum skills 
{
	HEALTH,
	ATTACK,
	MULTISHOT
	//Add skills to list
};

/* Timer functions, timing is used as a global variable for 
use for any time related activities */    

int timing;
void timer(clock_t begin);
void render_clock(double time_spent);
int getTimeSpent(int time);
void render_pause_menu(void);

//Struct init

struct c_CharacterStats player;
struct Enemy Enemies[enemycount];
struct Boss Boss[bosscount];
struct upgrades chest;
struct Projectile Projectiles[MAX_PROJECTILE];
