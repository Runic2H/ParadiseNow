#include <stdio.h>
#include "cprocessing.h"
#include <conio.h>
#include <time.h>
#include "Enemy.h"
#include "character.h"

#define color_green CP_Color_Create(0,255,0,255)
#define color_black CP_Color_Create(0, 0, 0, 255)
#define color_red CP_Color_Create(255, 0, 0, 255)
#define color_blue CP_Color_Create(0,0,255,255)

CP_Vector vectorEnemy;
CP_Vector vectorMove, Vectorplayer;
CP_Vector acceleration;
float* objPositionX, * objPositionY;
float mousePosX, mousePosY;
int layout;
struct c_CharacterStats mage;
float x = 200.0f;
float y = 200.0f;
clock_t begin;
char runtime[256];

//Update Mouse Position
void mouse_update()
{
	mousePosX = CP_Input_GetMouseX();
	mousePosY = CP_Input_GetMouseY();
}

//Redraw
void render(void)
{
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Graphics_DrawCircle(*objPositionX, *objPositionY, 20);
}

void game_init(void)
{
	enemy_init_posXY();
	begin = clock();
	layout = 0;
	mage.positionX = 200.0F;
	mage.positionY = 200.0F;
	objPositionX = &mage.positionX;
	objPositionY = &mage.positionY;
}


void game_update(void)
{
	// CALUCULATE CLOCK
	/*clock_t end = clock();
	double time_spent = (double)(end-begin) / CLOCKS_PER_SEC;
	snprintf(runtime, 256, "%0.2f", time_spent);*/

	//DRAW CLOCK
	CP_Settings_Fill(color_red);
	CP_Font_DrawTextBox(runtime, 190.0f, 20.0f, 50.0f);

	if (CP_Input_KeyTriggered(KEY_TAB))
	{
		layout == 1 ? (layout = 0) : (layout = 1);
	}
	if (layout == 0)
	{
		c_CharacterWASD(objPositionX, objPositionY);
	}
	else
	{
		c_CharacterMouse(objPositionX, objPositionY);
	}

	render();
	enemy_draw(*objPositionX, *objPositionY);
}


void game_exit(void)
{

}
