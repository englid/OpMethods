#include "dictionary.h"
#include "grid.h"
#include <stdio.h>
#include <conio.h>
using namespace std;

void findMatchesBinary(dictionary dict, grid grid);
void testSearch(string dictFile);

void main(){
	dictionary test = dictionary("test4.txt");
	grid test2("input15.txt", 15);
	//test.print();
	test.selectionSort();
	cout << "\n\n";
	//test.print();
	cout << "\n\n";

	findMatches(test, test2);
	//test2.printGrid();

	cout << endl << endl;
	grid test3("input30.txt", 30);
	//test3.printGrid();

	cout << "\nDone.\t";
	int f;
	cin >> f;
}

void findMatchesBinary(dictionary dict, grid grid){
	int n, m;
	for (int l = 0; l < grid.getSize(); l++){									//cover matrix length
		for (int w = 0; w < grid.getSize(); w++){								//cover matrix width	
			int i = dict.binarySearchByLetter(grid.workGrid[w][l], dict.list, 0, dict.list.size() -1 );
			if (i == -1)
				continue;
			while (dict.list[i][0] == grid.workGrid[w][l]){
					for (int x = -1; x <= 1; x++){									//x and y represent all directions  <-- Not sure how the algorithm works at this point -Rob
						for (int y = -1; y <= 1; y++){
							if (y == 0 && x == 0)
								continue;
							for (int j = 0; j < dict.list[i].length(); j++){			//final loop for checking for matches
								if (j == dict.list[i].length()-1){
									cout << dict.list[i]<< endl;
									break;
								}
								n = (w + j * y);
								m = (l + j * x);
								if (n < 0)
									n = n + grid.getSize();
								if (n >= grid.getSize())
									n = n - grid.getSize();
								if (m < 0)
									m = m + grid.getSize();
								if (m >= grid.getSize())
									m = m - grid.getSize();
								if ((dict.list[i])[j] != grid.workGrid[n][m])
									break;
							}
						}
					}
					i++;
					if (i >= dict.list.size())
						break;
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
	//findMatches(dict, searchGrid);
}
