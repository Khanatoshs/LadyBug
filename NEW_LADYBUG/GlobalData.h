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
#define MAP_ROW 47
//---------------------------------------------------------------

//ENEMIES

//Max number of enemies
#define NUM_ENEMIES 5
//Enemy Initial Position
#define E_INI_POS_X 10
#define E_INI_POS_Y 10

//----------------------------------------------------------------

//Player

//Player Initial position
#define P_INI_POS_X 38
#define P_INI_POS_Y 23

//Player Movement differential
#define MOV_DIFF 2

//Lives
#define LIVES 3


#pragma comment(lib, "user32")

using namespace std;
using namespace System;

int Console_Width = Console::WindowWidth;
int Console_Height = Console::WindowHeight;

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
};

//Item Data
typedef struct Item {
	Position pos;
	int color;
	int value;
};

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
bool Check_Limits(Position p,int**map) {
	if (p.x <0 || p.x+1>Console_Width) {
		return false;
	}
	if (p.y <0 || p.y +1>Console_Height) {
		return false;
	}
	if (map[p.y][p.x] == 1 || map[p.y][p.x] == 2 || map[p.y][p.x] == 3) {
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

//Searches map for number code num of desired element returns a collection of Struct Position ande the size of array in variable size
Position* Search_Map(int num,int**map,int &size) {
	int cont = 0;
	for (int i = 1; i < MAP_ROW; i+=2) {
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
	for (int i = 1; i < MAP_ROW; i += 2) {
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