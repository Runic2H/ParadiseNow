#include "macros.h"


CP_Vector vectorEnemy;
CP_Vector vectorMove, Vectorplayer;
CP_Vector acceleration;

#define enemycount 20
#define enemyAlive 1
#define enemyDead 0

// this should be parsed from char.h

struct Enemy {
	int ID; // 1, 2, 3, 4, 5
	float enemy_posX;
	float enemy_posY;
	int AliveDead; // enemyAlive 1 or enemyDead 1 0 
	float speed;
};

struct Enemy Enemies[enemycount];

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
		Enemies[i].speed = CP_Random_RangeFloat(1, 3);
	}
}

void enemy_draw(float player_x, float player_y, CP_Image imageoverlay)
{
	CP_Settings_Fill(color_red);

	for (int i = 0; i < enemycount; i++)
	{
		float* fpointerx = &Enemies[i].enemy_posX;
		float* fpointery = &Enemies[i].enemy_posY;
		enemy_vector(player_x, player_y, fpointerx, fpointery, Enemies[i].speed);
		//CP_Graphics_DrawCircle(*fpointerx, *fpointery, 15);
		CP_Image_Draw(imageoverlay, *fpointerx, *fpointery, 55, 55, 255);
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