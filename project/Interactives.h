/* Header file for Interactives */

struct upgrades {
	int alive;
	float posX;
	float posY;
	float diameter;
	int skill;
};

void chest_init(void);

void chest_spawn(void);

void chest_collision(float playerX, float playerY);

void render_Chest(float posX, float posY, float diameter);
