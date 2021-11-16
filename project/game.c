#include <stdio.h>
#include "cprocessing.h"
#include "character.h"

float *objPositionX, *objPositionY;
float mousePosX, mousePosY;
CP_Vector vectorMove, vectorMouse, *vectorObject, acceleration;
int layout;
struct c_CharacterStats mage;

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
	layout = 0;
	mage.positionX = 200.0F;
	mage.positionY = 200.0F;
	objPositionX = &mage.positionX;
	objPositionY = &mage.positionY;
}

void game_update(void)
{
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
}


void game_exit(void)
{

}
