#include "macros.h"


void InitProjectiles() {
    for (int i = 0; i < MAX_PROJECTILE; i++) {
        Projectiles[i].isActive = 0;
    }

}



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
                }
                break;
            }




        }
    }




}

void DrawProjectile() {
    for (int i = 0; i < MAX_PROJECTILE; i++) {

        if (Projectiles[i].isActive == 1) {
            CP_Settings_Fill(color_blue);
            CP_Graphics_DrawCircle(Projectiles[i].Point.x, Projectiles[i].Point.y, 10.0);
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