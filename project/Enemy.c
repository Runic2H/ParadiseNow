/*---------------------------------------------------------
 * file:	Enemy.c
 * author:	ELTON TEO ZHE WEI
			LOUIS MINEO @ LINN MIN HTOO
			RICHMOND CHOO TZE YONG
			ABDUL HADI

 * email:	e.teo@digipen.edu
			louismineo.l@digipen.edu
			r.choo@digipen.edu
			abdulhadi.b@digipen.edu
*
 * brief:	This file contains the enemy structure of
 *			our product. It contains all enemy-related functions,
 *			i.e. their AI logic or rendering.
 *


 * Copyright © 2021 DigiPen, All rights reserved.
* ---------------------------------------------------------*/

#include "macros.h"


CP_Vector vectorEnemy;
CP_Vector vectorMove, Vectorplayer;
CP_Vector acceleration;

// this should be parsed from char.h

int global_spawnRanflag;
int global_BOSS_spawnRanflag;

CP_Sound Slime_Death = NULL;
CP_Sound Boss_Death = NULL;


/*-------------------------FUNCTION HEADER-----------------------*//*
function:	outerlimit_rand()

author:		Louis Mineo

			outerlimit_rand() is used to produce an output of x and y
			coord. for the enemies's spawn location. Because we want
			the enemies spawn outside of the screen then slowly make
			their way to the player, we used will gather the input
			CP_System_GetWindowHeight, so that the window height and
			window width is not hardcoded, thus easier for dynamic scalling
			of the screen size.


Return : float value which is an X or Y outside the window
*//*---------------------------------------------------------------*/
float outerlimit_rand(float lower, float upper, float window_heightOrWidth)
{
	float p = CP_Random_RangeFloat(lower, upper); //rand number

	if (0 > p) {
		return p;
	}
	else
	{
		return (p + window_heightOrWidth);
	}
}

/*-------------------------FUNCTION HEADER-----------------------*//*
function:	enemy_vector()

author:		Louis Mineo

			enemy_vector(), this function will create the vector for
			movement of the enemy entity from its current XY,Y position,
			to the character's X,Y position.

Return : -
*//*---------------------------------------------------------------*/
void enemy_vector(float player_x, float player_y, float* ex, float* ey, float speed) {

	Vectorplayer = CP_Vector_Set(player_x, player_y);
	vectorEnemy = CP_Vector_Set(*ex, *ey);
	vectorMove = CP_Vector_Subtract(Vectorplayer, vectorEnemy);
	acceleration = CP_Vector_Scale(CP_Vector_Normalize(vectorMove), speed);

	*ex = vectorEnemy.x + acceleration.x;
	*ey = vectorEnemy.y + acceleration.y;

}
/*-------------------------FUNCTION HEADER-----------------------*//*
function:	enemy_init_posXY()

author:		Louis Mineo

			enemy_init_posXY(), this function will initialize the enemy
			and boss's XY positions, the aliveDead status, speed, health,
			and other variables within its struct.

			it will only initialize the specific amount of enemies and
			bosses as defined as EnemyInitCount and BossInitCount, and
			then and the other enemies and bosses are initialized with
			the "DEAD" status , and given a position outside the window
			with speed set as 0 so that they won't move.

Return: -
*//*---------------------------------------------------------------*/
void enemy_init_posXY()
{

	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		if (i < EnemyInitCount)
		{
			//Enemies[i].ID = i + 1;

			if (i % 2)
			{
				Enemies[i].enemy_posX = outerlimit_rand(-50.0f, 50.0f, (float)CP_System_GetWindowWidth());
				Enemies[i].enemy_posY = CP_Random_RangeFloat(-50.0f, ((float)CP_System_GetWindowHeight() + 50.0f));

			}
			else
			{
				Enemies[i].enemy_posX = CP_Random_RangeFloat(-50.0f, ((float)CP_System_GetWindowWidth() + 50.0f));
				Enemies[i].enemy_posY = outerlimit_rand(-50.0f, 50.0f, (float)CP_System_GetWindowHeight());
			}

			Enemies[i].AliveDead = 1; // ALL LIVE
			Enemies[i].speed = CP_Random_RangeFloat(2, 6);
			Enemies[i].health = 5;
			Enemies[i].collisionWproj = 0;
			Enemies[i].diameter = 55.f;
			Enemies[i].kill = 0;
			Enemies[i].enemy_posX = outerlimit_rand(-50.0f, 50.0f, (float)s_windowWidth);
			Enemies[i].enemy_posY = CP_Random_RangeFloat(-50.0f, ((float)s_windowHeight + 50.0f));

		}
		// no Else function as the rest of the elements are initialized w zero
		else
		{
			Enemies[i].enemy_posX = -50.f;
			Enemies[i].enemy_posY = -50.f;
			Enemies[i].AliveDead = 0;
			Enemies[i].speed = 0.f;
			Enemies[i].health = 5;
			Enemies[i].collisionWproj = 0;
			Enemies[i].diameter = 55.f;
			Enemies[i].kill = 0;


		}
		Enemies[i].enemy_posX = CP_Random_RangeFloat(-50.0f, ((float)s_windowWidth + 50.0f));
		Enemies[i].enemy_posY = outerlimit_rand(-50.0f, 50.0f, (float)s_windowHeight);
	}

	for (int j = 0; j < MAX_BOSS; ++j) {

		if (j < BossInitCount)
		{
			//Boss[j].ID = j + 1;

			if (j % 2) {
				Boss[j].boss_posX = outerlimit_rand(-50.0f, 50.0f, (float)s_windowWidth);
				Boss[j].boss_posY = CP_Random_RangeFloat(-50.0f, ((float)s_windowHeight + 50.0f));
			}
			else
			{
				Boss[j].boss_posX = CP_Random_RangeFloat(-50.0f, ((float)s_windowHeight + 50.0f));
				Boss[j].boss_posY = outerlimit_rand(-50.0f, 50.0f, (float)s_windowWidth);
			}

			Boss[j].AliveDead = 1;
			Boss[j].speed = CP_Random_RangeFloat(2, 4);
			Boss[j].health = 10;
			Boss[j].collisionWproj = 0;
			Boss[j].diameter = 95.f;
			Boss[j].kill = 0;
		}
		// no Else function as the rest of the elements are initialized w zero
		else
		{
			Boss[j].boss_posX = -50.f;
			Boss[j].boss_posY = -50.f;
			Boss[j].AliveDead = 0;
			Boss[j].speed = 0.f;
			Boss[j].health = 10;
			Boss[j].collisionWproj = 0;
			Boss[j].diameter = 55.f;
			Boss[j].kill = 0;
		}
	}

	//sound init
	Slime_Death = CP_Sound_LoadMusic("./Sounds/Slime Death.wav");
	Boss_Death = CP_Sound_LoadMusic("./Sounds/Boss Death.wav");

}

/*-------------------------FUNCTION HEADER-----------------------*//*
function:	enemy_draw()

author:		Louis Mineo

			enemy_draw() will draw both bosses and enemies for
			rendering onto the window screen.

Return : -
*//*---------------------------------------------------------------*/
void enemy_draw(float player_x, float player_y, CP_Image imageoverlay, CP_Image bossimage)
{
	CP_Settings_Fill(color_red);

	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		if (Enemies[i].AliveDead == 1)
		{
			float* fpointerx = &Enemies[i].enemy_posX;
			float* fpointery = &Enemies[i].enemy_posY;
			//enemy_vector(player_x, player_y, fpointerx, fpointery, Enemies[i].speed);
			//CP_Graphics_DrawCircle(*fpointerx, *fpointery, 15);
			CP_Image_Draw(imageoverlay, *fpointerx, *fpointery, 28, 28, 255);
			if (Enemies[i].health != 0)
			{
				CP_Settings_Fill(color_white);
				CP_Graphics_DrawRect(*fpointerx - 12, *fpointery - 25, 25, 10);
				CP_Settings_Fill(color_red);
				for (int health = Enemies[i].health; health >= 0; health--)
				{
					float length = (float)health * 5.f;
					CP_Graphics_DrawRect(*fpointerx - 12, *fpointery - 25, length, 10);
				}
			}
		}
	}

	for (int j = 0; j < MAX_BOSS; j++)
	{
		float* bossX = &Boss[j].boss_posX;
		float* bossY = &Boss[j].boss_posY;
		//enemy_vector(player_x, player_y, bossX, bossY, Boss[i].speed);
		CP_Image_Draw(bossimage, *bossX, *bossY, 35, 35, 255);
		if (Boss[j].health != 0)
		{
			CP_Settings_Fill(color_white);
			CP_Graphics_DrawRect(*bossX - 25, *bossY - 30, 50.f, 10.f);
			for (int health = Boss[j].health; health >= 0; health--)
			{
				float length = (float)health * 5.f;
				CP_Settings_Fill(color_red);
				CP_Graphics_DrawRect(*bossX - 25, *bossY - 30, length, 10.f);
			}
		}
	}

}

/*-------------------------FUNCTION HEADER-----------------------*//*
function:	stationary_plants()

author:		Richmond Choo

			stationary_plants is for creating the position of the
			stationary plants within the game screen and they will
			then be rendered.

			as of now, they serve no purpose, but will do so in
			future updates, if any.

Return : -
*//*---------------------------------------------------------------*/
void stationary_plants(float player_x, float player_y, float stationary_x, float stationary_y, CP_Image imageoverlay) {

	float position_x, position_y;

	CP_Vector stationaryenemy, move;


	Vectorplayer = CP_Vector_Set(player_x, player_y);
	stationaryenemy = CP_Vector_Set(stationary_x, stationary_y);
	move = CP_Vector_Subtract(Vectorplayer, stationaryenemy);
	acceleration = CP_Vector_Scale(CP_Vector_Normalize(move), 4.5);

	position_x = stationaryenemy.x + acceleration.x;
	position_y = stationaryenemy.y + acceleration.y;

	CP_Settings_Fill(color_blue);
	//CP_Graphics_DrawCircle(position_x, position_y, 15);
	CP_Image_Draw(imageoverlay, position_x, position_y, 35, 35, 255);
}
/*-------------------------FUNCTION HEADER-----------------------*//*
function:	enemy_collision()

author:		Abdul Hadi

			enemy_collision will loop thru the entire array of
			projectiles and then enemies,find the ones who are still
			"ALIVE", and check if they are colliding, with is_ProjectileColliding().
			when it returns true, enemy health is decreased and the
			projectile is no longer active.

Return : -
*//*---------------------------------------------------------------*/
void enemy_collision()
{
	for (int j = 0; j < MAX_PROJECTILE; j++)
	{
		if (Projectiles[j].isActive == 1) {
			for (int i = 0; i < MAX_ENEMIES; i++)
			{
				if (Enemies[i].AliveDead == 1) {
					if (is_ProjectileColliding(Enemies[i].enemy_posX, Enemies[i].enemy_posY, 25.f, Projectiles[j].Point.x, Projectiles[j].Point.y, 10.f))
					{
						Enemies[i].health -= player.attack;
						Projectiles[j].isActive = 0;
					}
					else
					{
						continue;
					}
				}
			}
		}
	}
}
/*-------------------------FUNCTION HEADER-----------------------*//*
function:	boss_Collision()

author:		Louis Mineo

			boss_collision will loop thru the entire array of projectiles
			and then bosses,find the ones who are still "ALIVE", and check
			if they are colliding, with is_ProjectileColliding(). when it
			returns true, enemy health is decreased and the projectile is
			no longer active.

Return : -
*//*---------------------------------------------------------------*/
void boss_Collision()
{
	for (int j = 0; j < MAX_PROJECTILE; j++)
	{
		if (Projectiles[j].isActive == 1) {
			for (int i = 0; i < MAX_BOSS; i++)
			{
				if (Boss[i].AliveDead == 1) {
					if (is_ProjectileColliding(Boss[i].boss_posX, Boss[i].boss_posY, 50.f, Projectiles[j].Point.x, Projectiles[j].Point.y, 10.f))
					{
						Boss[i].health -= player.attack;
						Projectiles[j].isActive = 0;

					}
					else
					{
						continue;
					}
				}
			}
		}
	}
}

/*-------------------------FUNCTION HEADER-----------------------*//*
function:	boss_deadAlive_update()

author:		Louis Mineo

			boss_deadAlive_update() will check the boss's health is
			less than 0, if it is, its variables are reset to 0 and
			set to "DEAD" status with 0 speed, and positioned outside
			the screen.

Return : -
*//*---------------------------------------------------------------*/
void boss_die(float player_x, float player_y)
{
	for (int i = 0; i < MAX_BOSS; i++)
	{
		if (Boss[i].health <= 0)
		{
			Boss[i].AliveDead = 0;
			Boss[i].boss_posX = -50.0f;
			Boss[i].boss_posY = -50.0f;
			Boss[i].speed = 0.0f;
			if (Boss[i].kill == 0)
			{
				Boss[i].kill = 1;
				player.gold += 10;
				player.score += 5;
			}
			else
			{
				continue;
			}
			// play boss death sound
			CP_Sound_Play(Boss_Death);


		}

		if (Boss[i].AliveDead == 1)
		{
			float* fpointerx = &Boss[i].boss_posX;
			float* fpointery = &Boss[i].boss_posY;
			enemy_vector(player_x, player_y, fpointerx, fpointery, Boss[i].speed);
		}
	}
}
/*-------------------------FUNCTION HEADER-----------------------*//*
function:	enemy_deadAlive_update

author:		Louis Mineo

			enemy_deadAlive_update() will check the enemy's health
			is less than 0, if it is, its variables are reset to 0.
			and set to "DEAD" status with 0 speed, and positioned
			outside the screen.

Return : -
*//*---------------------------------------------------------------*/
void enemy_deadAlive_update(float player_x, float player_y)
{
	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		if (Enemies[i].health <= 0)
		{
			Enemies[i].AliveDead = 0;
			Enemies[i].enemy_posX = -50.0f;
			Enemies[i].enemy_posY = -50.0f;
			Enemies[i].speed = 0.0f;
			if (Enemies[i].kill == 0)
			{
				Enemies[i].kill = 1;
				player.gold += 5;
				player.score += 1;
			}
			else
			{
				continue;
			}

			// play slime death sound
			CP_Sound_Play(Slime_Death);
		}

		if (Enemies[i].AliveDead == 1)
		{
			float* fpointerx = &Enemies[i].enemy_posX;
			float* fpointery = &Enemies[i].enemy_posY;
			enemy_vector(player_x, player_y, fpointerx, fpointery, Enemies[i].speed);
		}
	}

	/*
	for (int i = 0; i < bosscount; ++i)
	{
		float* bossX = &Boss[i].boss_posX;
		float* bossY = &Boss[i].boss_posY;
		enemy_vector(player_x, player_y, bossX, bossY, Boss[i].speed);
	}
	*/
}

/*-------------------------FUNCTION HEADER-----------------------*//*
function:	enemy_respawn

author:		Louis Mineo

			enemy_respawn will get an input of how many enemies to
			spawn every X seconds. then it will loop thru the enemies
			array and set the enemies to spawn outside the screen,
			with various variable amounts like speed.

			it also has a cooldown global_spawnRanflag, that the
			enemies only spawn once within that Xth second.

Return : -
*//*---------------------------------------------------------------*/
void enemy_respawn(int every_Xsecs, int no_of_enemiesToRespawn)
{
	if (global_timing % every_Xsecs != 0)
	{
		global_spawnRanflag = 0;
	}

	else if (global_timing != 0 && global_timing % every_Xsecs == 0) // if every_Xsecs == 15, means every 15 secs, this function will execute
	{
		if (global_spawnRanflag == 0)
		{
			printf("Spawn\n");
			// counting of enemies alive
			int spawned_count = 0;
			for (int i = 0; i < MAX_ENEMIES; i++)
			{
				if (Enemies[i].AliveDead == 0 && spawned_count < no_of_enemiesToRespawn)
				{
					if (i % 2)
					{
						Enemies[i].enemy_posX = outerlimit_rand(-50.0f, 50.0f, (float)CP_System_GetWindowWidth());
						Enemies[i].enemy_posY = CP_Random_RangeFloat(-50.0f, ((float)CP_System_GetWindowHeight() + 50.0f));

					}
					else
					{
						Enemies[i].enemy_posX = CP_Random_RangeFloat(-50.0f, ((float)CP_System_GetWindowWidth() + 50.0f));
						Enemies[i].enemy_posY = outerlimit_rand(-50.0f, 50.0f, (float)CP_System_GetWindowHeight());
					}
					Enemies[i].AliveDead = 1; // ALL LIVE
					Enemies[i].speed = CP_Random_RangeFloat(2, 6);
					Enemies[i].health = 5;
					printf("%d", Enemies[i].health);
					Enemies[i].collisionWproj = 0;
					Enemies[i].diameter = 55.f;
					Enemies[i].kill = 0;
					spawned_count++;
				}
			}
			global_spawnRanflag = 1;
		}
	}
}

/*-------------------------FUNCTION HEADER-----------------------*//*
function:	enemy_respawn

author:		Louis Mineo

			boss_respawn will get an input of how many bosses to
			spawn every X seconds. then it will loop thru the bosses
			array and set the bosses to spawn outside the screen, with
			various variable amounts like speed.

			it also has a cooldown global_BOSS_spawnRanflag, that the
			bosses only spawn once within that Xth second.

Return : -
*//*---------------------------------------------------------------*/
void boss_respawn(int every_Xsecs, int no_of_bossToRespawn)
{
	if (global_timing % every_Xsecs != 0)
	{
		global_BOSS_spawnRanflag = 0;
	}

	else if (global_timing != 0 && global_timing % every_Xsecs == 0) // if every_Xsecs == 15, means every 15 secs, this function will execute
	{
		if (global_BOSS_spawnRanflag == 0)
		{
			printf("Spawn\n");
			// counting of enemies alive
			int boss_spawned_count = 0;
			for (int i = 0; i < MAX_BOSS; i++)
			{
				if (Boss[i].AliveDead == 0 && boss_spawned_count < no_of_bossToRespawn)
				{
					if (i % 2)
					{
						Boss[i].boss_posX = outerlimit_rand(-50.0f, 50.0f, (float)CP_System_GetWindowWidth());
						Boss[i].boss_posY = CP_Random_RangeFloat(-50.0f, ((float)CP_System_GetWindowHeight() + 50.0f));

					}
					else
					{
						Boss[i].boss_posX = CP_Random_RangeFloat(-50.0f, ((float)CP_System_GetWindowWidth() + 50.0f));
						Boss[i].boss_posY = outerlimit_rand(-50.0f, 50.0f, (float)CP_System_GetWindowHeight());
					}
					Boss[i].AliveDead = 1; // ALL LIVE
					Boss[i].speed = CP_Random_RangeFloat(2, 6);
					Boss[i].health = 10;
					printf("%d", Boss[i].health);
					Boss[i].collisionWproj = 0;
					Boss[i].diameter = 55.f;
					Boss[i].kill = 0;
					boss_spawned_count++;
				}
			}
			global_BOSS_spawnRanflag = 1;
		}
	}
}
