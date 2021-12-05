/*---------------------------------------------------------
 * file:	digipenlogo.c
 * author:	RICHMOND CHOO TZE YONG

 * email:	r.choo@digipen.edu
*
 * brief:	This file contains logic behind the game's starting
 *			sequence containing the school's logo
 *


 * Copyright © 2021 DigiPen, All rights reserved.
* ---------------------------------------------------------*/

#include "macros.h"
#include "cprocessing.h"
#include <stdio.h>


void menu_init(void);
void menu_update(void);
void menu_exit(void);

CP_Image digipenz = NULL;

/*-------------------------FUNCTION HEADER-----------------------*//*
function:	digipen_init()

author:		Richmond Choo

			digipen_init loads the digipen logo into memory as digipenz
Return : -
*//*---------------------------------------------------------------*/
void digipen_init(void) {
	CP_System_SetWindowSize(1280, 720);
	digipenz = CP_Image_Load("./images/digipenlogo.png");
}

/*-------------------------FUNCTION HEADER-----------------------*//*
function:	digipen_update()

author:		Richmond Choo

			digipen_update displays the image by fading it from black,
			into the image. then transitions to the menu.c screen

Return : -
*//*---------------------------------------------------------------*/
void digipen_update(void) {

	static float alpha = 0;
	static bool hasreachedalpha = 0;
	static float counter = 0;




	if (hasreachedalpha == 0) {
		alpha += 100 * CP_System_GetDt();
		CP_Image_Draw(digipenz, 640.0f, 365.0f, 1280.0f, 735.0f, (int)alpha);
	}

	if (alpha >= 255) {
		alpha = 255;
		hasreachedalpha = 1;
	}

	if (hasreachedalpha) {
		counter += CP_System_GetDt();	//accumulates number
		CP_Graphics_ClearBackground(color_black);
		CP_Settings_Fill(color_white);
		CP_Settings_TextSize(70.0f);
		CP_Font_DrawTextBox("LOADING...", 530.0f, 360.0f, 300.0f);
	}

	if (counter >= 0.20f) {
		CP_Engine_SetNextGameState(menu_init, menu_update, menu_exit);
	}


}

/*-------------------------FUNCTION HEADER-----------------------*//*
function:	digipen_exit()

author:		Richmond Choo

			digipen_exit frees the image from memory

Return : -
*//*---------------------------------------------------------------*/
void digipen_exit(void) {

	CP_Image_Free(&digipenz);
}







/*
*
*	use LERP. ask for start and end, creates a number range. input number to fit into range.
*	parametrisiation.
*	2 seconds fade in.
	1 second mark, 50% done. time accumulated
	acucmulated time / ending time = number between 0-1
	interpolate => 1-(eqn29)


*
	fade in
	hold
	fade out
	main menu
	*/