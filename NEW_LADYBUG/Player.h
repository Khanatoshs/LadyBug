#include"GlobalData.h"



bool Move_Player(Player &p) {
	int iniX = p.pos.x;
	int iniY = p.pos.y;
	switch (p.direction) {
	case UP:
		p.pos.y-=p.movment_diff;
		break;
	case LEFT:
		p.pos.x -= p.movment_diff;
		break;
	case RIGHT:
		p.pos.x += p.movment_diff;
		break;
	case DOWN:
		p.pos.y += p.movment_diff;
		break;
	default:return false;
	}
	if (!Check_Limits(p.pos)) {
		p.pos.x = iniX;
		p.pos.y = iniY;
		return false;
	}
	return true;
}

//change char based on direction
void Change_Sprite(Player &p) {
	switch (p.direction) {
	case UP:
		p.sprite[0][0] = char(191); p.sprite[0][1] = char(218);
		p.sprite[1][0] = char(200); p.sprite[1][1] = char(188);
		break;
	case LEFT:
		p.sprite[0][0] = char(192); p.sprite[0][1] = char(187);
		p.sprite[1][0] = char(218); p.sprite[1][1] = char(188);
		break;
	case RIGHT:
		p.sprite[0][0] = char(201); p.sprite[0][1] = char(217);
		p.sprite[1][0] = char(200); p.sprite[1][1] = char(191);
		break;
	case DOWN:
		p.sprite[0][0] = char(201); p.sprite[0][1] = char(187);
		p.sprite[1][0] = char(217); p.sprite[1][1] = char(192);
		break;
	}
}

//Draw Player
void Draw_Player(Player &p) {
	
	Change_Sprite(p);
	for (int i = 0; i < 2; i++) {
		Move_Cursor(p.pos.x, p.pos.y+i);
		for (int j = 0; j < 2; j++) {
			cout << p.sprite[i][j];
		}
	}
}