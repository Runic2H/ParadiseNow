#include "macros.h"

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
	renderPlayer(objPositionX, objPositionY);
	enemy_draw(*objPositionX, *objPositionY);
	timer(begin);
}

void game_init(void)
{
	CP_System_SetWindowSize(1280, 720);
	enemy_init_posXY();
	begin = clock();
	layout = WASD;
	mage.positionX = 200.0F;
	mage.positionY = 200.0F;
	objPositionX = &mage.positionX;
	objPositionY = &mage.positionY;
}


void game_update(void)
{
	if (CP_Input_KeyTriggered(KEY_TAB))
	{
		layout == WASD ? (layout = MOUSE) : (layout = WASD);
	}
	if (layout == WASD)
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
