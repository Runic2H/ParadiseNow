#include "macros.h"

char health[4];
void c_CharacterInit(void)
{
	player.positionX = 200.f;
	player.positionY = 200.f;
	player.diameter = 20.f;
	player.exp = 0;
	player.gold = 0;
	player.attack = 1;
	player.health = 10;
	player.multishot = 1;
	player.damageCooldown = 1.0f;
}

void c_CharacterWASD(float *objPositionX, float *objPositionY)
{
	CP_Vector direction = {10,10};
	CP_Vector velocity = CP_Vector_Scale(CP_Vector_Normalize(direction), 400.f * CP_System_GetDt());
	CP_Matrix rotate = CP_Matrix_Rotate(45.0f);
	CP_Vector movement = CP_Vector_MatrixMultiply(rotate, velocity);
	if (CP_Input_MouseDown(MOUSE_BUTTON_2))
	{
		//To implement looking around
	}
	else
	{
		if (CP_Input_KeyDown(KEY_W))
		{
			if (CP_Input_KeyDown(KEY_A))
			{
				*objPositionX += movement.x/2;
				*objPositionY -= movement.y/2;
			}
			else if (CP_Input_KeyDown(KEY_D))
			{
				*objPositionX -= movement.x/2;
				*objPositionY -= movement.y/2;
			}
			else
			{
				*objPositionY -= velocity.y;
			}
		}
		if (CP_Input_KeyDown(KEY_S))
		{
			if (CP_Input_KeyDown(KEY_A))
			{
				*objPositionX -= movement.x/2;
				*objPositionY += movement.y/2;
			}
			else if (CP_Input_KeyDown(KEY_D))
			{
				*objPositionX -= movement.x/2;
				*objPositionY += movement.y/2;
			}
			else
			{
				*objPositionY += velocity.y;
			}
		}
		if (CP_Input_KeyDown(KEY_A))
		{
			*objPositionX -= velocity.x;
		}
		if (CP_Input_KeyDown(KEY_D))
		{
			*objPositionX += velocity.x;
		}
	}

}

void c_CharacterMouse(float* objPositionX, float* objPositionY)
{
	CP_Vector playerVector = CP_Vector_Set(*objPositionX, *objPositionY);
	CP_Vector mouseVector = CP_Vector_Set(CP_Input_GetMouseX(), CP_Input_GetMouseY());
	CP_Vector directionVector = CP_Vector_Subtract(mouseVector, playerVector);
	CP_Vector speed = CP_Vector_Scale(CP_Vector_Normalize(directionVector), 300.f * CP_System_GetDt());
	if (CP_Input_MouseDown(MOUSE_BUTTON_2))
	{
		//To implement looking around
	}
	else
	{
		*objPositionX += speed.x;
		*objPositionY += speed.y;
	}
}

void renderPlayer(float* positionX, float* positionY,CP_Image mage)
{
	CP_Settings_Fill(color_white);
	//CP_Graphics_DrawCircle(*positionX, *positionY, 20);
	CP_Image_Draw(mage, *positionX, *positionY, 100, 100, 255);
}

void playerCollide(float* objPositionX, float* objPositionY) {
	for (int i = 0; i < enemycount; i++) {
		if (Enemies[i].AliveDead == 1) {
			if (is_PlayerColliding(Enemies[i].enemy_posX, Enemies[i].enemy_posY, 27.5f,
				*objPositionX, *objPositionY, 50.f) && player.damageCooldown <= 0.f) {


				player.health -= 1;
				player.damageCooldown = 1.0f;
			}
			else
				continue;
		}

	}
	snprintf(health, 4, "%d", player.health);
	CP_Settings_TextSize(40.0f);
	CP_Settings_Fill(color_red);
	CP_Font_DrawTextBox(health, 10.f, 700.0f, 50.0f);
	player.damageCooldown -= CP_System_GetDt();
}
