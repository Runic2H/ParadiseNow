#include "macros.h"

char skill[4];

CP_Sound chest_open = NULL;

void chest_init(void)
{
	chest.alive = TRUE;
	chest.posX = CP_Random_RangeFloat(100.f,(float)s_windowWidth - 100.f);
	chest.posY = CP_Random_RangeFloat(100.f,(float)s_windowHeight - 100.f);
	chest.diameter = chestSize;
	chest.skill = CP_Random_RangeInt(HEALTH, SHIELD);
	chest.cooldown = 0.0f;


	// sound init
	chest_open = CP_Sound_LoadMusic("./Sounds/chest_open.wav");
}

//Part of render_chest
void chest_SpawnCheck(void)
{
	if (is_ChestColliding(chest.posX, chest.posY, chest.diameter, player.positionX, player.positionY, 20.f))
	{
		if (player.gold >= 55 && chest.cooldown <= 0.f)
		{
			chest.cooldown = 2.f;
			add_skill(chest.skill);
			player.gold -= 55;
			if (player.gold < 0)
			{
				player.gold = 0;
			}
			chest.alive = FALSE;

			//play sound of opening chest
			CP_Sound_Play(chest_open);
		}
	}
	if (global_timing != 0 && global_timing % 45 == 0)
	{
		chest.alive = FALSE;
	};
	chest.cooldown -= CP_System_GetDt();
}

//Draw Chest
void render_Chest(float posX, float posY, float diameter, CP_Image chestZ)
{
	if (chest.alive == TRUE)
	{
		CP_Settings_Fill(color_white);
		if (is_ChestColliding(chest.posX, chest.posY, chest.diameter, player.positionX, player.positionY, 20.f))
		{
			if (player.gold < 55)
			{
				CP_Settings_TextSize(20.f);
				CP_Font_DrawText("Not Enough Gold! (55 gold)", chest.posX - 100.f, chest.posY - 30.f);
			}
		}
		//CP_Graphics_DrawCircle(chest.posX, chest.posY, chest.diameter);
		CP_Image_Draw(chestZ, chest.posX, chest.posY, 30.0f, 30.0f, 255);
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
		if (player.health == player.MAXhealth)
		{
			player.MAXhealth++;
			player.health = player.MAXhealth;
		}
		else
		{
			player.health += 2;
			if (player.health >= player.MAXhealth)
			{
				player.health = player.MAXhealth;
			}
		}
		player.damageCooldown = 1.0f;
		player.damageTaken = 0;
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

		CP_Font_DrawText("Opened!", chest.posX, Linear(chest.posY, chest.posY - 20.f, (timerStart / duration)));
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
