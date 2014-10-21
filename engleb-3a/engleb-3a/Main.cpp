#include "dictionary.h"
#include "grid.h"
#include <stdio.h>
#include <conio.h>
using namespace std;

void findMatches(dictionary dict, grid grid);
void testSearch(string dictFile, string gridFile);

void main(){
	dictionary test = dictionary("dictionary.txt");

	cout << "\nDone.\t";
}

void findMatches(dictionary dict, grid grid){
	for (int i = 0; i < dict.list.size; i++){										//iterate through every word in dictionary
		for (int l = 0; l < grid.getLength(); i++){									//cover matrix length
			for (int w = 0; w < grid.getWidth(); i++){								//cover matrix width
				if (dict.list[i][0] == grid.workGrid[w][l]){						//check if first letter matches
					for (int x = -1; x <= 1; x++){									//x and y represent all directions
						for (int y = -1; y <= 1; y++){
							if (y == 0 && x == 0)
								continue;
							for (int j = 0; j < dict.list[i].length; j++){			//final loop for checking for matches
								if (j == dict.list[i].length){
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
