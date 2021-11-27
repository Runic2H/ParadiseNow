/* Header file for Collision */

int is_ChestColliding(float chestX, float chestY, float chestSize, float playerX, float playerY, float playerSize);

int is_ProjectileColliding(float enemyX, float enemyY, float enemySize, float projX, float projY, float projSize);

int is_CharacterColliding(float enemyX, float enemyY, float enemySize, float playerX, float playerY, float playerSize);