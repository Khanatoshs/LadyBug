#include"Controller.h"


int main() {
	
	Enemy* enemyArray=new Enemy[NUM_ENEMIES];
	Player p;
	int**map = new int*[MAP_ROW];

	InitEnemies(enemyArray);
	InitPlayer(p);
	InitMap(map);
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