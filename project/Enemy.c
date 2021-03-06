#include "macros.h"


CP_Vector vectorEnemy;
CP_Vector vectorMove, Vectorplayer;
CP_Vector acceleration;

int enemyHP = 5;
int bossHP = 10;

// this should be parsed from char.h

int global_spawnRanflag;

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

	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		if(i < EnemyInitCount)
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
			Enemies[i].health = enemyHP;
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
			Enemies[i].health = enemyHP;
			Enemies[i].collisionWproj = 0;
			Enemies[i].diameter = 55.f;
			Enemies[i].kill = 0;


		}
			Enemies[i].enemy_posX = CP_Random_RangeFloat(-50.0f, ((float)s_windowWidth + 50.0f));
			Enemies[i].enemy_posY = outerlimit_rand(-50.0f, 50.0f, (float)s_windowHeight);
	}

	for (int j = 0; j < bosscount; ++j) {

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
		Boss[j].health = bossHP;
		Boss[j].collisionWproj = 0;
		Boss[j].diameter = 95.f;
		Boss[j].kill = 0;
	}
}


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
		}
	}

	for (int i = 0; i < bosscount; ++i)
	{
		float* bossX = &Boss[i].boss_posX;
		float* bossY = &Boss[i].boss_posY;
		//enemy_vector(player_x, player_y, bossX, bossY, Boss[i].speed);
		CP_Image_Draw(bossimage, *bossX, *bossY, 35, 35, 255);
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
	CP_Image_Draw(imageoverlay, position_x, position_y, 35, 35, 255);
}

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

void boss_Collision()
{
	for (int j = 0; j < MAX_PROJECTILE; j++)
	{
		if (Projectiles[j].isActive == 1) {
			for (int i = 0; i < bosscount; i++)
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


void boss_die()
{
	for (int i = 0; i < bosscount; i++)
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
		}
	}
}

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
			enemyHP++;
			bossHP += 5;
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
					Enemies[i].health = enemyHP;
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
