/*---------------------------------------------------------
 * file:	projectiles.c

 * author:	ABDUL HADI


 * email:	abdulhadi.b@digipen.edu

 * brief:	This file contains functions related to the
 *          projectile mechanic of the game. The functions
 *			will initialize, shoot and render the
 *			Projectiles


 * Copyright © 2021 DigiPen, All rights reserved.
* ---------------------------------------------------------*/

#include "macros.h"

CP_Sound woosh = NULL;

/*-------------------------FUNCTION HEADER-----------------------*//*
function:	InitProjectiles()

author:	    Abdul Hadi

brief:      InitProjectiles will initialize all the projcetiles with
            an active status of 0

return:     void
*//*---------------------------------------------------------------*/
void InitProjectiles() {
    for (int i = 0; i < MAX_PROJECTILE; i++) {
        Projectiles[i].isActive = 0;
    }
    //sound init
    woosh = CP_Sound_LoadMusic("./Sounds/projectile_woosh.wav");
}

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
void Shoot(float PositionX, float PositionY, float* Cooldown)
{
    

    if (CP_Input_MouseDown(MOUSE_BUTTON_1) && *Cooldown <= 0) {
        for (int i = 0; i < MAX_PROJECTILE; i++) {
            if (Projectiles[i].isActive == 1)
                continue;
            else {
               for (int k = 0; k < player.multishot; k++) {
                   if (k == 0) {
                       Projectiles[i + k].Mouse_Position.x = CP_Input_GetMouseX();
                       Projectiles[i + k].Mouse_Position.y = CP_Input_GetMouseY();
                       Projectiles[i + k].isActive = 1;
                       Projectiles[i + k].Point.x = PositionX;
                       Projectiles[i + k].Point.y = PositionY;
                       Projectiles[i + k].Subtract = CP_Vector_Subtract(Projectiles[i].Mouse_Position, Projectiles[i].Point);
                       Projectiles[i + k].Normalize = CP_Vector_Normalize(Projectiles[i].Subtract);
                       Projectiles[i + k].Velocity.x = Projectiles[i].Normalize.x * 250;
                       Projectiles[i + k].Velocity.y = Projectiles[i].Normalize.y * 250;
                       *Cooldown = 0.20f;
                   }
                   if (k % 2 != 0) { //odd number
                       Rotation = CP_Matrix_Rotate(-(5.f) * ((float)(k+1)/2));
                       Projectiles[i + k].Mouse_Position.x = CP_Input_GetMouseX();
                       Projectiles[i + k].Mouse_Position.y = CP_Input_GetMouseY();
                       Projectiles[i + k].isActive = 1;
                       Projectiles[i + k].Point.x = PositionX;
                       Projectiles[i + k].Point.y = PositionY;
                       Projectiles[i + k].Subtract = CP_Vector_Subtract(Projectiles[i+k].Mouse_Position, Projectiles[i+k].Point);
                       Projectiles[i + k].Subtract = CP_Vector_MatrixMultiply(Rotation, Projectiles[i + k].Subtract);
                       Projectiles[i + k].Normalize = CP_Vector_Normalize(Projectiles[i+k].Subtract);
                       Projectiles[i + k].Velocity.x = Projectiles[i+k].Normalize.x * 250;
                       Projectiles[i + k].Velocity.y = Projectiles[i+k].Normalize.y * 250;
                       *Cooldown = 0.20f;

                   }
                   if (k % 2 == 0) { //even number
                       Rotation = CP_Matrix_Rotate((5.f) * ((float)(k / 2)));
                       Projectiles[i + k].Mouse_Position.x = CP_Input_GetMouseX();
                       Projectiles[i + k].Mouse_Position.y = CP_Input_GetMouseY();
                       Projectiles[i + k].isActive = 1;
                       Projectiles[i + k].Point.x = PositionX;
                       Projectiles[i + k].Point.y = PositionY;
                       Projectiles[i + k].Subtract = CP_Vector_Subtract(Projectiles[i+k].Mouse_Position, Projectiles[i+k].Point);
                       Projectiles[i + k].Subtract = CP_Vector_MatrixMultiply(Rotation, Projectiles[i + k].Subtract);
                       Projectiles[i + k].Normalize = CP_Vector_Normalize(Projectiles[i+k].Subtract);
                       Projectiles[i + k].Velocity.x = Projectiles[i+k].Normalize.x * 250;
                       Projectiles[i + k].Velocity.y = Projectiles[i+k].Normalize.y * 250;
                       *Cooldown = 0.20f;

                   }

                   //play sound of projectile
                   CP_Sound_Play(woosh);
                }
                break;
            }




        }
    }




}

/*-------------------------FUNCTION HEADER-----------------------*//*
function:	DrawProjectile(CP_Image projectileZ)

author:	    Abdul Hadi

brief:      DrawProjectile will render all the active projectiles each
            frame. If the projectile position exceeds the window height
            or width, it ill be cleared and changed to inactive.

return:     void
*//*---------------------------------------------------------------*/
void DrawProjectile(CP_Image projectileZ) {
    for (int i = 0; i < MAX_PROJECTILE; i++) {

        if (Projectiles[i].isActive == 1) {
            //CP_Graphics_DrawCircle(Projectiles[i].Point.x, Projectiles[i].Point.y, 10.0);
            CP_Image_Draw(projectileZ, Projectiles[i].Point.x, Projectiles[i].Point.y, 10.0f, 10.0f, 255);
            Projectiles[i].Point.x += (Projectiles[i].Velocity.x * CP_System_GetDt());
            Projectiles[i].Point.y += (Projectiles[i].Velocity.y * CP_System_GetDt());




            if (Projectiles[i].Point.x > s_windowWidth || Projectiles[i].Point.x < 0 ||
                Projectiles[i].Point.y > s_windowHeight || Projectiles[i].Point.y < 0)
            {
                Projectiles[i].isActive = 0;
                continue;
            }
        }

    }

}