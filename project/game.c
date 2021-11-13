#include <stdio.h>
#include "cprocessing.h"
#include <conio.h>
#include <time.h>
#include "Enemy.h"

#define color_green CP_Color_Create(0,255,0,255)
#define color_black CP_Color_Create(0, 0, 0, 255)
#define color_red CP_Color_Create(255, 0, 0, 255)
#define color_blue CP_Color_Create(0,0,255,255)

CP_Vector vectorEnemy;
CP_Vector vectorMove, Vectorplayer;
CP_Vector acceleration;
float x = 200.0f;
float y = 200.0f;

float position_x, position_y; // FOR THE PLANTS

clock_t begin;
char runtime[256];






void player_movement(void) {
	CP_Settings_Fill(color_green);
	CP_Graphics_DrawCircle(x, y, 10);


	if (CP_Input_KeyDown(KEY_D)) { //ASCII value for D key
		x = x + 8;
	}
	if (CP_Input_KeyDown(KEY_A)) { //ASCII for A key
		x = x - 8;
	}
	if (CP_Input_KeyDown(KEY_W)) { //ASCII for W key
		y = y - 8;
	}
	if (CP_Input_KeyDown(KEY_S)) { //ASCII for S key
		y = y + 8;
	}
	CP_Graphics_ClearBackground(color_black);
	CP_Settings_Fill(color_green);
	CP_Graphics_DrawCircle(x, y, 15);

	//printf("x = %.2f\n y = %.2f\n\n", x, y);
}



void stationary_plants(float player_x, float player_y, float stationary_x, float stationary_y) {

	CP_Vector stationaryenemy, move;


	Vectorplayer = CP_Vector_Set(player_x, player_y);
	stationaryenemy = CP_Vector_Set(stationary_x, stationary_y);
	move = CP_Vector_Subtract(Vectorplayer, stationaryenemy);
	acceleration = CP_Vector_Scale(CP_Vector_Normalize(move), 4.5);

	position_x = stationaryenemy.x + acceleration.x;
	position_y = stationaryenemy.y + acceleration.y;

}


void game_init(void)
{
	CP_Graphics_ClearBackground(color_black);
	enemy_init_posXY();
	//printf("enemycount = %d\n", enemycount);

	begin = clock();

}






void game_update(void)
{
	player_movement();

	CP_Settings_Fill(color_red);
	enemy_draw(x, y);




	CP_Settings_Fill(color_blue);						//ambient stationary enemy plants
	stationary_plants(x, y, 100.0f, 100.0f);
	CP_Graphics_DrawCircle(position_x, position_y, 15);
	stationary_plants(x, y, 150.0f, 100.0f);
	CP_Graphics_DrawCircle(position_x, position_y, 15);
	stationary_plants(x, y, 200.0f, 100.0f);
	CP_Graphics_DrawCircle(position_x, position_y, 15);
	stationary_plants(x, y, 250.0f, 100.0f);
	CP_Graphics_DrawCircle(position_x, position_y, 15);
	stationary_plants(x, y, 300.0f, 100.0f);
	CP_Graphics_DrawCircle(position_x, position_y, 15);



	// CALUCULATE CLOCK
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	snprintf(runtime, 256, "%0.2f", time_spent);

	//DRAW CLOCK
	CP_Settings_Fill(color_red);
	CP_Font_DrawTextBox(runtime, 190.0f, 20.0f, 50.0f);


}//game_update






void game_exit(void)
{

}
