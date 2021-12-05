/* Header file for character */
/*---------------------------------------------------------
 * file:	character.h
 *
 * author:	ELTON TEO ZHE WEI
			ABDUL HADI

 * email:	e.teo@digipen.edu
			abdulhadi.b@digipen.edu
*
 * brief:	This file contains all function declarations for
 *			character.c as well as structs for the player
 *			object


 * Copyright © 2021 DigiPen, All rights reserved.
* ---------------------------------------------------------*/

struct c_CharacterStats
{
	int alive;
	int health;
	int MAXhealth;
	int	attack;
	int gold;
	int score;
	int multishot;
	float positionX;
	float positionY;
	float diameter;
	float damageCooldown;
	int shield;
	float damageTaken;
};

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
void c_CharacterWASD(void);

/*-------------------------FUNCTION HEADER-----------------------*//*
function:	c_CharacterMouse()

author:		Elton Teo

brief:		This function calculates the velocity using the resultant
			vector from player and mouse to calculate the speed. It
			also had border collision to prevent the player from
			going out of bounds

return:		-
*//*---------------------------------------------------------------*/
void c_CharacterMouse(void);

/*-------------------------FUNCTION HEADER-----------------------*//*
function:	c_renderPlayer()

author:		Richmond Choo

brief:		This function renders the player model and effects for
			a certain skill if unlocked during gameplay

return:		-
*//*---------------------------------------------------------------*/
void c_renderPlayer(CP_Image mage, CP_Image energyshield);

/*-------------------------FUNCTION HEADER-----------------------*//*
function:	c_CharacterInit()

author:		Elton Teo

brief:		This function initialises all starting values for the
			character struct object player. It also initialises the
			sounds for player damage

return:		-
*//*---------------------------------------------------------------*/
void c_CharacterInit(void);

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
void playerCollide(float objPositionX, float objPositionY);

/*-------------------------FUNCTION HEADER-----------------------*//*
function:	c_renderHUD

author:		Elton Teo

brief:		This function renders the HUD and all character elements
			such as damage taken, certain upgrades. HUD includes the
			health, health bar and gold as well as the score

return:		-
*//*---------------------------------------------------------------*/
void c_renderHUD(CP_Image warning);

