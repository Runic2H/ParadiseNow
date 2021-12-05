/*---------------------------------------------------------
 * file:	character.c
 * 
 * author:	ELTON TEO ZHE WEI
			LOUIS MINEO @ LINN MIN HTOO
			ABDUL HADI

 * email:	e.teo@digipen.edu
			louismineo.l@digipen.edu
			abdulhadi.b@digipen.edu
*
 * brief:	This file contains all functions pertaining to
 *			character movement and the collision for enemies. 
 *			It also contains functions for rendering the
 *			player and the player HUD


 * Copyright © 2021 DigiPen, All rights reserved.
* ---------------------------------------------------------*/

#include "macros.h"

char health[4];
char gold[4];
char max[4];
char score[4];

CP_Sound Character_DMG = NULL;

/*-------------------------FUNCTION HEADER-----------------------*//*
function:	c_CharacterInit()

author:		Elton Teo

brief:		This function initialises all starting values for the
			character struct object player. It also initialises the
			sounds for player damage

return:		-
*//*---------------------------------------------------------------*/
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
	player.damageCooldown = 0.f;
	player.shield = 0;
	player.damageTaken = 0;
	Character_DMG = CP_Sound_LoadMusic("./Sounds/dmg to char.wav");
}

/*-------------------------FUNCTION HEADER-----------------------*//*
function:	c_CharacterWASD()

author:		Elton Teo

brief:		This function calculates the vector velocity for the
			player to move around in an 8 directional movement using
			a rotation matrix to shift the vector by 45*. It also has
			border collision to prevent the player from going out of
			bounds from the game play area.

return:		-
*//*---------------------------------------------------------------*/
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

/*-------------------------FUNCTION HEADER-----------------------*//*
function:	c_CharacterMouse()

author:		Elton Teo

brief:		This function calculates the velocity using the resultant
			vector from player and mouse to calculate the speed. It
			also had border collision to prevent the player from
			going out of bounds

return:		-
*//*---------------------------------------------------------------*/
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
		if (is_BorderColliding(player.positionX, player.positionY, (float)s_windowWidth, (float)s_windowHeight))
		{
			speed = CP_Vector_Zero();
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
		else
		{
			player.positionX += speed.x;
			player.positionY += speed.y;
		}
	}
}

/*-------------------------FUNCTION HEADER-----------------------*//*
function:	playerCollide()

author:		Abdul Hadi
			Louis Mineo

brief:		This function checks the collision between the player and
			every enemy and boss. It reduces the players health if
			collision is detected but only if the player does not
			have a certain chest upgrade. It uses the CP_System_GetDT
			to give the player some form of Iframes before getting hit
			again

return:		-
*//*---------------------------------------------------------------*/
void playerCollide(float objPositionX, float objPositionY) {
	for (int i = 0; i < MAX_ENEMIES; i++) {
		if (Enemies[i].AliveDead == 1) {
			if (is_PlayerColliding(Enemies[i].enemy_posX, Enemies[i].enemy_posY, 27.5f,
				objPositionX, objPositionY, 50.f) && player.damageCooldown <= 0.f) {

				if (player.shield != 1)
				{
					player.health -= 1;
					CP_Sound_Play(Character_DMG);
					player.damageCooldown = .75f;
					player.damageTaken = .75f;
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
					CP_Sound_Play(Character_DMG);
					player.damageCooldown = .5f;
					player.damageTaken = .5f;
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
	player.damageTaken -= CP_System_GetDt();
}

/*-------------------------FUNCTION HEADER-----------------------*//*
function:	c_renderPlayer()

author:		Richmond Choo

brief:		This function renders the player model and effects for
			a certain skill if unlocked during gameplay

return:		-
*//*---------------------------------------------------------------*/
void c_renderPlayer(CP_Image mage, CP_Image energyshield)
{
	if (player.shield == 1) {
		CP_Image_Draw(energyshield, player.positionX, player.positionY, 56, 56, 255);
	}
	CP_Image_Draw(mage, player.positionX, player.positionY, 56, 56, 255);
}

/*-------------------------FUNCTION HEADER-----------------------*//*
function:	c_renderHUD

author:		Elton Teo

brief:		This function renders the HUD and all character elements
			such as damage taken, certain upgrades. HUD includes the
			health, health bar and gold as well as the score

return:		-
*//*---------------------------------------------------------------*/
void c_renderHUD(CP_Image warning)
{
	if (player.shield == 1)
	{
		CP_Settings_TextSize(40.0f);
		CP_Settings_Fill(color_blue);
		CP_Font_DrawTextBox("Energy Shield", 10.f, 580.f, 400.f);
	}

	if (player.health != 0)
	{
		CP_Settings_Fill(color_white);
		float lengthMAX = player.MAXhealth * 10.f;
		//Max Health Bar
		CP_Graphics_DrawRect(10.f, 600.f, lengthMAX, 10);
		if (player.shield == 1)
		{
			CP_Settings_Fill(color_blue);
		}
		else
		{
			CP_Settings_Fill(color_red);
		}
		for (int playerHealth = player.health; playerHealth >= 0; playerHealth--)
		{
			//Current Health Bar
			float length = (float)playerHealth * 10.f;
			CP_Graphics_DrawRect(10.f, 600.f, length, 10);
		}
	}

	snprintf(health, 4, "%d", player.health);
	snprintf(max, 4, "%d", player.MAXhealth);
	CP_Settings_TextSize(40.0f);
	CP_Settings_Fill(color_red);
	CP_Font_DrawTextBox("Health:", 10.f, 650.f, 125.f);
	CP_Font_DrawTextBox(health, 125.f, 650.f, 50.f);
	CP_Font_DrawTextBox("/", 165.f, 650.f, 10.f);
	CP_Font_DrawTextBox(max, 190.f, 650.0f, 50.f);

	if (player.health <= 3)
	{
		CP_Image_Draw(warning, 260.0f, 660.0f, Linear(min_size+80.0f, max_size+80.0f, timerStart / duration),
			Linear(min_size+80.0f, max_size+80.0f, timerStart / duration), 255);
	}

	snprintf(gold, 4, "%d", player.gold);
	CP_Settings_TextSize(40.0f);
	CP_Settings_Fill(color_yellow);
	CP_Font_DrawTextBox("Gold:", 10.f, 700.f, 125.f);
	CP_Font_DrawTextBox(gold, 125.f, 700.f, 150.f);

	snprintf(score, 4, "%d", player.score);
	CP_Settings_TextSize(40.0f);
	CP_Settings_Fill(color_white);
	CP_Font_DrawTextBox("Score:", 10.f, 100.f, 150.f);
	CP_Font_DrawTextBox(score, 125.f, 100.f, 500.f);

	if (player.damageCooldown > 0 && player.damageTaken > 0)
	{
		CP_Settings_TextSize(30.0f);
		CP_Font_DrawText("Argh!", player.positionX, Linear(player.positionY, player.positionY - 25.f, (timerStart / duration)));
	}
}
