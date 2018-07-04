#include"GlobalData.h"

//Open map and pass the values to variable
void Read_Map(int**map) {
	ifstream file;
	file.open("mapa-1.txt");
	for (int i = 0; i < MAP_ROW; i++) {
		for (int j = 0; j < MAP_COL; j++)
		{
			int data;
			file >> data;
			map[i][j] = data;
		}
	}
	file.close();
}
void Draw_Map(int**map) {
	for (int i = 0; i < MAP_ROW; i+=2) {
		for (int j = 0; j < MAP_COL; j+=2) {
			DrawSquare(map, j, i);
		}
	}
}

void DrawPoints(Player p) {
	Move_Cursor(80,4);
	cout << "Points: "<<p.points;
}