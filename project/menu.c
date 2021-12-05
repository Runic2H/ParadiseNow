/*---------------------------------------------------------
 * file:	game.c
 *
 * author:	LOUIS MINEO @ LINN MIN HTOO
			RICHMOND CHOO TZE YONG

 * email:	louismineo.l@digipen.edu
			r.choo@digipen.edu
*
 * brief:	This file contains the main menu loading sequence
 *	that is launched right after digipenlogo.c
 *  is used to launch more sequences such as
 * - credits.c
 * - howtoplay.c
 * - game.c


 * Copyright © 2021 DigiPen, All rights reserved.
* ---------------------------------------------------------*/


#include <stdio.h>
#include "cprocessing.h"
#include "macros.h"

/* Forward declarations */
void game_init(void);
void game_update(void);
void game_exit(void);

void howtoplay_init(void);
void howtoplay_update(void);
void howtoplay_exit(void);

void credits_init(void);
void credits_update(void);
void credits_exit(void);


CP_Image menu = NULL;
CP_Image options = NULL;

CP_Sound menu_music = NULL;

int counter;



/*-------------------------FUNCTION HEADER-----------------------*//*
function: menu_init (void)

author: Richmond Choo, Louis Mineo

brief: this function initialises sound, window width, and images
	to be used in later functions.
	plays music on startup

return:	void
*//*---------------------------------------------------------------*/
void menu_init(void) {

	CP_System_SetWindowSize(1280, 720);
	menu = CP_Image_Load("./images/menubackground.png");
	menu_music = CP_Sound_LoadMusic("./Sounds/menu.wav");
	CP_Sound_PlayMusic(menu_music);
	options = CP_Image_Load("./images/menuoptions1.png");
}




/*-------------------------FUNCTION HEADER-----------------------*//*
function: void menu_update(void)

author: Richmond Choo

brief: this function draws the images whose variables are declared in
	the previous function. checks for button collisions, and
	implementation.
	buttons -> start game, how to play, quit game, credits.

return:	void
*//*---------------------------------------------------------------*/
void menu_update(void) {

	CP_Image_Draw(menu, 640.0f, 365.0f, 1280.0f, 735.0f, 255);
	CP_Image_Draw(options, 645.0f, 550.0f, 700.0f, 100.0f, 255);

	if (CP_Input_MouseTriggered(MOUSE_BUTTON_1)) {
		if (CP_Input_GetMouseX() >= 303.0f && CP_Input_GetMouseX() <= 468.0f					//tutorial
			&& CP_Input_GetMouseY() >= 504.0f && CP_Input_GetMouseY() <= 593.0f) {
			CP_Settings_Fill(color_white);										
			CP_Graphics_DrawRect(303.0f, 504.0f, 165.0f, 89.0f);
			CP_Engine_SetNextGameState(howtoplay_init, howtoplay_update, howtoplay_exit);
		}

		if (CP_Input_GetMouseX() >= 494.0f && CP_Input_GetMouseX() <= 626.0f					//start game
			&& CP_Input_GetMouseY() >= 507.0f && CP_Input_GetMouseY() <= 593.0f) {
			CP_Settings_Fill(color_white);
			CP_Graphics_DrawRect(494.0f, 507.0f, 132.0f, 89.0f);
			CP_Engine_SetNextGameState(game_init, game_update, game_exit);
		}


		if (CP_Input_GetMouseX() >= 657.0f && CP_Input_GetMouseX() <= 793.0f					//exit game
			&& CP_Input_GetMouseY() >= 504.0f && CP_Input_GetMouseY() <= 593.0f) {
			CP_Settings_Fill(color_white);
			CP_Graphics_DrawRect(657.0f, 504.0f, 132.0f, 89.0f);
			CP_Engine_Terminate();
		}


		if (CP_Input_GetMouseX() >= 820.0f && CP_Input_GetMouseX() <= 972.0f					//credits
			&& CP_Input_GetMouseY() >= 504.0f && CP_Input_GetMouseY() <= 593.0f) {
			CP_Settings_Fill(color_white);
			CP_Graphics_DrawRect(820.0f, 504.0f, 165.0f, 89.0f);
			CP_Engine_SetNextGameState(credits_init, credits_update, credits_exit);
		}
	}
}



/*-------------------------FUNCTION HEADER-----------------------*//*
function: void menu_exit(void)

author: Richmond Choo

brief: this function frees up the memory spaces used by the image
	variables. cleans up the file nicely.

return:	void
*//*---------------------------------------------------------------*/
void menu_exit(void) {
	CP_Image_Free(&menu);
	CP_Sound_Free(&menu_music);
	CP_Image_Free(&options);
}