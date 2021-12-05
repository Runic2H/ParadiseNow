/* Header file for Projectiles */
/*---------------------------------------------------------
 * file:	projectiles.h

 * author:	ABDUL HADI


 * email:	abdulhadi.b@digipen.edu

 * brief:	This file contains all the functions and
            definitions required for the projectiles


 * Copyright © 2021 DigiPen, All rights reserved.
* ---------------------------------------------------------*/

#define MAX_PROJECTILE 300

typedef struct Projectile {
    CP_Vector Velocity;
    CP_Vector Point;
    CP_Vector Mouse_Position;
    CP_Vector Subtract;
    CP_Vector Normalize;
    int isActive;
    



} Projectile;

CP_Matrix Rotation;

/*-------------------------FUNCTION HEADER-----------------------*//*
function:	InitProjectiles()

author:	    Abdul Hadi

brief:      InitProjectiles will initialize all the projcetiles with
            an active status of 0

return:     void
*//*---------------------------------------------------------------*/
void InitProjectiles();

/*-------------------------FUNCTION HEADER-----------------------*//*
function:	Shoot(float PositionX, float PositionY, float* Cooldown)

author:	    Abdul Hadi

brief:      Shoot will create a projectile at the player mouse position
            if the left mouse button is pressed. It has a cooldown
            of 0.2 seconds.

            If the player has multishot, it will also create projectiles
            with the use of rotation from the main projectile.

return:     void
*//*---------------------------------------------------------------*/
void Shoot(float PositionX, float PositionY, float* Cooldown);

/*-------------------------FUNCTION HEADER-----------------------*//*
function:	DrawProjectile(CP_Image projectileZ)

author:	    Abdul Hadi

brief:      DrawProjectile will render all the active projectiles each
            frame. If the projectile position exceeds the window height
            or width, it ill be cleared and changed to inactive.

return:     void
*//*---------------------------------------------------------------*/
void DrawProjectile(CP_Image Image);

float ShootCooldown;


