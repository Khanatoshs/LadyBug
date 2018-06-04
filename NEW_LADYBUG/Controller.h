#include"Enemy.h"
#include"Player.h"

//Controller Function
void controller(Player &p, Enemy*ArrEnem) {
	while (true) {
		Console::Clear();
		Draw_Player(p);
		if (_kbhit()) {
			char key = getch();
			if (key == char(27)) {
				break;
			}
			int direction = KeyToDirection(key);
			if (direction) {
				p.direction = direction;
				if (!Move_Player(p)) {
					continue;
				}
			}
			else {
				continue;
			}
		}
		Sleep(10);
	}
}