/*---------------------------------------------------------
 * file:	macros.c

 * author:	RICHMOND CHOO TZE YONG

 * email:	r.choo@digipen.edu
*
 * brief:	This file contains the functions for general
 *			purpose use cases such as timer functions to
 *			display timer, pause menu functions and other
 *			various rendering functions


 * Copyright © 2021 DigiPen, All rights reserved.
* ---------------------------------------------------------*/

#include "macros.h"

void howtoplay_init(void);
void howtoplay_update(void);
void howtoplay_exit(void);
char runtime[256];

/*-------------------------FUNCTION HEADER-----------------------*//*
function:	timer

author:		Richmond Choo

brief:		This function displays a timer for when game starts to
			indicate how long the player has survived

return:		-
*//*---------------------------------------------------------------*/
void timer(clock_t begin)
{
	clock_t end = clock();
	if (pause == 0) {
		double time_spent = (double)((double)end - (double)begin) / CLOCKS_PER_SEC;
		snprintf(runtime, 256, "%0.2f", time_spent);
		render_clock(time_spent);
		getTimeSpent((int)time_spent);
	}
}

/*-------------------------FUNCTION HEADER-----------------------*//*
function:	render_pause_menu()

author:		Richmond Choo

brief:		This function renders the various elements for the pause
			menu when the game is paused by the player

return:		-
*//*---------------------------------------------------------------*/
void render_pause_menu(void) {
	CP_Settings_Fill(color_pause);
	CP_Graphics_DrawRect(0.0f, 0.0f, 1280.0f, 720.0f);
	CP_Settings_Fill(color_red);
	CP_Settings_TextSize(30.0f);
	CP_Font_DrawTextBox("PAUSED", 595.0f, 30.0f, 500.0f);

	if (CP_Input_MouseTriggered(MOUSE_BUTTON_1)) {
		if (CP_Input_GetMouseX() >= 460.0f && CP_Input_GetMouseX() <= 810.0f
			&& CP_Input_GetMouseY() >= 235.0f && CP_Input_GetMouseY() <= 335.0f) {					//RESUME
			CP_Settings_Fill(color_white);
			CP_Graphics_DrawRect(460.0f, 235.0f, 350.0f, 100.0f);
			pause = 0;
		}

		if (CP_Input_GetMouseX() >= 460.0f && CP_Input_GetMouseX() <= 810.0f
			&& CP_Input_GetMouseY() >= 385.0f && CP_Input_GetMouseY() <= 485.0f) {					//TUTORIAL
			CP_Settings_Fill(color_white);
			CP_Graphics_DrawRect(460.0f, 385.0f, 350.0f, 100.0f);

			CP_Engine_SetNextGameState(howtoplay_init, howtoplay_update, howtoplay_exit);
		}

		if (CP_Input_GetMouseX() >= 460.0f && CP_Input_GetMouseX() <= 810.0f
			&& CP_Input_GetMouseY() >= 535.0f && CP_Input_GetMouseY() <= 635.0f) {					//MAIN MENU
			CP_Settings_Fill(color_white);
			CP_Graphics_DrawRect(460.0f, 535.0f, 350.0f, 100.0f);
			CP_Engine_SetNextGameState(menu_init, menu_update, menu_exit);
		}
	}

	CP_Settings_Fill(button_box);
	CP_Graphics_DrawRect(460.0f, 235.0f, 350.0f, 100.0f);
	CP_Graphics_DrawRect(460.0f, 385.0f, 350.0f, 100.0f);
	CP_Graphics_DrawRect(460.0f, 535.0f, 350.0f, 100.0f);

	CP_Settings_Fill(color_buttons);
	CP_Settings_TextSize(50.0f);
	CP_Font_DrawTextBox("RESUME", 550.0f, 300.0f, 500.0f);
	CP_Font_DrawTextBox("HOW TO PLAY", 505.0f, 450.0f, 500.0f);
	CP_Font_DrawTextBox("MAIN MENU", 525.0f, 600.0f, 500.0f);
}

/*-------------------------FUNCTION HEADER-----------------------*//*
function:	render_clock()

author:		Richmond Choo

brief:		This function renders the timer to display the time spent

return:		-
*//*---------------------------------------------------------------*/
void render_clock(double time_spent)
{
	CP_Settings_TextSize(30.0f);
	CP_Settings_Fill(color_red);
	CP_Font_DrawTextBox(runtime, (s_windowWidth/2.f), 50.0f, 500.0f);
}

/*-------------------------FUNCTION HEADER-----------------------*//*
function:	getTimeSpent()

author:		Elton Teo

brief:		This function returns the current time spent as a global
			variable for other functions requiring time implementation

return:		-
*//*---------------------------------------------------------------*/
int getTimeSpent(int time) //Used to get timing, auto run at timer();
{
	// returns time spent to global variable
	global_timing = (int)time;
	return global_timing;
}