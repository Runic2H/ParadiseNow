#include "macros.h"
#include <stdio.h>
#include "cprocessing.h"

CP_Image gameover = NULL;

void game_init(void);
void game_update(void);
void game_exit(void);

void howtoplay_init(void);
void howtoplay_update(void);
void howtoplay_exit(void);

void menu_init(void);
void menu_update(void);
void menu_exit(void);


void gameover_init(void) {
	gameover = CP_Image_Load("./images/gameover.png");
}



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
	CP_Settings_Fill(button_box);
	CP_Graphics_DrawRect(290.0f, 320.0f, 215.0f, 40.0f);
	CP_Graphics_DrawRect(540.0f, 320.0f, 215.0f, 40.0f);
	CP_Graphics_DrawRect(790.0f, 320.0f, 215.0f, 40.0f);

	CP_Settings_Fill(color_buttons);
	CP_Settings_TextSize(35.0f);
	CP_Font_DrawTextBox("TUTORIAL", 320.0f, 350.0f, 300.0f);
	CP_Font_DrawTextBox("RESTART", 570.0f, 350.0f, 300.0f);
	CP_Font_DrawTextBox("MAIN MENU", 820.0f, 350.0f, 300.0f);

}

void gameover_exit(void) {

	CP_Image_Free(&gameover);

}