/* Header file for macros */


struct Enemy {
	int health;
	int collisionWproj;
	int ID; // 1, 2, 3, 4, 5
	float enemy_posX;
	float enemy_posY;
	int AliveDead; // enemyAlive 1 or enemyDead 1 0 
	float speed;
};


struct Boss {
	int health;
	int collisionWproj;
	int ID;
	float boss_posX;
	float boss_posY;
	int AliveDead;
	float speed;
};

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

void enemy_draw(float player_x, float player_y, CP_Image imageoverlay, CP_Image bossimage);

void stationary_plants(float player_x, float player_y, float stationary_x, float stationary_y, CP_Image imageoverlay);

void enemy_collision();

void boss_Collision();

void boss_dmg();

void boss_die();

void enemy_deadAlive_update(float player_x, float player_y);

void enemy_TEST_TAKEDMG_update();