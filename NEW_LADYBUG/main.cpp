#include"Controller.h"


int main() {
	
	Enemy* enemyArray=new Enemy[NUM_ENEMIES];
	Player p;
	p.pos.x = P_INI_POS_X;
	p.pos.y = P_INI_POS_Y;
	p.sprite = new char*[2];
	for (int i = 0; i < 2; i++) {
		p.sprite[i] = new char[2];
	}
	Cursor_visible();
	controller(p,enemyArray);
	
	
}