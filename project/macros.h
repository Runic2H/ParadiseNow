/* Header file for macros */

#include <stdio.h>

#include "cprocessing.h"

#include <conio.h>

#include <time.h>

#include "Enemy.h"

#include "character.h"

#include "Interactives.h"

#define color_green CP_Color_Create(0,255,0,255)

#define color_black CP_Color_Create(0, 0, 0, 255)

#define color_red CP_Color_Create(255, 0, 0, 255)

#define color_blue CP_Color_Create(0,0,255,255)

enum controlScheme { WASD, MOUSE };