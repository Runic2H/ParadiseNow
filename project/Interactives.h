/* Header file for Interactives */

struct upgrades {
	int alive;
	float posX;
	float posY;
	float diameter;
	int skill;
	float cooldown;
};

void chest_init(void);

void chest_SpawnCheck(void);

void render_Chest(float posX, float posY, float diameter, CP_Image chestZ);

void add_skill(int skillno);

void render_skill(int skillno);
