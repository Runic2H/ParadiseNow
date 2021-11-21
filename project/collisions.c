#include "macros.h"

int is_ChestColliding(float chestX, float chestY, float chestSize, float playerX, float playerY, float playerSize)
{
	return ((playerX >= chestX) && (playerY >= chestY)) && ((playerX + playerSize >= chestX + chestSize)
		&& (playerY + playerSize >= playerY + chestY));
}

//int is_ProjectileColliding(float enemyX, float enemyY, float enemySize, float projX, float projY, float projSize)
//{
//	return ((projX >= enemyX) && (projY >= enemyY)) && ((projX + projSize >= enemyX + enemySize)
//		&& (projY + projSize >= enemyY + enemySize));
//}

int is_ProjectileColliding(float enemyX, float enemyY, float enemySize, float projX, float projY, float projSize)
{
	return (enemyX < projX + projSize) 
		&& ((enemyX + enemySize) > projX) 
		&& (enemyY < (projY + projSize)) 
		&& ((enemyY + enemySize) > projY);
}