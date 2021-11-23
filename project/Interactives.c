#include "macros.h"



void chest_init(void)
{
	chest.posX = CP_Random_RangeFloat(0.f,(float)CP_System_GetDisplayHeight());
	chest.posY = CP_Random_RangeFloat(0.f,(float)CP_System_GetDisplayHeight() - 400.f);
	chest.alive = 1;
	chest.diameter = chestSize;
	chest.skill = CP_Random_RangeInt(1, 2);
}

void chest_spawn(void)
{
	if (chest.alive == 1)
	{
		render_Chest(chest.posX, chest.posY, chest.diameter);
		if (timing % 15 == 0)
		{
			chest.alive = 0;
			CP_Graphics_ClearBackground(color_background);
			chest_init();
		}
	}
}

void render_Chest(float posX, float posY, float diameter)
{
	CP_Settings_Fill(color_blue);
	CP_Graphics_DrawCircle(chest.posX, chest.posY, chest.diameter);
}

void chest_collision(float playerX, float playerY)
{
	if (is_ChestColliding(chest.posX, chest.posY, chest.diameter, playerX, playerY, 20.f))
	{
		CP_Font_DrawTextBox("'E' to Open", (chest.posX) - 30.f, chest.posY - 30.f, 100.f);
		if (CP_Input_KeyTriggered(KEY_E))
		{
			chest.alive = 0;
			CP_Graphics_ClearBackground(color_background);
			chest_init();
		}
	}
}
