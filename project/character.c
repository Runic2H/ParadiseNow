#include "macros.h"

void c_CharacterInit(void)
{
	player.alive = TRUE;
	player.dmg_taken = FALSE;
	player.positionX = 200.f;
	player.positionY = 200.f;
	player.diameter = c_defaultSize;
	player.exp = 0;
	player.gold = 0;
	player.attack = 1;
	player.health = 10;
	player.multishot = 1;
}

void c_CharacterWASD()
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
				player.positionX += movement.x / 2;
				player.positionY -= movement.y / 2;
			}
			else if (CP_Input_KeyDown(KEY_D))
			{
				player.positionX -= movement.x / 2;
				player.positionY -= movement.y / 2;
			}
			else
			{
				player.positionY -= velocity.y;
			}
		}
		if (CP_Input_KeyDown(KEY_S))
		{
			if (CP_Input_KeyDown(KEY_A))
			{
				player.positionX -= movement.x / 2;
				player.positionY += movement.y / 2;
			}
			else if (CP_Input_KeyDown(KEY_D))
			{
				player.positionX -= movement.x / 2;
				player.positionY += movement.y / 2;
			}
			else
			{
				player.positionY += velocity.y;
			}
		}
		if (CP_Input_KeyDown(KEY_A))
		{
			player.positionX-= velocity.x;
		}
		if (CP_Input_KeyDown(KEY_D))
		{
			player.positionX += velocity.x;
		}
	}
}

void c_CharacterMouse()
{
	CP_Vector playerVector = CP_Vector_Set(player.positionX, player.positionY);
	CP_Vector mouseVector = CP_Vector_Set(CP_Input_GetMouseX(), CP_Input_GetMouseY());
	CP_Vector directionVector = CP_Vector_Subtract(mouseVector, playerVector);
	CP_Vector speed = CP_Vector_Scale(CP_Vector_Normalize(directionVector), 300.f * CP_System_GetDt());
	if (CP_Input_MouseDown(MOUSE_BUTTON_2))
	{
		//To implement looking around
	}
	else
	{
		player.positionX += speed.x;
		player.positionY += speed.y;
	}
}

void c_renderPlayer(CP_Image mage)
{
	CP_Settings_Fill(color_white);
	CP_Image_Draw(mage, player.positionX, player.positionY, 100, 100, 255);
}

void c_playerCollision(void)
{
	for (int i = 0; i < enemycount; i++)
	{
		if (is_CharacterColliding(Enemies[i].enemy_posX, Enemies[i].enemy_posY, Enemies[i].diameter, player.positionX, player.positionY, player.diameter))
		{
			player.dmg_taken = 1;
			if (player.dmg_taken == 1)
			{
				player.health -= 1;
				player.dmg_taken = 0;
				printf("%d", player.health);
			}
		}
	}
}

void damagePlayer(void)
{
}
