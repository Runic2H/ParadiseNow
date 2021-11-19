#include <stdio.h>
#include "cprocessing.h"


/* Forward declarations */
void game_init(void);
void game_update(void);
void game_exit(void);
#define color_background CP_Color_Create(50, 100, 0, 255)


void menu_init(void) {

	CP_System_SetWindowSize(1280, 720);
	CP_Graphics_ClearBackground(color_background);

}

/*
	mouse coords x y
	keyboard button press.

	menu state = 0
	button up = 1
	button up = 2

	when space is pressed, select the current button


*/


void menu_update(void) {

	if (CP_Input_KeyTriggered(KEY_ENTER)) {
		CP_Engine_SetNextGameState(game_init, game_update, game_exit);
	}

}

void menu_exit(void) {

}