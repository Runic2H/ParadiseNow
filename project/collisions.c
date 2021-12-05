/*---------------------------------------------------------
 * file:	collision.c
 *
 * author:	ELTON TEO ZHE WEI
			ABDUL HADI

 * email:	e.teo@digipen.edu
			abdulhadi.b@digipen.edu
*
 * brief:	This file contains all functions pertaining to
 *			various collision functions between different
 *			objects. Included are collision functions for
 *			projectiles, character, chest and border.


 * Copyright © 2021 DigiPen, All rights reserved.
* ---------------------------------------------------------*/

#include "macros.h"


/*-------------------------FUNCTION HEADER-----------------------*//*
function:	is_ProjectileColliding

author:		Elton Teo

brief:		This function checks for collision between projectiles
			and enemies

return:		int 1 or 0
*//*---------------------------------------------------------------*/
int is_ProjectileColliding(float enemyX, float enemyY, float enemySize, float projX, float projY, float projSize)
{
	return (enemyX < projX + projSize) 
		&& ((enemyX + enemySize) > projX) 
		&& (enemyY < (projY + projSize)) 
		&& ((enemyY + enemySize) > projY);
}

/*-------------------------FUNCTION HEADER-----------------------*//*
function:	is_ChestColliding

author:		Elton Teo

brief:		This function checks for collision between chest and
			character

return:		int 1 or 0
*//*---------------------------------------------------------------*/
int is_ChestColliding(float chestX, float chestY, float chestWidth, float playerX, float playerY, float playerSize)
{
	return (playerX < (chestX + chestWidth))
		&& ((playerX + playerSize) > chestX)
		&& (playerY < (chestY + chestWidth))
		&& ((playerY + playerSize) > chestY);
}

/*-------------------------FUNCTION HEADER-----------------------*//*
function:	is_PlayerColliding

author:		Abdul Hadi

brief:		This function checks for collision between enemy and the
			player

return:		int 1 or 0
*//*---------------------------------------------------------------*/
int is_PlayerColliding(float enemyX, float enemyY, float enemySize, float playerX, float playerY, float playerSize) {
	return (enemyX < playerX + playerSize)
		&& ((enemyX + enemySize) > playerX)
		&& (enemyY < (playerY + playerSize))
		&& ((enemyY + enemySize) > playerY);
}

/*-------------------------FUNCTION HEADER-----------------------*//*
function:	is_BorderColliding

author:		Elton Teo

brief:		This function checks for collision between the border and
			the player

return:		int 1 or 0
*//*---------------------------------------------------------------*/
int is_BorderColliding(float playerX, float playerY, float windowWidth, float windowHeight)
{
	return (playerX > windowWidth) 
		|| (playerY > windowHeight) 
		|| (playerX < 0.f) 
		|| (playerY < 0.f);
}