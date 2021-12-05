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

int counter;


void menu_init(void) {

	CP_System_SetWindowSize(1280, 720);
	menu = CP_Image_Load("./images/menubackground.png");
	options = CP_Image_Load("./images/menuoptions.png");
}



void menu_update(void) {


	//if (CP_Input_KeyTriggered(KEY_ANY)) {
	//	CP_Engine_SetNextGameState(game_init, game_update, game_exit);
	//}

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

void menu_exit(void) {
	CP_Image_Free(&menu);
	CP_Image_Free(&options);
}