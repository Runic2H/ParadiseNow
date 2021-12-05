/* Header file for Collision */
/*---------------------------------------------------------
 * file:	collision.h
 *
 * author:	ELTON TEO ZHE WEI
			ABDUL HADI

 * email:	e.teo@digipen.edu
			abdulhadi.b@digipen.edu
*
 * brief:	This file contains all functions declarations for
 *			the collision.c file


 * Copyright © 2021 DigiPen, All rights reserved.
* ---------------------------------------------------------*/


/*-------------------------FUNCTION HEADER-----------------------*//*
function:	is_ChestColliding

author:		Elton Teo

brief:		This function checks for collision between chest and
			character

return:		int 1 or 0
*//*---------------------------------------------------------------*/
int is_ChestColliding(float chestX, float chestY, float chestSize, float playerX, float playerY, float playerSize);

/*-------------------------FUNCTION HEADER-----------------------*//*
function:	is_ProjectileColliding

author:		Elton Teo

brief:		This function checks for collision between projectiles
			and enemies

return:		int 1 or 0
*//*---------------------------------------------------------------*/
int is_ProjectileColliding(float enemyX, float enemyY, float enemySize, float projX, float projY, float projSize);

/*-------------------------FUNCTION HEADER-----------------------*//*
function:	is_PlayerColliding

author:		Abdul Hadi

brief:		This function checks for collision between enemy and the
			player

return:		int 1 or 0
*//*---------------------------------------------------------------*/
int is_PlayerColliding(float enemyX, float enemyY, float enemySize, float playerX, float playerY, float playerSize);

/*-------------------------FUNCTION HEADER-----------------------*//*
function:	is_BorderColliding

author:		Elton Teo

brief:		This function checks for collision between the border and
			the player

return:		int 1 or 0
*//*---------------------------------------------------------------*/
int is_BorderColliding(float playerX, float playerY, float windowWidth, float windowHeight);

