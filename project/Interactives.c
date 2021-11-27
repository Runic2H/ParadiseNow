#include "macros.h"

void chest_init(void)
{
	chest.alive = TRUE;
	chest.posX = CP_Random_RangeFloat(0.f,(float)CP_System_GetDisplayHeight());
	chest.posY = CP_Random_RangeFloat(0.f,(float)CP_System_GetDisplayHeight() - 400.f);
	chest.diameter = chestSize;
	chest.skill = CP_Random_RangeInt(0, 4);
}

//Part of render_chest
void chest_SpawnCheck(void)
{
	if (is_ChestColliding(chest.posX, chest.posY, chest.diameter, player.positionX, player.positionY, 20.f))
	{
		if (CP_Input_KeyTriggered(KEY_E) && player.gold >= 25)
		{
			add_skill(chest.skill);
			player.gold -= 25;
			if (player.gold < 0)
			{
				player.gold = 0;
			}
			chest_init();
		}
	}
	if (global_timing != 0 && global_timing % 15 == 0)
	{
		chest.alive = FALSE;
	};
}

//Draw Chest
void render_Chest(float posX, float posY, float diameter)
{
	if (chest.alive == TRUE)
	{
		CP_Settings_Fill(color_white);
		if (is_ChestColliding(chest.posX, chest.posY, chest.diameter, player.positionX, player.positionY, 20.f))
		{
			if (CP_Input_KeyTriggered(KEY_E) || player.gold < 25)
			{
				CP_Font_DrawTextBox("Not Enough Gold! (25)", (chest.posX) - 55.f, chest.posY - 30.f, 200.f);
			}
			else
			{
				CP_Font_DrawTextBox("Press 'E' (25 gold)", (chest.posX) - 55.f, chest.posY - 30.f, 200.f);
			}
		}
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
		player.MAXhealth += 1;
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
	case HEAL:
		player.health += 2;
		if (player.health >= player.MAXhealth)
		{
			player.health = player.MAXhealth;
		}
		break;
	case SHIELD:
		player.shield = 1;
		break;
	}
}
