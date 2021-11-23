/* Header file for character */

struct c_CharacterStats
{
	int health;
	int	attack;
	int gold;
	int exp;
	float positionX;
	float positionY;
	float diameter;
};

void c_CharacterWASD(float *objPositionX, float *objPositionY);

void c_CharacterMouse(float* objPositionX, float* objPositionY);

void renderPlayer(float* positionX, float* positionY, CP_Image mage);

void c_CharacterInit();


