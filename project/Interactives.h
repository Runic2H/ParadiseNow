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

void render_Chest(float posX, float posY, float diameter);
