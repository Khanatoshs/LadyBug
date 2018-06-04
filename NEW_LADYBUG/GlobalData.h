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

//Direction of Movement
#define UP 8
#define LEFT 4
#define RIGHT 6
#define DOWN 2

//---------------------------------------------------------------

//ENEMIES

//Max number of enemies
#define NUM_ENEMIES 5
//Enemy Initial Position
#define E_INI_POS_X 40
#define E_INI_POS_Y 40

//----------------------------------------------------------------

//Player

//Player Initial position
#define P_INI_POS_X 20
#define P_INI_POS_Y 20

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
typedef struct {
	int x=0;
	int y=0;
}Position;

//Player Data
typedef struct {
	Position pos;
	int direction=UP;
	int lives=LIVES;
	bool dead=false;
	long points=0;
	int movment_diff=MOV_DIFF;
	char**sprite;
	
}Player;

//Enemy Data
typedef struct {
	Position pos;
	int speed;
	bool dead=false;
}Enemy;

//Item Data
typedef struct {
	Position pos;
	int color;
	int value;
}Item;

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
	if (p.x <0 || p.x+1>Console_Width) {
		return false;
	}
	if (p.y <0 || p.y +1>Console_Height) {
		return false;
	}
	return true;
}
