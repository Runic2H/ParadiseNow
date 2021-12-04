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

CP_Image menu = NULL;
CP_Image digipen = NULL;

CP_Sound menu_music = NULL;

int counter;


void menu_init(void) {

	CP_System_SetWindowSize(1280, 720);
	menu = CP_Image_Load("./images/menubackground.png");

	menu_music = CP_Sound_LoadMusic("./Sounds/menu.wav");
	CP_Sound_PlayMusic(menu_music);
}



void menu_update(void) {


	if (CP_Input_KeyTriggered(KEY_ENTER)) {
		CP_Engine_SetNextGameState(game_init, game_update, game_exit);
	}

	CP_Image_Draw(menu, 640.0f, 365.0f, 1280.0f, 735.0f, 255);

	if (CP_Input_MouseTriggered(MOUSE_BUTTON_1)) {
		if (CP_Input_GetMouseX() >= 480.0f && CP_Input_GetMouseX() <= 780.0f
			&& CP_Input_GetMouseY() >= 500.0f && CP_Input_GetMouseY() <= 585.0f) {
			CP_Settings_Fill(color_white);
			CP_Graphics_DrawRect(480.0f, 500.0f, 300.0f, 85.0f);
			CP_Engine_SetNextGameState(howtoplay_init, howtoplay_update, howtoplay_exit);
		}
	}

	//DRAW
	CP_Settings_Fill(color_white);
	CP_Settings_TextSize(55.0f);
	CP_Font_DrawTextBox("PRESS ENTER TO START GAME", 340.0f, 100.0f, 1000.0f);
	CP_Settings_Fill(button_box);
	CP_Graphics_DrawRect(480.0f, 500.0f, 300.0f, 85.0f);
	CP_Settings_Fill(color_buttons);
	CP_Settings_TextSize(50.0f);
	CP_Font_DrawTextBox("HOW TO PLAY", 501.0f, 558.0f, 300.0f);
}

void menu_exit(void) {
	
	CP_Image_Free(&menu);
	CP_Image_Free(&digipen);
	CP_Sound_Free(&menu_music);

}