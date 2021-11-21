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
                Projectiles[i].Mouse_Position.x = CP_Input_GetMouseX();
                Projectiles[i].Mouse_Position.y = CP_Input_GetMouseY();
                Projectiles[i].isActive = 1;
                Projectiles[i].Point.x = PositionX;
                Projectiles[i].Point.y = PositionY;
                Projectiles[i].Subtract = CP_Vector_Subtract(Projectiles[i].Mouse_Position, Projectiles[i].Point);
                Projectiles[i].Normalize = CP_Vector_Normalize(Projectiles[i].Subtract);
                Projectiles[i].Velocity.x = Projectiles[i].Normalize.x * 250;
                Projectiles[i].Velocity.y = Projectiles[i].Normalize.y * 250;
                *Cooldown = 0.20f;
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




            if (Projectiles[i].Point.x > CP_System_GetWindowWidth() || Projectiles[i].Point.x < 0 ||
                Projectiles[i].Point.y > CP_System_GetWindowHeight() || Projectiles[i].Point.y < 0)
            {
                Projectiles[i].isActive = 0;
                continue;
            }


        }

    }

}