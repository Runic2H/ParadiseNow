#include "macros.h"

struct upgrades chest;

void chest_init(void)
{
	chest.alive = 0;
	chest.diameter = 30.f;
	chest.posX = CP_Random_RangeFloat(200.f, 400.f);
	chest.posY = CP_Random_RangeFloat(200.f, 400.f);
}

void chest_spawn(void)
{
	if (chest.alive == 0)
	{
		render_Chest(chest.posX, chest.posY, chest.diameter);
		chest.alive = 1;
	}
}

void render_Chest(float posX, float posY, float diameter)
{
	CP_Settings_Fill(color_blue);
	CP_Graphics_DrawCircle(chest.posX, chest.posY, chest.diameter);
}
