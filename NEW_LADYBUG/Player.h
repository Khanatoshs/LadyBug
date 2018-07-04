#include"GlobalData.h"

bool MoveTurners(Player p,int**map) {
	if(map[p.pos.y][p.pos.x]==2){
		int iniI, iniJ;
		bool isGood = false;
		if (map[p.pos.y - 2][p.pos.x] == 3&&(p.direction==LEFT||p.direction==RIGHT)) {
			iniI = p.pos.y - 4;
			iniJ = p.pos.x - 2;
			isGood = true;
		}
		else if (map[p.pos.y + 2][p.pos.x] == 3 && (p.direction == LEFT || p.direction == RIGHT)) {
			iniI = p.pos.y;
			iniJ = p.pos.x-2;
			isGood = true;
		}
		else if (map[p.pos.y][p.pos.x+2] == 3 && (p.direction == UP || p.direction == DOWN)) {
			iniI = p.pos.y-2;
			iniJ = p.pos.x;
			isGood = true;
		}
		else if (map[p.pos.y][p.pos.x-2] == 3 && (p.direction == UP || p.direction == DOWN)) {
			iniI = p.pos.y-2;
			iniJ = p.pos.x-4;
			isGood = true;
		}
		if (!isGood) {
			return false;
		}
		//Transpose that part of the map
		int aux[6][6];
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 6; j++) {
				aux[i][j] = map[iniI+i][iniJ+j];
			}
		}
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 6; j++) {
				map[iniI + i][iniJ + j]=aux[j][i];
			}
		}
		for (int i = 0; i < 6; i+=2) {
			for (int j = 0; j < 6; j+=2) {
				DrawSquare(map, iniJ+j, iniI+i);
			}
		}
		return true;
	}
	return true;
}

bool Move_Player(Player &p,int**map) {
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
	if (!MoveTurners(p, map)||!Check_LimitsPlayer(p.pos,map)) {
		p.pos.x = iniX;
		p.pos.y = iniY;
		return false;
	}
	
	Hide_Trail(iniX, iniY);
	return true;
}

//change char based on direction
void Change_Sprite_Player(Player &p) {
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
	
	Change_Sprite_Player(p);
	Change_Color(RED);
	for (int i = 0; i < 2; i++) {
		Move_Cursor(p.pos.x, p.pos.y+i);
		for (int j = 0; j < 2; j++) {
			cout << p.sprite[i][j];
		}
	}
}

void GetItem(int**map,Player &p) {
	if(map[p.pos.y][p.pos.x]==4){
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				map[p.pos.y+i][p.pos.x+j] = 0;
			}
		}
		p.points += 20;
	}
}