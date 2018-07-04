#include"Enemy.h"
#include"Player.h"
#include"Map.h"

//Controller Function
void controller(Player &p, Enemy*ArrEnem,int**map) {
	Draw_Map(map);
	InitSpawnTimer();
	while (true) {
		UpdateTimers(ArrEnem);
		if (_kbhit()) {
			char key = getch();
			if (key == char(27)) {
				break;
			}
			int direction = KeyToDirection(key);
			if (direction) {
				p.direction = direction;
				
				if (!Move_Player(p,map)) {
					continue;
				}
			}
			else {
				continue;
			}
		}
		GetItem(map, p);
		Spawn_Enemy(ArrEnem, map);
		Move_All_Enemies(p, ArrEnem, map);
		Draw_Enemies(ArrEnem);
		Draw_Player(p);
		DrawPoints(p);
		//Sleep(15);
	}
}