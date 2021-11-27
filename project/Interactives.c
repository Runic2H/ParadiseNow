#include "macros.h"

void chest_init(void)
{
	chest.alive = 1;
	chest.posX = CP_Random_RangeFloat(0.f,(float)CP_System_GetDisplayHeight());
	chest.posY = CP_Random_RangeFloat(0.f,(float)CP_System_GetDisplayHeight() - 400.f);
	chest.diameter = chestSize;
	chest.skill = CP_Random_RangeInt(0, 2);
}

//Part of render_chest
void chest_SpawnCheck(void)
{
	if (is_ChestColliding(chest.posX, chest.posY, chest.diameter, player.positionX, player.positionY, 20.f))
	{
		CP_Font_DrawTextBox("'E' to Open", (chest.posX) - 30.f, chest.posY - 30.f, 50.f);
		if (CP_Input_KeyTriggered(KEY_E))
		{
			add_skill(chest.skill);
			chest_init();
		}
	}
	if (timing != 0 && timing % 15 == 0)
	{
		chest.alive = 0;
	};
}

//Draw Chest
void render_Chest(float posX, float posY, float diameter)
{
	if (chest.alive == 1)
	{
		CP_Settings_Fill(color_blue);
		CP_Graphics_DrawCircle(chest.posX, chest.posY, chest.diameter);
	}
	else
	{
		chest_init();
	}
}

void add_skill(int skillno)
{
	switch (chest.skill)
	{
	case HEALTH:
		player.health += 1;
		break;
	case ATTACK:
		player.attack += 1;
		break;
	case MULTISHOT:
		player.multishot += 1;
		break;
	}
}
