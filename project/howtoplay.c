#include "macros.h"
#include <stdio.h>
#include "cprocessing.h"

CP_Image howtoplay = NULL;

void menu_init(void);
void menu_update(void);
void menu_exit(void);


/*-------------------------FUNCTION HEADER-----------------------*//*
function: void howtoplay_init(void)

author: Richmond Choo

brief: loads an image into the variable. to be used in later
	functions.

return:	void
*//*---------------------------------------------------------------*/
void howtoplay_init(void) {

	howtoplay = CP_Image_Load("./images/howtoplay.png");
}




/*-------------------------FUNCTION HEADER-----------------------*//*
function: void howtoplay_update(void)

author: Richmond Choo

brief: draws the image loaded from the previous function
	sets up a button with collision detection, implementation

return: void
*//*---------------------------------------------------------------*/
void howtoplay_update(void) {


	if (CP_Input_MouseTriggered(MOUSE_BUTTON_1)) {
		if (CP_Input_GetMouseX() >= 530.0f && CP_Input_GetMouseX() <= 750.0f
			&& CP_Input_GetMouseY() >= 630.0f && CP_Input_GetMouseY() <= 695.0f) {
			CP_Settings_Fill(color_white);
			CP_Graphics_DrawRect(530.0f, 630.0f, 220.0f, 65.0f);
			CP_Engine_SetNextGameState(menu_init, menu_update, menu_exit);
		}
	}

	if (CP_Input_KeyTriggered(KEY_ESCAPE)) {
		CP_Engine_SetNextGameState(menu_init, menu_update, menu_exit);
	}


	CP_Image_Draw(howtoplay, 640.0f, 365.0f, 1280.0f, 735.0f, 255);

	CP_Settings_Fill(button_box);
	CP_Graphics_DrawRect(530.0f, 630.0f, 220.0f, 65.0f);
	CP_Settings_Fill(color_buttons);
	CP_Settings_TextSize(50.0f);
	CP_Font_DrawTextBox("RETURN", 555.0f, 677.0f, 220.0f);

}




/*-------------------------FUNCTION HEADER-----------------------*//*
function: void howtoplay_exit(void)

author: Richmond Choo

brief: frees up the memory used by the image. cleans up the file nicely

return:	void
*//*---------------------------------------------------------------*/
void howtoplay_exit(void) {

	CP_Image_Free(&howtoplay);

}