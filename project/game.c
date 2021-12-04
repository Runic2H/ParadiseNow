//test
#include "macros.h"

int layout;
clock_t begin;
CP_Image genericenemy = NULL;
CP_Image boss = NULL;
CP_Image stationaryplants = NULL;
CP_Image background = NULL;
CP_Image Mage = NULL;
CP_Image energyshield = NULL;
CP_Image projectileZ = NULL;
CP_Image chestZ = NULL;


CP_Sound gameplay_music = NULL;


void gameover_init(void);
void gameover_update(void);
void gameover_exit(void);

void you_died(void)
{
	if (player.health <= 0)
	{
		CP_Sound_StopAll();
		CP_Engine_SetNextGameState(gameover_init, gameover_update, gameover_exit);
	}
}

//void menu_init(void);
//void menu_update(void);
//void menu_exit(void);

//Render stuff
void render(void)
{
	CP_Image_Draw(background, 640.0f, 365.0f, 1280.0f, 735.0f, 255);
	c_renderPlayer(Mage, energyshield);
	c_renderHUD();
	DrawProjectile(projectileZ);
	timer(begin);
	enemy_draw(player.positionX, player.positionY, genericenemy, boss);
	render_Chest(chest.posX,chest.posY,chest.diameter, chestZ);
	render_skill(chest.skill);

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
	boss_die(player.positionX, player.positionY);
	enemy_deadAlive_update(player.positionX, player.positionY);
	enemy_respawn(15, 15);
	boss_respawn(5, 1);
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

	//Ease in
	timerStart = 0.f;
	duration = 1.f;
	min_y = 150.f;
	max_y = 100.f;

	//images
	background = CP_Image_Load("./images/background2.png");
	genericenemy = CP_Image_Load("./images/slime.png");
	stationaryplants = CP_Image_Load("./images/stationaryplants.png");
	boss = CP_Image_Load("./images/boss.png");
	Mage = CP_Image_Load("./images/mage.png");
	energyshield = CP_Image_Load("./images/magebubble.png");
	projectileZ = CP_Image_Load("./images/projectile.png");
	chestZ = CP_Image_Load("./images/chest.png");

	//sounds
	gameplay_music = CP_Sound_LoadMusic("./Sounds/gameplay.wav");
	CP_Sound_PlayMusic(gameplay_music);
}


void game_update(void)
{
	timerStart += CP_System_GetDt();
	if (timerStart >= duration) {
		timerStart = 0.f;
		SWAP(float, min_y, max_y);
	}
	
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
	  checkUpdates();
	}
	else 
	{
		if (CP_Input_KeyTriggered(KEY_ESCAPE))
		{
			pause = FALSE;
		}
	}
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
	CP_Image_Free(&energyshield);
	CP_Image_Free(&projectileZ);
	CP_Image_Free(&chestZ);
	
	CP_Sound_Free(&gameplay_music);

	
}
