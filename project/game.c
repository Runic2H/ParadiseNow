//test


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

CP_Image genericenemy = NULL;
CP_Image boss = NULL;
CP_Image stationaryplants = NULL;
CP_Image background = NULL;

void menu_init(void);
void menu_update(void);
void menu_exit(void);



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
	DrawProjectile();
	
	timer(begin);
  enemy_draw(*objPositionX, *objPositionY, genericenemy, boss);
  
	//stationary plants, add @ different positions through different waves
	stationary_plants(*objPositionX, *objPositionY, 400.0f, 300.0f, stationaryplants);
	stationary_plants(*objPositionX, *objPositionY, 500.0f, 300.0f, stationaryplants);
	stationary_plants(*objPositionX, *objPositionY, 600.0f, 300.0f, stationaryplants);
	stationary_plants(*objPositionX, *objPositionY, 700.0f, 300.0f, stationaryplants);
	stationary_plants(*objPositionX, *objPositionY, 800.0f, 300.0f, stationaryplants);
	stationary_plants(*objPositionX, *objPositionY, 900.0f, 300.0f, stationaryplants);
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
	InitProjectiles();
	ShootCooldown = 0.0f;

		//images
	background = CP_Image_Load("./images/background.png");
	genericenemy = CP_Image_Load("./images/slime.png");
	stationaryplants = CP_Image_Load("./images/stationaryplants.png");
	boss = CP_Image_Load("./images/boss.png");

}


void game_update(void)
{
	//CP_Image_Draw(background, 0, 0, 1000, 1000, 255);
  //go back to main menu
	if (CP_Input_KeyTriggered(KEY_ESCAPE)) 
  {								
		CP_Engine_SetNextGameState(menu_init, menu_update, menu_exit);
	}

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
	Shoot(*objPositionX, *objPositionY, &ShootCooldown);
	ShootCooldown -= CP_System_GetDt();
	render();
	
}


void game_exit(void)
{
	CP_Graphics_ClearBackground(color_black);
	CP_Image_Free(&genericenemy);
	CP_Image_Free(&stationaryplants);
	CP_Image_Free(&background);
	CP_Image_Free(&boss);
}
