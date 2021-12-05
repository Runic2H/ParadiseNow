/* Header file for Interactives */
/*---------------------------------------------------------
 * file:	Interactives.h
 *
 * author:	ELTON TEO ZHE WEI

 * email:	e.teo@digipen.edu
*
 * brief:	This file contains all function declarations for
 *			Interactives.c. It also contains the struct for
 *			chest objects


 * Copyright © 2021 DigiPen, All rights reserved.
* ---------------------------------------------------------*/

struct upgrades {
	int alive;
	float posX;
	float posY;
	float diameter;
	int skill;
	float cooldown;
};

/*-------------------------FUNCTION HEADER-----------------------*//*
function:	chest_init

author:		Elton Teo

brief:		This function initialises all values needed for the chest
			object

return:		-
*//*---------------------------------------------------------------*/
void chest_init(void);

/*-------------------------FUNCTION HEADER-----------------------*//*
function:	chest_SpawnCheck

author:		Elton Teo

brief:		This function checks the collision between the player and
			the chest. If collided and the player has met the gold
			requirement to purchase, It will call the add_skill
			function to grant the player the acquired skill and reduce
			his gold it will then set the chest.alive to false. Not
			opening the chest after 45 seconds will also result in
			the chest despawning and chest.alive be set to false. A
			cooldown is also used to control the spawnrate of chests

return:		-
*//*---------------------------------------------------------------*/
void chest_SpawnCheck(void);

/*-------------------------FUNCTION HEADER-----------------------*//*
function:	render_Chest

author:		Elton Teo

brief:		This function renders the chest image as well as relevant
			text to the player upon collision

return:		-
*//*---------------------------------------------------------------*/
void render_Chest(float posX, float posY, float diameter, CP_Image chestZ);

/*-------------------------FUNCTION HEADER-----------------------*//*
function:	add_skill

author:		Elton Teo

brief:		This function uses a switch case and a number parsed by
			a random number gen to upgrade the player's stats or
			skills according to the number generated

return:		-
*//*---------------------------------------------------------------*/
void add_skill(int skillno);

/*-------------------------FUNCTION HEADER-----------------------*//*
function:	render_skill

author:		Elton Teo

brief:		This function renders the easein functions to indicate
			what skills the player has acquired via floating text

return:		-
*//*---------------------------------------------------------------*/
void render_skill(int skillno);
