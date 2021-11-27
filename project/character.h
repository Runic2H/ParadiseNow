/* Header file for character */

struct c_CharacterStats
{
	int alive;
	int health;
	int MAXhealth;
	int	attack;
	int gold;
	int exp;
	int multishot;
	float positionX;
	float positionY;
	float diameter;
	float damageCooldown;
	int shield;
};

void c_CharacterWASD(void);

void c_CharacterMouse(void);

void c_renderPlayer(CP_Image mage);

void c_CharacterInit(void);

void playerCollide(float objPositionX, float objPositionY);

void c_renderHUD(void);


