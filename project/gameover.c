/*---------------------------------------------------------
 * file:	gameover.c
 * author:	ELTON TEO ZHE WEI
			LOUIS MINEO @ LINN MIN HTOO
			RICHMOND CHOO TZE YONG
			ABDUL HADI

 * email:	e.teo@digipen.edu
			louismineo.l@digipen.edu
			r.choo@digipen.edu
			abdulhadi.b@digipen.edu
*
 * brief:	This file contains logic behind the game's screen
 *			state after the player/character has depleted its health
 *			, thus game over.
 *


 * Copyright � 2021 DigiPen, All rights reserved.
* ---------------------------------------------------------*/

#include "macros.h"
#include <stdio.h>
#include "cprocessing.h"

CP_Image gameover = NULL;
char score[4];
char surv_time[4];

void game_init(void);
void game_update(void);
void game_exit(void);

void howtoplay_init(void);
void howtoplay_update(void);
void howtoplay_exit(void);

void menu_init(void);
void menu_update(void);
void menu_exit(void);

/*-------------------------FUNCTION HEADER-----------------------*//*
function:	gameover_init()

author:		Richmond Choo

			gameover_init loads the gameover art into memory as gameover.

			then creates logic over which button pressed by the mouse
			as it can change the game state to howtoplay, game_init
			or menu_init

Return : void
*//*---------------------------------------------------------------*/
void gameover_init(void) {
	gameover = CP_Image_Load("./images/gameover.png");
}


/*-------------------------FUNCTION HEADER-----------------------*//*
function:	gameover_update()

author:		Richmond Choo

			gameover_update loads the gameover art onto the screen.

			then creates logic over which button pressed by the mouse
			as it can change the game state to howtoplay, game_init
			or menu_init

Return : void
*//*---------------------------------------------------------------*/
void gameover_update(void) {

	CP_Image_Draw(gameover, 640.0f, 365.0f, 1280.0f, 735.0f, 255);


	if (CP_Input_MouseTriggered(MOUSE_BUTTON_1)) {
		if (CP_Input_GetMouseX() >= 290.0f && CP_Input_GetMouseX() <= 505.0f
			&& CP_Input_GetMouseY() >= 320.0f && CP_Input_GetMouseY() <= 360.0f) {
			CP_Settings_Fill(color_white);
			CP_Graphics_DrawRect(290.0f, 320.0f, 215.0f, 40.0f);
			CP_Engine_SetNextGameState(howtoplay_init, howtoplay_update, howtoplay_exit);
		}

		if (CP_Input_GetMouseX() >= 540.0f && CP_Input_GetMouseX() <= 755.0f						//restart
			&& CP_Input_GetMouseY() >= 320.0f && CP_Input_GetMouseY() <= 360.0f) {
			CP_Settings_Fill(color_white);
			CP_Graphics_DrawRect(540.0f, 320.0f, 215.0f, 40.0f);
			CP_Engine_SetNextGameState(game_init, game_update, game_exit);
		}

		if (CP_Input_GetMouseX() >= 790.0f && CP_Input_GetMouseX() <= 1005.0f						//restart
			&& CP_Input_GetMouseY() >= 320.0f && CP_Input_GetMouseY() <= 360.0f) {
			CP_Settings_Fill(color_white);
			CP_Graphics_DrawRect(790.0f, 320.0f, 215.0f, 40.0f);
			CP_Engine_SetNextGameState(menu_init, menu_update, menu_exit);
		}
	}


	//draw

	snprintf(score, 4, "%d", player.score);
	snprintf(surv_time, 4, "%d", getTimeSpent(global_timing));

	CP_Settings_Fill(button_box);
	CP_Graphics_DrawRect(290.0f, 270.0f, 215.0f, 40.0f);
	CP_Graphics_DrawRect(790.0f, 270.0f, 215.0f, 40.0f);
	CP_Graphics_DrawRect(290.0f, 320.0f, 215.0f, 40.0f);
	CP_Graphics_DrawRect(540.0f, 320.0f, 215.0f, 40.0f);
	CP_Graphics_DrawRect(790.0f, 320.0f, 215.0f, 40.0f);

	CP_Settings_Fill(color_buttons);
	CP_Settings_TextSize(35.0f);
	CP_Font_DrawTextBox("SCORE: ", 300.0f, 300.0f, 300.0f);
	CP_Font_DrawText(score, 400.f, 300.f);
	CP_Font_DrawTextBox("TIME(s): ", 800.0f, 300.0f, 300.0f);
	CP_Font_DrawText(surv_time, 920.f, 300.f);
	CP_Font_DrawTextBox("TUTORIAL", 320.0f, 350.0f, 300.0f);
	CP_Font_DrawTextBox("RESTART", 570.0f, 350.0f, 300.0f);
	CP_Font_DrawTextBox("MAIN MENU", 820.0f, 350.0f, 300.0f);

}
/*-------------------------FUNCTION HEADER-----------------------*//*
function:	gameover_exit()

author:		Richmond Choo

			gameover_exit frees the image from memory

Return : void
*//*---------------------------------------------------------------*/
void gameover_exit(void) {

	CP_Image_Free(&gameover);

}