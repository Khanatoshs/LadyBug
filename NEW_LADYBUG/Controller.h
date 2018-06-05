#include"Enemy.h"
#include"Player.h"
#include"Map.h"

//Controller Function
void controller(Player &p, Enemy*ArrEnem,int**map) {
	Draw_Map(map);
	while (true) {
		if (_kbhit()) {
			char key = getch();
			if (key == char(27)) {
				break;
			}
			if (key == 'e') {
				Spawn_Enemy(ArrEnem,map);
				continue;
			}
			int direction = KeyToDirection(key);
			if (direction) {
				p.direction = direction;
				Move_All_Enemies(p, ArrEnem,map);
				if (!Move_Player(p,map)) {
					continue;
				}
			}
			else {
				continue;
			}
		}

		Draw_Enemies(ArrEnem);
		Draw_Player(p);
		Sleep(15);
	}
}