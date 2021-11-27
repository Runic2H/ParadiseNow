#include "macros.h"

void howtoplay_init(void);
void howtoplay_update(void);
void howtoplay_exit(void);
char runtime[256];

void timer(clock_t begin)
{
	clock_t end = clock();
	if (pause == 0) {
		double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
		snprintf(runtime, 256, "%0.2f", time_spent);
		render_clock(time_spent);
		getTimeSpent((int)time_spent);
	}

	//to improve here, make the timing stop whilst game paused
}


void render_pause_menu(void) {
	CP_Settings_Fill(color_pause);
	CP_Graphics_DrawRect(0.0f, 0.0f, 1280.0f, 720.0f);
	CP_Settings_Fill(color_red);
	CP_Settings_TextSize(30.0f);
	CP_Font_DrawTextBox("PAUSED", 595.0f, 30.0f, 500.0f);

	if (CP_Input_MouseTriggered(MOUSE_BUTTON_1)) {
		if (CP_Input_GetMouseX() >= 460.0f && CP_Input_GetMouseX() <= 810.0f
			&& CP_Input_GetMouseY() >= 235.0f && CP_Input_GetMouseY() <= 335.0f) {
			CP_Settings_Fill(color_white);
			CP_Graphics_DrawRect(460.0f, 235.0f, 350.0f, 100.0f);
			pause = 0;
		}

		if (CP_Input_GetMouseX() >= 460.0f && CP_Input_GetMouseX() <= 810.0f
			&& CP_Input_GetMouseY() >= 385.0f && CP_Input_GetMouseY() <= 485.0f) {
			CP_Settings_Fill(color_white);
			CP_Graphics_DrawRect(460.0f, 385.0f, 350.0f, 100.0f);

			CP_Engine_SetNextGameState(howtoplay_init, howtoplay_update, howtoplay_exit);
		}

		if (CP_Input_GetMouseX() >= 460.0f && CP_Input_GetMouseX() <= 810.0f
			&& CP_Input_GetMouseY() >= 535.0f && CP_Input_GetMouseY() <= 635.0f) {
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


void render_clock(double time_spent)
{
	CP_Settings_TextSize(20.0f);
	CP_Settings_Fill(color_red);
	CP_Font_DrawTextBox(runtime, 640.f, 20.0f, 50.0f);
}

//Used to get timing, auto run at timer();
int getTimeSpent(int time)
{
	// returns time spent to global variable
	timing = (int)time;
	return timing;
}