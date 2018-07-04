#include"GlobalData.h"

//Update end timer
void UpdateTimers(Enemy* arrE) {
	for (int i = 0; i < NUM_ENEMIES; i++){
		if (!arrE[i].dead) {
			time(&arrE[i].timer.end);
		}
	}
	time(&SpawnTimer.end);
}

//See where it will move next
void Move_Enemy(Player p,Enemy &e,int **map) {
	int iniX = e.pos.x;
	int iniY = e.pos.y;
	if (p.pos.y != e.pos.y||p.pos.x != e.pos.x) {
		if (p.pos.y > e.pos.y) {
			e.pos.y += e.movment_diff;
			e.direction = DOWN;
		}else
		if (p.pos.y < e.pos.y) {
			e.pos.y -= e.movment_diff;
			e.direction = UP;
		}else
		if (p.pos.x > e.pos.x) {
			e.pos.x += e.movment_diff;
			e.direction = RIGHT;
		}else
		if (p.pos.x < e.pos.x) {
			e.pos.x -= e.movment_diff;
			e.direction = LEFT;
		}
		if (!Check_LimitsEnemy(e.pos,map)) {
			e.pos.x = iniX;
			e.pos.y = iniY;
			return;
		}
		DrawSquare(map, iniX, iniY);
	}

}

//Check if enemy should move
bool CheckMove(Enemy &e) {
	if (difftime(e.timer.end, e.timer.start) > MOVETIME) {
		time(&e.timer.start);
		return true;
	}
	return false;
}

bool CheckSpawn() {
	if(difftime(SpawnTimer.end, SpawnTimer.start)>SPAWN_TIME) {
		time(&SpawnTimer.start);
		return true;
	}
	return false;
}

void Move_All_Enemies(Player p,Enemy*arrE,int**map) {
	for (int i = 0; i < NUM_ENEMIES; i++) {
		if (!arrE[i].dead && CheckMove(arrE[i])) {
			Move_Enemy(p, arrE[i],map);
		}
		
	}
}

void Change_Sprite_Enemy(Enemy &e) {
	switch (e.direction) {
	case UP:
		e.sprite[0][0] = char(187); e.sprite[0][1] = char(201);
		e.sprite[1][0] = char(185); e.sprite[1][1] = char(204);
		break;
	case LEFT:
		e.sprite[0][0] = char(200); e.sprite[0][1] = char(202);
		e.sprite[1][0] = char(201); e.sprite[1][1] = char(203);
		break;
	case RIGHT:
		e.sprite[0][0] = char(202); e.sprite[0][1] = char(188);
		e.sprite[1][0] = char(203); e.sprite[1][1] = char(187);
		break;
	case DOWN:
		e.sprite[0][0] = char(185); e.sprite[0][1] = char(204);
		e.sprite[1][0] = char(188); e.sprite[1][1] = char(200);
		break;
	}
}

//Draws a Single Enemy
void DrawEnemy(Enemy e) {
	Change_Color(WHITE);
	for (int j = 0; j < 2; j++) {
		Move_Cursor(e.pos.x, e.pos.y + j);
		cout << e.sprite[j][0] << e.sprite[j][1];
	}
}

//Draws all enemies
void Draw_Enemies(Enemy *e) {
	for (int i = 0; i < NUM_ENEMIES; i++) {
		if (e[i].dead) {
			continue;
		}
		Change_Sprite_Enemy(e[i]);
		DrawEnemy(e[i]);
	}
}

int CountAlive(Enemy* arrE) {
	int cont = 0;
	for (int i = 0; i < NUM_ENEMIES; i++) {
		if (!arrE[i].dead) {
			cont++;
		}
	}
	return cont;
}

void Spawn_Enemy(Enemy*e,int**map) {
	if (CountAlive(e) == NUM_ENEMIES||!CheckSpawn()) {
		return;
	}
	int size = 0;
	Position*p = Search_Map(-1, map, size);
	for (int j = 0; j < size; j++) {
		for (int i = 0; i < NUM_ENEMIES; i++) {
			if (!e[i].dead) {
				continue;
			}
			e[i].dead = false;
			e[i].pos.x = p[j].x;
			e[i].pos.y = p[j].y;
			time(&e[i].timer.start);
			time(&e[i].timer.end);
			break;
		}
	}	
}