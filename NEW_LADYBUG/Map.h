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
	for (int i = 0; i < MAP_ROW; i++) {
		Move_Cursor(0, i);
		for (int j = 0; j < MAP_COL; j++) {
			
			if (map[i][j] == 1) {
				Change_Color(BLUE);
				cout << char(178);
			}
			else if(map[i][j] == 2){
				Change_Color(GREEN);
				cout << char(178);
			}
			else if (map[i][j] == 3) {
				Change_Color(YELLOW);
				cout << char(178);
			}
			else {
				cout << " ";
			}
		}
	}
}