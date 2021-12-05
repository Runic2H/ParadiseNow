/*---------------------------------------------------------
 * file:	game.c
 * 
 * author:	ELTON TEO ZHE WEI
			LOUIS MINEO @ LINN MIN HTOO
			RICHMOND CHOO TZE YONG
			ABDUL HADI

 * email:	e.teo@digipen.edu
 			louismineo.l@digipen.edu
			r.choo@digipen.edu
			abdulhadi.b@digipen.edu
*
 * brief:	This file contains the main gameplay structure of
 *			our product. It contains all initialised values
 *			needed to start the game, the game_update loop
 *			and rendering is all done here


 * Copyright © 2021 DigiPen, All rights reserved.
* ---------------------------------------------------------*/


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
CP_Image warning = NULL;


CP_Sound gameplay_music = NULL;


void gameover_init(void);
void gameover_update(void);
void gameover_exit(void);

/*-------------------------FUNCTION HEADER-----------------------*//*
function: 	you_died()

author:		Richmond Choo

brief:		This function checks when player health is less than or 
			equal to 0 and if true will transition to the game_over 
			game state signalling that the player has lost and game 
			has ended

return:		-
*//*---------------------------------------------------------------*/
void you_died(void)
{
	if (player.health <= 0)
	{
		CP_Sound_StopAll();
		CP_Engine_SetNextGameState(gameover_init, gameover_update, gameover_exit);
	}
}

/*-------------------------FUNCTION HEADER-----------------------*//*
function:	render()

author:		Everyone

brief:		This function contains all functions pertaining to 
			rendering of various graphic elements. Such functions 
			include the rendering of player, the projectiles, 
			the enemies, the HUD, the timer, and the chest and easein 
			for the skills. Static rendering of various mobs such as 
			stationary mobs are also included here and the pause menu

return:		-
*//*---------------------------------------------------------------*/
void render(void) //Render stuff
{
	CP_Image_Draw(background, 640.0f, 365.0f, 1280.0f, 735.0f, 255);
	c_renderPlayer(Mage, energyshield);
	c_renderHUD(warning);
	DrawProjectile(projectileZ);
	timer(begin);
	enemy_draw(player.positionX, player.positionY, genericenemy, boss);
	render_Chest(chest.posX,chest.posY,chest.diameter, chestZ);
	render_skill(chest.skill);

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


/*-------------------------FUNCTION HEADER-----------------------*//*
function:	checkUpdates()

author:		Everyone

brief:		This function contains all functions pertaining to
			updating data. Functions included that checks for data
			updates are player collision, enemy collision, respawn
			for bosses and enemies, whether the player is alive and
			the cooldown and projectile function

return:		-
*//*---------------------------------------------------------------*/
void checkUpdates(void)
{
	playerCollide(player.positionX, player.positionY);
	Shoot(player.positionX, player.positionY, &ShootCooldown);
	ShootCooldown -= CP_System_GetDt();
	chest_SpawnCheck();
	enemy_collision();
	boss_Collision();
	boss_deadAlive_update(player.positionX, player.positionY);
	enemy_deadAlive_update(player.positionX, player.positionY);
	enemy_respawn(15, 15);
	boss_respawn(5, 1);
	you_died();
}

/*-------------------------FUNCTION HEADER-----------------------*//*
function:	game_init()

author:		Everyone

brief:		This function initialises all values and functions at
			runtime and is only called once on game start. It
			initialises data for the timer, the character stats,
			the spawning of enemies, setting the window size and
			the default control scheme and game state. It also loads
			the various game sounds and images and the starting values
			for easein functions

return:		-
*//*---------------------------------------------------------------*/
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
	min_size = 20.f;
	max_size = 30.f;

	//images
	background = CP_Image_Load("./images/background2.png");
	genericenemy = CP_Image_Load("./images/slime.png");
	stationaryplants = CP_Image_Load("./images/stationaryplants.png");
	boss = CP_Image_Load("./images/boss.png");
	Mage = CP_Image_Load("./images/mage.png");
	energyshield = CP_Image_Load("./images/magebubble.png");
	projectileZ = CP_Image_Load("./images/projectile.png");
	chestZ = CP_Image_Load("./images/chest.png");
	warning = CP_Image_Load("./images/warning.png");

	//sounds
	gameplay_music = CP_Sound_LoadMusic("./Sounds/gameplay.wav");
	CP_Sound_PlayMusic(gameplay_music);
}

/*-------------------------FUNCTION HEADER-----------------------*//*
function:	game_update()

author:		Elton and Richmond

brief:		This is the main update loop of the game, where functions
			called here are done at every frame. The if statements
			check for game state and control scheme and has a if
			statement for easein functions. the check_updates and
			render functions are called here to update and draw
			at every frame

return:		-
*//*---------------------------------------------------------------*/
void game_update(void)
{
	timerStart += CP_System_GetDt();
	if (timerStart >= duration) {
		timerStart = 0.f;
		SWAP(float, min_y, max_y);
		SWAP(float, min_size, max_size);
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

/*-------------------------FUNCTION HEADER-----------------------*//*
function:	game_exit()

author:		Richmond

brief:		This frees up memory for assets used and exits the game

return:		-
*//*---------------------------------------------------------------*/
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
	CP_Image_Free(&warning);
	CP_Sound_Free(&gameplay_music);	
}
