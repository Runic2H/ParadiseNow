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


/*-------------------------FUNCTION HEADER-----------------------*//*
function: void credits_init(void)

author: Richmond Choo

brief: This function loads all the cp_image variables with their
	respective images, to be used in the later function

return:	void
*//*---------------------------------------------------------------*/
void credits_init(void) {

	backgroundc = CP_Image_Load("./images/creditsbackground.png");
	elton = CP_Image_Load("./images/elton.png");
	hadi = CP_Image_Load("./images/hadi.png");
	richmond = CP_Image_Load("./images/richmond.png");
	louis = CP_Image_Load("./images/louis.png");
}







/*-------------------------FUNCTION HEADER-----------------------*//*
function: void credits_update(void)

author: Richmond Choo

brief: this function uses the image variables declared previously in
	the init function. Draws various textbox, button collision,
	and implementation

return:	void
*//*---------------------------------------------------------------*/
void credits_update(void) {



	CP_Image_Draw(backgroundc, 640.0f, 365.0f, 1280.0f, 735.0f, 255);
	CP_Settings_Fill(color_green);
	CP_Settings_TextSize(55.0f);
	CP_Font_DrawText("SLIME RUSH", 515.0f, 94.0f);
	CP_Settings_TextSize(35.0f);
	CP_Font_DrawText("ParadiseNow", 515.0f, 115.0f);
	CP_Settings_TextSize(25.0f);
	CP_Settings_Fill(color_white);
	CP_Font_DrawText(" Created at:    DigiPen Institute of Technology Singapore", 380.0f, 140.0f);
	
	
	CP_Settings_TextSize(50.0f);
	CP_Settings_Fill(color_buttons);
	CP_Font_DrawText("President:", 46.0f, 195.0f);
	CP_Settings_Fill(color_white);
	CP_Settings_TextSize(25.0f);
	CP_Font_DrawText("Claude Comair",46.0f, 225.0f);

	CP_Settings_TextSize(50.0f);
	CP_Settings_Fill(color_buttons);
	CP_Font_DrawText("Executives:", 46.0f, 350.0f);
	CP_Settings_Fill(color_white);
	CP_Settings_TextSize(25.0f);
	CP_Font_DrawText("Jason Chu", 46.0f, 380.0f);
	CP_Font_DrawText("Michael Gats", 46.0f, 400.0f);
	CP_Font_DrawText("Raymond Yan", 46.0f, 420.0f);
	CP_Font_DrawText("Prasanna Ghali", 46.0f, 440.0f);
	CP_Font_DrawText("Erik Mohrmann", 46.0f, 460.0f);
	CP_Font_DrawText("Angela Kugler", 46.0f, 480.0f);
	CP_Font_DrawText("Ben Ellinger", 46.0f, 500.0f);
	//
	CP_Font_DrawText("Christopher Comair", 260.0f, 380.0f);
	CP_Font_DrawText("Michele Comair", 260.0f, 400.0f);
	CP_Font_DrawText("Samir Abou Samra", 260.0f, 420.0f);
	CP_Font_DrawText("John Bauer", 260.0f, 440.0f);
	CP_Font_DrawText("Melvin Gonsalvez", 260.0f, 460.0f);
	CP_Font_DrawText("Charles Duba", 260.0f, 480.0f);
	CP_Font_DrawText("Johnny Deek", 260.0f, 500.0f);
	//
	
	CP_Settings_TextSize(50.0f);
	CP_Settings_Fill(color_buttons);
	CP_Font_DrawText("Instructors:", 46.0f, 600.0f);
	CP_Settings_Fill(color_white);
	CP_Settings_TextSize(25.0f);
	CP_Font_DrawText("Chen Ding Xiang - Professor", 46.0f, 630.0f);
	CP_Font_DrawText("Gerald Wong - Professor", 46.0f, 660.0f);

	//
	CP_Settings_TextSize(25.0f);
	CP_Settings_Fill(color_white);
	CP_Font_DrawText("Elton: ", 800.0f, 250.0f);
	CP_Font_DrawText("Hadi: ", 800.0f, 350.0f);
	CP_Font_DrawText("Richmond: ", 800.0f, 450.0f);
	CP_Font_DrawText("Louis: ", 800.0f, 550.0f);

	CP_Settings_TextSize(17.0f);
	CP_Font_DrawText(" Programmer - Enemies, collision", 800.0f, 570.0f);
	CP_Font_DrawText(" Programmer - Graphics, enemies", 800.0f, 470.0f);
	CP_Font_DrawText(" Programmer - Character skill", 800.0f, 370.0f);
	CP_Font_DrawText(" Programmer - Character, item interactions", 800.0f, 270.0f); //elton


	CP_Image_Draw(elton, 750.0f, 250.0f, 70.0f, 70.0f, 255);
	CP_Image_Draw(hadi, 750.0f, 350.0f, 70.0f, 70.0f, 255);
	CP_Image_Draw(richmond, 750.0f, 450.0f, 70.0f, 70.0f, 255);
	CP_Image_Draw(louis, 750.0f, 550.0f, 70.0f, 70.0f, 255);


	CP_Settings_Fill(button_box);
	CP_Graphics_DrawRect(500.0f, 656.0f, 150.0f, 35.0f);

	CP_Settings_Fill(color_buttons);
	CP_Settings_TextSize(25.0f);
	CP_Font_DrawTextBox("MAIN MENU", 520.0f, 680.0f, 150.0f);


	if (CP_Input_MouseTriggered(MOUSE_BUTTON_1)) {
		if (CP_Input_GetMouseX() >= 500.0f && CP_Input_GetMouseX() <= 650.0f					//tutorial
			&& CP_Input_GetMouseY() >= 656.0f && CP_Input_GetMouseY() <= 691.0f) {
			CP_Settings_Fill(color_white);
			CP_Graphics_DrawRect(500.0f, 656.0f, 150.0f, 35.0f);
			CP_Engine_SetNextGameState(menu_init, menu_update, menu_exit);
		}
	}


}




/*-------------------------FUNCTION HEADER-----------------------*//*
function: void credits_exit(void)

author: Richmond Choo

brief: frees up memory used by the image variable. cleans up the entire
	file nicely.

return:	void
*//*---------------------------------------------------------------*/
void credits_exit(void) {

	CP_Image_Free(&elton);
	CP_Image_Free(&hadi);
	CP_Image_Free(&richmond);
	CP_Image_Free(&louis);
	CP_Image_Free(&backgroundc);
}