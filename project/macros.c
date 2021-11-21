#include "macros.h"


char runtime[256];

void timer(clock_t begin)
{
	clock_t end = clock();
	double time_spent = (double)(end - begin)/CLOCKS_PER_SEC;
	snprintf(runtime, 256, "%0.2f", time_spent);
	render_clock(time_spent);
	getTimeSpent((int)time_spent);
}

void render_clock(double time_spent)
{
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