/* Header file for Projectiles */
#define MAX_PROJECTILE 300

typedef struct Projectile {
    CP_Vector Velocity;
    CP_Vector Point;
    CP_Vector Mouse_Position;
    CP_Vector Subtract;
    CP_Vector Normalize;
    int isActive;
    



} Projectile;

Projectile Projectiles[MAX_PROJECTILE];
CP_Matrix Rotation;
//int Multishot;

void InitProjectiles();
void Shoot(float PositionX, float PositionY, float* Cooldown);
void DrawProjectile();
float ShootCooldown;

//To be Removed
//CP_Vector Normal_Y;
//CP_Vector UnitX_Left;
//CP_Vector UnitX_Right;

