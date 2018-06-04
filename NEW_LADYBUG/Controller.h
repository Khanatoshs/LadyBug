#include"Enemy.h"
#include"Player.h"

//Controller Function
void controller(Player &p, Enemy*ArrEnem) {
	while (true) {
		Console::Clear();
		
		Draw_Enemies(ArrEnem);
		Draw_Player(p);
		if (_kbhit()) {
			char key = getch();
			if (key == char(27)) {
				break;
			}
			if (key == 'e') {
				Spawn_Enemy(ArrEnem);
				continue;
			}
			int direction = KeyToDirection(key);
			if (direction) {
				p.direction = direction;
				Move_All_Enemies(p, ArrEnem);
				if (!Move_Player(p)) {
					continue;
				}
				
			}
			else {
				continue;
			}
		}
		
		Sleep(50);
	}
}