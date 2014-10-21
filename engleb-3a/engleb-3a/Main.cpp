#include "dictionary.h"
#include "grid.h"
#include <stdio.h>
#include <conio.h>
using namespace std;

void findMatches(dictionary dict, grid grid);
void testSearch(string dictFile);

void main(){
	dictionary test = dictionary("dictionary.txt");
	grid test2("input15.txt", 15);
	//findMatches(test, test2);
	test2.printGrid();

	cout << endl << endl;
	grid test3("input30.txt", 30);
	test3.printGrid();

	cout << "\nDone.\t";
}

void findMatches(dictionary dict, grid grid){
	for (int i = 0; i < dict.list.size(); i++){										//iterate through every word in dictionary
		for (int l = 0; l < grid.getSize(); i++){									//cover matrix length
			for (int w = 0; w < grid.getSize(); i++){								//cover matrix width
				if (dict.list[i][0] == grid.workGrid[w][l]){						//check if first letter matches
					for (int x = -1; x <= 1; x++){									//x and y represent all directions  <-- Not sure how the algorithm works at this point -Rob
						for (int y = -1; y <= 1; y++){
							if (y == 0 && x == 0)
								continue;
							for (int j = 0; j < dict.list[i].length(); j++){			//final loop for checking for matches
								if (j == dict.list[i].length()){
									cout << dict.list[i];
									break;
								}
								if (dict.list[i][j] != grid.workGrid[w + j * y][l + j * x])
									break;
							}
						}
					}
				}
			}
		}
	}
}

void testSearch(dictionary dict){
	string fileName;
	int size;
	cout << "What is the name of the grid file? ";
	cin >> fileName;
	cout << endl << "What is the size of the grid? ";
	cin >> size;
	grid searchGrid(fileName, size);
	findMatches(dict, searchGrid);
}
