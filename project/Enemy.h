/* Header file for macros */


/*
1. diff speed for each enemies

2. diff enemy mech

3. collision check
- calc.bounding box of 2 obj
-

-check if collide character / player

check enemy, projectileand character collisions, that returns True or False

- character invulnerable for 2 secs after collision w enemy
*/

#define color_red CP_Color_Create(255, 0, 0, 255)

float outerlimit_rand(float lower, float upper, float window_heightOrWidth);

void enemy_vector(float player_x, float player_y, float* ex, float* ey, float speed);

void enemy_init_posXY();

void enemy_draw(float player_x, float player_y, CP_Image imageoverlay);

void stationary_plants(float player_x, float player_y, float stationary_x, float stationary_y, CP_Image imageoverlay);