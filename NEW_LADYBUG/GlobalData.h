#pragma once

#include<iostream>
#include<conio.h>
#include<Windows.h>
#include<math.h>
#include<time.h>
#include<fstream>

//Arrow_Keys
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

//Colors
#define CYAN 1
#define GREEN 2
#define BLUE 3
#define RED 4
#define YELLOW 5
#define WHITE 6

//Direction of Movement
#define UP 8
#define LEFT 4
#define RIGHT 6
#define DOWN 2

//Map
#define MAP_COL 80
#define MAP_ROW 50
//---------------------------------------------------------------

//ENEMIES

//Max number of enemies
#define NUM_ENEMIES 5
//Enemy Initial Position
#define E_INI_POS_X 10
#define E_INI_POS_Y 10
//Enemy Time between movements
#define MOVETIME 0.5
//Tiem bewtween enemy spawns
#define SPAWN_TIME 5
//----------------------------------------------------------------

//Player

//Player Initial position
#define P_INI_POS_X 38
#define P_INI_POS_Y 24

//Player Movement differential
#define MOV_DIFF 2

//Lives
#define LIVES 3


#pragma comment(lib, "user32")

using namespace std;
using namespace System;

typedef struct Timer {
	time_t start;
	time_t end;
};

//Position of an element
typedef struct Position {
	int x=0;
	int y=0;
};

//Player Data
typedef struct Player{
	Position pos;
	int direction=UP;
	int lives=LIVES;
	bool dead=false;
	long points=0;
	int movment_diff=MOV_DIFF;
	char**sprite;
	
};

//Enemy Data
typedef struct Enemy{
	Position pos;
	int direction=UP;
	bool dead=true;
	int movment_diff = MOV_DIFF;
	char**sprite;
	Timer timer;
};

//Item Data
typedef struct Item {
	Position pos;
	int color;
	int value;
};

//------------------------------------------------------------

int Console_Width = Console::WindowWidth;
int Console_Height = Console::WindowHeight;

Timer SpawnTimer;

void InitSpawnTimer() {
	time(&SpawnTimer.end);
	time(&SpawnTimer.start);
}
//------------------------------------------------------------
void InitEnemies(Enemy* enemyArray) {
	for (int j = 0; j < NUM_ENEMIES; j++) {
		enemyArray[j].pos.x = E_INI_POS_X;
		enemyArray[j].pos.y = E_INI_POS_Y;
		enemyArray[j].sprite = new char*[2];
		for (int i = 0; i < 2; i++) {
			enemyArray[j].sprite[i] = new char[2];
		}
	}
}

void InitPlayer(Player &p) {
	p.pos.x = P_INI_POS_X;
	p.pos.y = P_INI_POS_Y;

	p.sprite = new char*[2];
	for (int i = 0; i < 2; i++) {
		p.sprite[i] = new char[2];
	}
}

void InitMap(int** map) {
	for (int i = 0; i < MAP_ROW; i++) {
		map[i] = new int[MAP_COL];
	}
}

//------------------------------------------------------------

void Maximize_Console() {
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
	Console_Width = Console::WindowWidth;
	Console_Height = Console::WindowHeight;
}
void Cursor_visible() {
	Console::CursorVisible = !Console::CursorVisible;
}
void Move_Cursor(int x, int y) {
	Console::SetCursorPosition(x, y);
}

//Change color 1 Cyan 2 Green 3 Blue 4 Red 5 Yellow Default Black
void Change_Color(int color) {
	switch (color) {
	case CYAN:
		Console::ForegroundColor = ConsoleColor::Cyan;
		break;
	case GREEN:
		Console::ForegroundColor = ConsoleColor::Green;
		break;
	case BLUE:
		Console::ForegroundColor = ConsoleColor::Blue;
		break;
	case RED:
		Console::ForegroundColor = ConsoleColor::Red;
		break;
	case YELLOW:
		Console::ForegroundColor = ConsoleColor::Yellow;
		break;
	case WHITE:
		Console::ForegroundColor = ConsoleColor::White;
		break;
	default:
		Console::ForegroundColor = ConsoleColor::Black;
		break;
	}
}
//Changes Ascii value to a direction for players or enemies to use
int KeyToDirection(char key) {
	
	switch (key) {
	case KEY_LEFT: return LEFT; break;
	case KEY_UP : return UP; break;
	case KEY_RIGHT : return RIGHT; break;
	case KEY_DOWN : return DOWN; break;
	default:return 0;
	}
}



//Checks if anything goes beyond limits

bool Check_Limits(Position p) {
	if (p.x <0 || p.x + 1>Console_Width) {
		return false;
	}
	if (p.y <0 || p.y + 1>Console_Height) {
		return false;
	}
}

bool Check_LimitsEnemy(Position p,int**map) {
	if (Check_Limits(p)) {
		return false;
	}
	if (map[p.y][p.x] == 1 || map[p.y][p.x] == 2 || map[p.y][p.x] == 3) {
		return false;
	}
	return true;
}

bool Check_LimitsPlayer(Position p, int**map) {
	if (Check_Limits(p)) {
		return false;
	}
	if (map[p.y][p.x] == 1 || map[p.y][p.x] == 3) {
		return false;
	}
	return true;
}


void Hide_Trail(int x, int y) {
	for (int i = 0; i < 2; i++)
	{
		Move_Cursor(x, y + i);
		cout << " " << " ";
	}
}

//Searches map for number code num of desired element returns a collection of Struct Position and
//the size of array in variable size (used because there could be many spawn points)
Position* Search_Map(int num,int**map,int &size) {
	int cont = 0;
	for (int i = 0; i < MAP_ROW; i+=2) {
		for (int j = 0; j < MAP_COL; j+=2){
			if (map[i][j] == num) {
				cont++;
			}
		}
	}
	size = cont;
	if (cont == 0) {
		return nullptr;
	}
	Position* arrPos = new Position[cont];
	int n = 0;
	for (int i = 0; i < MAP_ROW; i += 2) {
		for (int j = 0; j < MAP_COL; j += 2) {
			if (map[i][j] == num) {
				arrPos[n].x = j;
				arrPos[n].y = i;
				n++;
			}
		}
	}
	return arrPos;
}

//Draws one square of 2x2 starting at x,y
void DrawSquare(int**map, int x, int y) {
	for (int i = 0; i < 2; i++) {
		Move_Cursor(x, y + i);
		for (int j = 0; j < 2; j++) {
			switch (map[y + i][x + j]) {
			case 1:
				Change_Color(BLUE);
				cout << char(178);
				break;
			case 2:
				Change_Color(GREEN);
				cout << char(178);
				break;
			case 3:
				Change_Color(YELLOW);
				cout << char(178);
				break;
			case 4:
				Change_Color(WHITE);
				cout << 'o';
				break;
			default:
				cout << " ";
				break;
			}
		}
	}
}