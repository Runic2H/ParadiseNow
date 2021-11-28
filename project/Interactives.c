#include "macros.h"

char skill[4];

void chest_init(void)
{
	chest.alive = TRUE;
	chest.posX = CP_Random_RangeFloat(100.f,(float)s_windowWidth - 100.f);
	chest.posY = CP_Random_RangeFloat(100.f,(float)s_windowHeight - 100.f);
	chest.diameter = chestSize;
	chest.skill = CP_Random_RangeInt(HEALTH, SHIELD);
	chest.cooldown = 0.0f;
}

//Part of render_chest
void chest_SpawnCheck(void)
{
	if (is_ChestColliding(chest.posX, chest.posY, chest.diameter, player.positionX, player.positionY, 20.f))
	{
		if (CP_Input_KeyTriggered(KEY_SPACE) && player.gold >= 25 && chest.cooldown <= 0.f)
		{
			chest.cooldown = 2.f;
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
	chest.cooldown -= CP_System_GetDt();
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
				CP_Font_DrawTextBox("Not Enough Gold (25 gold)", chest.posX - 70.f, chest.posY - 30.f, 250.f);
			}
			else if (player.gold >= 25)
			{
				CP_Settings_TextSize(20.f);
				CP_Font_DrawTextBox("Press 'Space' (25 gold)", chest.posX - 65.f, chest.posY - 30.f, 250.f);
			}
		}
		CP_Graphics_DrawCircle(chest.posX, chest.posY, chest.diameter);
	}
	else
	{
		if (chest.cooldown <= 0.f)
		{
			chest_init();
		}
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
		player.damageCooldown = 1.0f;
		break;
	case SHIELD:
		player.shield = 1;
		break;
	}
}

void render_skill(int skillno)
{
	CP_Settings_Fill(color_white);
	if (chest.cooldown >= 0.0f && chest.alive == FALSE)
	{
		CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
		if (chest.skill == HEALTH)
		{
			CP_Font_DrawText("Health +", (s_windowWidth / 2.f), EaseInSine(min_y, max_y, (timerStart / duration)));
		}
		else if (chest.skill == ATTACK)
		{
			CP_Font_DrawText("Attack +", (s_windowWidth / 2.f), EaseInSine(min_y, max_y, (timerStart / duration)));
		}
		else if (chest.skill == MULTISHOT)
		{
			CP_Font_DrawText("Projectile +", (s_windowWidth / 2.f), EaseInSine(min_y, max_y, (timerStart / duration)));
		}
		else if (chest.skill == HEAL)
		{
			CP_Font_DrawText("Healing", (s_windowWidth / 2.f), EaseInSine(min_y, max_y, (timerStart / duration)));
		}
		else if (chest.skill == SHIELD)
		{
			CP_Font_DrawText("Energy Shield", (s_windowWidth / 2.f), EaseInSine(min_y, max_y, (timerStart / duration)));
		}
		CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_LEFT, CP_TEXT_ALIGN_V_BASELINE);
	}
}
