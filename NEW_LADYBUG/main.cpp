#include"Controller.h"


int main() {
	
	Enemy* enemyArray=new Enemy[NUM_ENEMIES];
	Player p;
	int**map = new int*[MAP_ROW];
	p.pos.x = P_INI_POS_X;
	p.pos.y = P_INI_POS_Y;

	p.sprite = new char*[2];
	for (int i = 0; i < 2; i++) {
		p.sprite[i] = new char[2];
	}
	
	for (int j = 0; j < NUM_ENEMIES; j++) {
		enemyArray[j].pos.x = E_INI_POS_X;
		enemyArray[j].pos.y = E_INI_POS_Y;
		enemyArray[j].sprite = new char*[2];
		for (int i = 0; i < 2; i++) {
			enemyArray[j].sprite[i] = new char[2];
		}
	}
	
	for (int i = 0; i < MAP_ROW; i++) {
		map[i] = new int[MAP_COL];
	}

	Read_Map(map);
	Maximize_Console();
	Cursor_visible();
	controller(p,enemyArray,map);

	for (int i = 0; i < NUM_ENEMIES; i++) {
		delete[] enemyArray[i].sprite;
	}
	delete[] p.sprite;
	delete[] enemyArray;
	for (int i = 0; i < MAP_ROW; i++) {
		delete[] map[i];
	}
	delete[] map;
}