//test
#include "macros.h"

CP_Vector vectorEnemy;
int layout;
float x = 200.0f;
float y = 200.0f;
clock_t begin;

CP_Image genericenemy = NULL;
CP_Image boss = NULL;
CP_Image stationaryplants = NULL;
CP_Image background = NULL;
CP_Image Mage = NULL;

//void menu_init(void);
//void menu_update(void);
//void menu_exit(void);

void you_died(void)
{
	if (player.health <= 0)
	{
		CP_Engine_Terminate();
	}
}

//Render stuff
void render(void)
{
	CP_Image_Draw(background, 640.0f, 365.0f, 1280.0f, 735.0f, 255);
	c_renderPlayer(Mage);
	c_renderHUD();
	DrawProjectile();
	timer(begin);
	enemy_draw(player.positionX, player.positionY, genericenemy, boss);
	render_Chest(chest.posX,chest.posY,chest.diameter);

	//stationary plants, add @ different positions through different waves
	stationary_plants(player.positionX, player.positionY, 400.0f, 300.0f, stationaryplants);
	stationary_plants(player.positionX, player.positionY, 500.0f, 300.0f, stationaryplants);
	stationary_plants(player.positionX, player.positionY, 600.0f, 300.0f, stationaryplants);
	stationary_plants(player.positionX, player.positionY, 700.0f, 300.0f, stationaryplants);
	stationary_plants(player.positionX, player.positionY, 800.0f, 300.0f, stationaryplants);
	stationary_plants(player.positionX, player.positionY, 900.0f, 300.0f, stationaryplants);

	//pause
	if (pause == TRUE) 
	{
		render_pause_menu();
	}
}

void checkUpdates(void)
{
	playerCollide(player.positionX, player.positionY);
	Shoot(player.positionX, player.positionY, &ShootCooldown);
	ShootCooldown -= CP_System_GetDt();
	chest_SpawnCheck();
	enemy_collision();
	boss_Collision();
	boss_die();
	enemy_deadAlive_update(player.positionX, player.positionY);
	you_died();
}


void game_init(void)
{
	CP_Settings_TextSize(20.0f);
	CP_System_SetWindowSize(1280, 720);
	enemy_init_posXY();
	chest_init();
	c_CharacterInit();
	InitProjectiles();
	begin = clock();
	layout = WASD;
	ShootCooldown = 0.0f;
	pause = 0;

	//images
	background = CP_Image_Load("./images/background2.png");
	genericenemy = CP_Image_Load("./images/slime.png");
	stationaryplants = CP_Image_Load("./images/stationaryplants.png");
	boss = CP_Image_Load("./images/boss.png");
	Mage = CP_Image_Load("./images/Mage.png");
	CP_System_ShowConsole();
}


void game_update(void)
{
	//timeStart += CP_System_GetDt();
	//if (timeStart >= duration) {
	//	timeStart = 0.f;
	//	SWAP(float, min_y, max_y);
	//}
	
	if (pause == FALSE) 
  {
		if (CP_Input_KeyTriggered(KEY_ESCAPE))
		{
			pause = TRUE;
		}
		if (CP_Input_KeyTriggered(KEY_TAB))
		{
			layout == WASD ? (layout = MOUSE) : (layout = WASD);
		}
		if (layout == WASD)
		{
			c_CharacterWASD();
		}
		else
		{
			c_CharacterMouse();
		}
	}
	else 
	{
		if (CP_Input_KeyTriggered(KEY_ESCAPE))
		{
			pause = TRUE;
		}
	}
	  checkUpdates();
	  render();
}


void game_exit(void)
{
	CP_Graphics_ClearBackground(color_black);
	CP_Image_Free(&genericenemy);
	CP_Image_Free(&stationaryplants);
	CP_Image_Free(&background);
	CP_Image_Free(&boss);
	CP_Image_Free(&Mage);
}
