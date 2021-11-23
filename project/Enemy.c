#include "macros.h"


CP_Vector vectorEnemy;
CP_Vector vectorMove, Vectorplayer;
CP_Vector acceleration;

// this should be parsed from char.h


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

void enemy_vector(float player_x, float player_y, float* ex, float* ey, float speed) {

	Vectorplayer = CP_Vector_Set(player_x, player_y);
	vectorEnemy = CP_Vector_Set(*ex, *ey);
	vectorMove = CP_Vector_Subtract(Vectorplayer, vectorEnemy);
	acceleration = CP_Vector_Scale(CP_Vector_Normalize(vectorMove), speed);

	*ex = vectorEnemy.x + acceleration.x;
	*ey = vectorEnemy.y + acceleration.y;

}

void enemy_init_posXY()
{

	for (int i = 0; i < enemycount; i++)
	{
		Enemies[i].ID = i + 1;

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
	}

	for (int j = 0; j < bosscount; ++j) {

		Boss[j].ID = j + 1;

		if (j % 2) {
			Boss[j].boss_posX = outerlimit_rand(-50.0f, 50.0f, (float)CP_System_GetWindowWidth());
			Boss[j].boss_posY = CP_Random_RangeFloat(-50.0f, ((float)CP_System_GetWindowHeight() + 50.0f));
		}
		else
		{
			Boss[j].boss_posX = CP_Random_RangeFloat(-50.0f, ((float)CP_System_GetWindowHeight() + 50.0f));
			Boss[j].boss_posY = outerlimit_rand(-50.0f, 50.0f, (float)CP_System_GetWindowWidth());
		}

		Boss[j].AliveDead = 1;
		Boss[j].speed = CP_Random_RangeFloat(2, 4);
		Boss[j].health = 1;
		Boss[j].collisionWproj = 0;

	}
}


void enemy_draw(float player_x, float player_y, CP_Image imageoverlay, CP_Image bossimage)
{
	CP_Settings_Fill(color_red);

	for (int i = 0; i < enemycount; i++)
	{
		if (Enemies[i].AliveDead == 1)
		{
			float* fpointerx = &Enemies[i].enemy_posX;
			float* fpointery = &Enemies[i].enemy_posY;
			//enemy_vector(player_x, player_y, fpointerx, fpointery, Enemies[i].speed);
			//CP_Graphics_DrawCircle(*fpointerx, *fpointery, 15);
			CP_Image_Draw(imageoverlay, *fpointerx, *fpointery, 55, 55, 255);
		}
	}

	for (int i = 0; i < bosscount; ++i)
	{
		float* bossX = &Boss[i].boss_posX;
		float* bossY = &Boss[i].boss_posY;
		//enemy_vector(player_x, player_y, bossX, bossY, Boss[i].speed);
		CP_Image_Draw(bossimage, *bossX, *bossY, 95, 95, 255);
	}

}


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
	CP_Image_Draw(imageoverlay, position_x, position_y, 55, 55, 255);
}

void enemy_collision()
{
	for (int i = 0; i < enemycount; i++)
	{
		if (is_ProjectileColliding(Enemies[i].enemy_posX, Enemies[i].enemy_posY, 55.f, Projectiles[0].Point.x, Projectiles[0].Point.y, 10.f))
		{
			printf("%d", Enemies[i].collisionWproj = 1);
			Projectiles[0].isActive = 0;
		}
		else
		{
			printf("%d", Enemies[i].collisionWproj = 0);
		}
	}
}

void boss_Collision()
{
	for (int i = 0; i < bosscount; i++)
	{
		if (is_ProjectileColliding(Boss[i].boss_posX, Boss[i].boss_posY, 55.f, Projectiles[0].Point.x, Projectiles[0].Point.y, 10.f))
		{
			printf("%d", Boss[i].collisionWproj = 1);
			Projectiles[0].isActive = 0;
		}
		else
		{
			printf("%d", Boss[i].collisionWproj = 0);
		}
	}
}

void boss_dmg()
{
	for (int i = 0; i < bosscount; i++)
	{
		if (Boss[i].collisionWproj == 1)
		{
			Boss[i].health -= 1;
		}
	}
}

void boss_die()
{
	for (int i = 0; i < bosscount; i++)
	{
		if (Boss[i].health == 0)
		{
			Boss[i].AliveDead = 0;
		}
	}
}

void enemy_TEST_TAKEDMG_update() {
	for (int i = 0; i < enemycount; i++)
	{
		if (Enemies[i].collisionWproj == 1)
		{
			Enemies[i].health -= 1;
		}
	}
}

void enemy_deadAlive_update(float player_x, float player_y)
{
	for (int i = 0; i < enemycount; i++)
	{
		if (Enemies[i].health == 0)
		{
			Enemies[i].AliveDead = 0;
		}

		if (Enemies[i].AliveDead == 1)
		{
			float* fpointerx = &Enemies[i].enemy_posX;
			float* fpointery = &Enemies[i].enemy_posY;
			enemy_vector(player_x, player_y, fpointerx, fpointery, Enemies[i].speed);
		}
	}


	for (int i = 0; i < bosscount; ++i)
	{
		float* bossX = &Boss[i].boss_posX;
		float* bossY = &Boss[i].boss_posY;
		enemy_vector(player_x, player_y, bossX, bossY, Boss[i].speed);
	}
}