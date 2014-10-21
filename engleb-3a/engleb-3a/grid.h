#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "d_matrix.h"

class grid{
private:
	int size;
public:
	matrix<char> workGrid;
	grid(string fileName, int size);
	int getSize(){ return size; }
	void setSize(int size){ this->size = size; }
	void printGrid();
};

grid::grid(string filename, int size){
	workGrid.resize(size, size);
	setSize(size);
	ifstream fin;
	string temp;
	string empty;
	int y = 0;
	fin.open(filename);
	if (!fin){ cout << "error"; }
	getline(fin, empty);
	while (fin.good() && y < size){
		getline(fin, temp);
		temp.erase(remove(temp.begin(), temp.end(), ' '), temp.end());
		for (int x = 0; x < size; x++){
			workGrid[y][x] = temp[x];
		}
		y++;
	}
	fin.close();
}

void grid::printGrid(){
	for (int y = 0; y < size; y++){
		for (int x = 0; x < size; x++){
			cout << workGrid[y][x];
		}
		cout << endl;
	}
}

