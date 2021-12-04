#include "macros.h"

int is_ProjectileColliding(float enemyX, float enemyY, float enemySize, float projX, float projY, float projSize)
{
	return (enemyX < projX + projSize) 
		&& ((enemyX + enemySize) > projX) 
		&& (enemyY < (projY + projSize)) 
		&& ((enemyY + enemySize) > projY);
}

int is_ChestColliding(float chestX, float chestY, float chestWidth, float playerX, float playerY, float playerSize)
{
	return (playerX < (chestX + chestWidth))
		&& ((playerX + playerSize) > chestX)
		&& (playerY < (chestY + chestWidth))
		&& ((playerY + playerSize) > chestY);
}

int (is_PlayerColliding)(float enemyX, float enemyY, float enemySize, float playerX, float playerY, float playerSize) {
	return (enemyX < playerX + playerSize)
		&& ((enemyX + enemySize) > playerX)
		&& (enemyY < (playerY + playerSize))
		&& ((enemyY + enemySize) > playerY);
}

int is_BorderColliding(float playerX, float playerY, float windowWidth, float windowHeight)
{
	return (playerX > windowWidth) 
		|| (playerY > windowHeight) 
		|| (playerX < 0.f) 
		|| (playerY < 0.f);
}