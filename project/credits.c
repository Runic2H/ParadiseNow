#include "macros.h"
#include "cprocessing.h"
#include <stdio.h>


void menu_init(void);
void menu_update(void);
void menu_exit(void);


CP_Image elton = NULL;
CP_Image hadi = NULL;
CP_Image richmond = NULL;
CP_Image louis = NULL;
CP_Image backgroundc = NULL;



void credits_init(void) {

	//elton = CP_Image_Load();
	//hadi = CP_Image_Load();
	//richmond = CP_Image_Load();
	//louis = CP_Image_Load();
	backgroundc = CP_Image_Load("./images/creditsbackground.png");
	elton = CP_Image_Load("./images/elton.png");
	hadi = CP_Image_Load("./images/hadi.png");
	richmond = CP_Image_Load("./images/richmond.png");
	louis = CP_Image_Load("./images/louis.png");
	CP_Graphics_ClearBackground(color_black);
}

void credits_update(void) {

	CP_Image_Draw(backgroundc, 640.0f, 365.0f, 1280.0f, 735.0f, 255);
	CP_Settings_Fill(color_white);
	CP_Settings_TextSize(25.0f);
	CP_Font_DrawText("  President: Claude Comair", 100.0f, 80.0f);
	CP_Font_DrawText("Instructors: Chen Ding Xiang - Professor", 100.0f, 150.0f);
	CP_Font_DrawText("                       Gerald Wong - Professor", 100.0f, 200.0f);

	CP_Settings_TextSize(30.0f);
	CP_Settings_Fill(color_buttons);
	CP_Font_DrawText("SlimeRush by ParadiseNow - CSD1400D", 750.0f, 80.0f);

	CP_Settings_TextSize(25.0f);
	CP_Settings_Fill(color_white);
	CP_Font_DrawText("Meet the team:",800.0f, 150.0f);
	CP_Font_DrawText("Elton: ", 800.0f, 250.0f);
	CP_Font_DrawText("Hadi: ", 800.0f, 350.0f);
	CP_Font_DrawText("Richmond: ", 800.0f, 450.0f);
	CP_Font_DrawText("Louis: ", 800.0f, 550.0f);


	CP_Settings_TextSize(15.0f);
	CP_Font_DrawText(" Lead developer in enemy implementation, spawn, and enemy implementation.", 800.0f, 570.0f);
	CP_Font_DrawText(" Centered on the graphics implementation, enemy application.", 800.0f, 470.0f);
	CP_Font_DrawText(" Aimed at character skills, and bug fixes.", 800.0f, 370.0f);
	CP_Font_DrawText(" Spearheaded character to enemy, and character to ambient interaction.", 800.0f, 270.0f);

	CP_Image_Draw(elton, 750.0f, 250.0f, 70.0f, 70.0f, 255);
	CP_Image_Draw(hadi, 750.0f, 350.0f, 70.0f, 70.0f, 255);
	CP_Image_Draw(richmond, 750.0f, 450.0f, 70.0f, 70.0f, 255);
	CP_Image_Draw(louis, 750.0f, 550.0f, 70.0f, 70.0f, 255);


	CP_Settings_Fill(button_box);
	CP_Graphics_DrawRect(130.0f, 370.0f, 215.0f, 40.0f);

	CP_Settings_Fill(color_buttons);
	CP_Settings_TextSize(35.0f);
	CP_Font_DrawTextBox("MAIN MENU", 150.0f, 400.0f, 300.0f);


	if (CP_Input_MouseTriggered(MOUSE_BUTTON_1)) {
		if (CP_Input_GetMouseX() >= 130.0f && CP_Input_GetMouseX() <= 315.0f					//tutorial
			&& CP_Input_GetMouseY() >= 370.0f && CP_Input_GetMouseY() <= 410.0f) {
			CP_Settings_Fill(color_white);
			CP_Graphics_DrawRect(130.0f, 370.0f, 215.0f, 40.0f);
			CP_Engine_SetNextGameState(menu_init, menu_update, menu_exit);
		}
	}


}


void credits_exit(void) {

	CP_Image_Free(&elton);
	CP_Image_Free(&hadi);
	CP_Image_Free(&richmond);
	CP_Image_Free(&louis);
	CP_Image_Free(&backgroundc);
}