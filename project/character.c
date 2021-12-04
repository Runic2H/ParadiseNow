#include "macros.h"

char health[4];
char gold[4];
char max[4];
char score[4];

void c_CharacterInit(void)
{
	player.alive = TRUE;
	player.MAXhealth = 10;
	player.positionX = s_windowWidth/2.f;
	player.positionY = s_windowHeight/2.f;
	player.diameter = c_defaultSize;
	player.score = 0;
	player.gold = 0;
	player.attack = 1;
	player.health = player.MAXhealth;
	player.multishot = 1;
	player.damageCooldown = 1.0f;
	player.shield = 0;
}

void c_CharacterWASD()
{
	CP_Vector direction = { 10,10 };
	CP_Vector velocity = CP_Vector_Scale(CP_Vector_Normalize(direction), 400.f * CP_System_GetDt());
	CP_Matrix rotate = CP_Matrix_Rotate(45.0f);
	CP_Vector movement = CP_Vector_MatrixMultiply(rotate, velocity);
	if (is_BorderColliding(player.positionX, player.positionY, (float)s_windowWidth, (float)s_windowHeight))
	{
		velocity = CP_Vector_Zero();
		movement = CP_Vector_Zero();
		if (player.positionX < 0.f)
		{
			player.positionX += 1.f;
		}
		else if (player.positionX > s_windowWidth)
		{
			player.positionX -= 1.f;
		}
		else if (player.positionY < 0.f)
		{
			player.positionY += 1.f;
		}
		else if (player.positionY > s_windowHeight)
		{
			player.positionY -= 1.f;
		}
	}
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
		player.positionX -= velocity.x;
	}
	if (CP_Input_KeyDown(KEY_D))
	{
		player.positionX += velocity.x;
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
		//To look around
	}
	else
	{
		player.positionX += speed.x;
		player.positionY += speed.y;
	}
}

void c_renderPlayer(CP_Image mage, CP_Image energyshield)
{
	//CP_Settings_Fill(color_white);
	if (player.shield == 1) {
		CP_Image_Draw(energyshield, player.positionX, player.positionY, 56, 56, 255);
	}
		CP_Image_Draw(mage, player.positionX, player.positionY, 56, 56, 255);
}

void playerCollide(float objPositionX, float objPositionY) {
	for (int i = 0; i < MAX_ENEMIES; i++) {
		if (Enemies[i].AliveDead == 1) {
			if (is_PlayerColliding(Enemies[i].enemy_posX, Enemies[i].enemy_posY, 27.5f,
				objPositionX, objPositionY, 50.f) && player.damageCooldown <= 0.f) {

				if (player.shield != 1)
				{
					player.health -= 1;
					player.damageCooldown = .5f;
				}
				else
				{
					player.shield = 0;
					player.damageCooldown = 2.0f;
				}
			}
			else
				continue;
		}
	}
	//Collision w boss
	for (int i = 0; i < MAX_BOSS; i++) {
		if (Boss[i].AliveDead == 1) {
			if (is_PlayerColliding(Boss[i].boss_posX, Boss[i].boss_posY, 27.5f,
				objPositionX, objPositionY, 50.f) && player.damageCooldown <= 0.f) {

				if (player.shield != 1)
				{
					player.health -= 2;
					player.damageCooldown = .5f;
				}
				else
				{
					player.shield = 0;
					player.damageCooldown = 2.0f;
				}
			}
			else
				continue;
		}
	}

	player.damageCooldown -= CP_System_GetDt();
}

void c_renderHUD(void)
{

	if (player.shield == 1)
	{
		CP_Settings_TextSize(40.0f);
		CP_Settings_Fill(color_blue);
		CP_Font_DrawTextBox("Energy Shield", 10.f, 600.f, 400.f);
	}

	snprintf(health, 4, "%d", player.health);
	snprintf(max, 4, "%d", player.MAXhealth);
	CP_Settings_TextSize(40.0f);
	CP_Settings_Fill(color_red);
	CP_Font_DrawTextBox("Health:", 10.f, 650.f, 125.f);
	CP_Font_DrawTextBox(health, 125.f, 650.f, 50.f);
	CP_Font_DrawTextBox("/", 165.f, 650.f, 10.f);
	CP_Font_DrawTextBox(max, 190.f, 650.0f, 50.f);

	snprintf(gold, 4, "%d", player.gold);
	CP_Settings_TextSize(40.0f);
	CP_Settings_Fill(color_yellow);
	CP_Font_DrawTextBox("Gold:", 10.f, 700.f, 125.f);
	CP_Font_DrawTextBox(gold, 125.f, 700.f, 150.f);

	snprintf(score, 4, "%d", player.score);
	CP_Settings_TextSize(40.0f);
	CP_Settings_Fill(color_white);
	CP_Font_DrawTextBox("Score:", 10.f, 100.f, 150.f);
	CP_Font_DrawTextBox(score, 125.f, 100.f, 1000.f);
}

