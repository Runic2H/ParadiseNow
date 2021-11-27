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
		CP_Font_DrawTextBox("'E' to Open", (chest.posX) - 35.f, chest.posY - 30.f, 100.f);
		if (CP_Input_KeyTriggered(KEY_E))
		{
			add_skill(chest.skill);
			chest_init();
		}
	}
	if (global_timing != 0 && global_timing % 15 == 0)
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

/*Things to do, research on moving vector textboxes, lecture have
Add More skills*/
void add_skill(int skillno)
{
	switch (chest.skill)
	{
	case HEALTH:
		player.health += 1;
		/*CP_Font_DrawText("Health +", (CP_System_GetWindowWidth() / 2.f), EaseInSine(min_y, max_y, (timeStart / duration)));*/
		break;
	case ATTACK:
		player.attack += 1;
		/*CP_Font_DrawText("Attack +", (CP_System_GetWindowWidth() / 2.f), EaseInSine(min_y, max_y, (timeStart / duration)));*/
		break;
	case MULTISHOT:
		player.multishot += 1;
		/*CP_Font_DrawText("Projectile +", (CP_System_GetWindowWidth() / 2.f), EaseInSine(min_y, max_y, (timeStart / duration)));*/
		break;
	}
}
