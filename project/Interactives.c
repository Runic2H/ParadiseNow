#include "macros.h"

char skill[4];

void chest_init(void)
{
	chest.alive = TRUE;
	chest.posX = CP_Random_RangeFloat(100.f,(float)s_windowWidth - 100.f);
	chest.posY = CP_Random_RangeFloat(100.f,(float)s_windowHeight - 100.f);
	chest.diameter = chestSize;
	chest.skill = CP_Random_RangeInt(HEALTH, SHIELD);
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
			chest.alive = FALSE;
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
			if (player.gold < 25)
			{
				CP_Settings_TextSize(20.f);
				CP_Font_DrawTextBox("Not Enough Gold (25)", chest.posX - 70.f, chest.posY - 30.f, 200.f);
			}
			else if (player.gold >= 25)
			{
				CP_Settings_TextSize(20.f);
				CP_Font_DrawTextBox("Press 'E' (25 gold)", chest.posX - 65.f, chest.posY - 30.f, 200.f);
			}
		}
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
		player.MAXhealth += 1;
		break;
	case ATTACK:
		player.attack += 1;
		break;
	case MULTISHOT:
		player.multishot += 1;
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

void render_skill(int skillno)
{
	if (chest.alive == FALSE)
	{
		if (chest.skill == 0)
		{
			CP_Font_DrawText("Health +", (s_windowWidth / 2.f) - 65.f, EaseInSine(min_y, max_y, (timerStart / duration)));
		}
		else if (chest.skill == 1)
		{
			CP_Font_DrawText("Attack +", (s_windowWidth / 2.f) - 65.f, EaseInSine(min_y, max_y, (timerStart / duration)));
		}
		else if (chest.skill == 2)
		{
			CP_Font_DrawText("Projectile +", (s_windowWidth / 2.f) - 65.f, EaseInSine(min_y, max_y, (timerStart / duration)));
		}
		else if (chest.skill == 3)
		{
			CP_Font_DrawText("Healing", (s_windowWidth / 2.f) - 65.f, EaseInSine(min_y, max_y, (timerStart / duration)));
		}
		else if (chest.skill == 4)
		{
			CP_Font_DrawText("Energy Shield", (s_windowWidth / 2.f) - 65.f, EaseInSine(min_y, max_y, (timerStart / duration)));
		}
	}
}
