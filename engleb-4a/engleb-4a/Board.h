// Declarations and functions for project #4

#include <iostream>
#include <limits.h>
#include "d_matrix.h"
#include "d_except.h"
#include <list>
#include <fstream>

using namespace std;

typedef int ValueType; // The type of the value in a cell
const int Blank = -1;  // Indicates that a cell is 

const int SquareSize = 3;  //  The number of cells in a small square
//  (usually 3).  The board has
//  SquareSize^2 rows and SquareSize^2
//  columns.

const int BoardSize = SquareSize * SquareSize;

const int MinValue = 1;
const int MaxValue = 9;

int numSolutions = 0;

class board
	// Stores the entire Sudoku board
{
public:
	board(int);
	void clear();
	void initialize(ifstream &fin);
	void print();
	void printConflicts();
	bool isBlank(int, int);
	ValueType getCell(int, int);
	void setCell(int, int, int);
	void updateConflicts();

private:

	// The following matrices go from 1 to BoardSize in each
	// dimension, i.e., they are each (BoardSize+1) * (BoardSize+1)

	matrix<int> value;
	matrix<bool> col;
	matrix<bool> rows;
	matrix<bool> squares;
};

board::board(int sqSize)
: value(BoardSize + 1, BoardSize + 1), col(BoardSize + 1, BoardSize + 1), rows(BoardSize + 1, BoardSize + 1)
// Board constructor
{
	clear();
}

void board::clear()
// Mark all possible values as legal for each board entry
{
	for (int i = 1; i <= BoardSize; i++)
	for (int j = 1; j <= BoardSize; j++)
	{
		value[i][j] = Blank;
	}
}

void board::initialize(ifstream &fin)
// Read a Sudoku board from the input file.
{
	char ch;

	clear();

	for (int i = 1; i <= BoardSize; i++)
	for (int j = 1; j <= BoardSize; j++)
	{
		fin >> ch;

		// If the read char is not Blank
		if (ch != '.')
			setCell(i, j, ch - '0');   // Convert char to intj
	}
	updateConflicts();
}

int squareNumber(int i, int j)
// Return the square number of cell i,j (counting from left to right,
// top to bottom.  Note that i and j each go from 1 to BoardSize
{
	// Note that (int) i/SquareSize and (int) j/SquareSize are the x-y
	// coordinates of the square that i,j is in.  

	return SquareSize * ((i - 1) / SquareSize) + (j - 1) / SquareSize + 1;
}

ostream &operator<<(ostream &ostr, vector<int> &v)
// Overloaded output operator for vector class.
{
	for (int i = 0; i < v.size(); i++)
		ostr << v[i] << " ";
	cout << endl;
	return ostr;
}

ValueType board::getCell(int i, int j)
// Returns the value stored in a cell.  Throws an exception
// if bad values are passed.
{
	if (i >= 1 && i <= BoardSize && j >= 1 && j <= BoardSize)
		return value[i][j];
	else
		throw rangeError("bad value in Cell is out of bounds");
}

void board::setCell(int i, int j, int newValue){
	if (newValue < 1 || newValue > BoardSize)
		throw rangeError("bad value in setCell");
	else if (i >= 1 && i <= BoardSize && j >= 1 && j <= BoardSize)
		value[i][j] = newValue;
	else
		throw rangeError("bad value in Cell out of bounds");
}

bool board::isBlank(int i, int j)
// Returns true if cell i,j is blank, and false otherwise.
{
	if (i < 1 || i > BoardSize || j < 1 || j > BoardSize)
		throw rangeError("bad value in setCell");

	return (getCell(i, j) == Blank);
}

void board::print()
// Prints the current board.
{
	for (int i = 1; i <= BoardSize; i++)
	{
		if ((i - 1) % SquareSize == 0)
		{
			cout << " -";
			for (int j = 1; j <= BoardSize; j++)
				cout << "---";
			cout << "-";
			cout << endl;
		}
		for (int j = 1; j <= BoardSize; j++)
		{
			if ((j - 1) % SquareSize == 0)
				cout << "|";
			if (!isBlank(i, j))
				cout << " " << getCell(i, j) << " ";
			else
				cout << "   ";
		}
		cout << "|";
		cout << endl;
	}

	cout << " -";
	for (int j = 1; j <= BoardSize; j++)
		cout << "---";
	cout << "-";
	cout << endl;
}

void board::updateConflicts(){
	for (int j = 0; j <= BoardSize; j++){
		for (int k = 0; k <= BoardSize; k++){
			//if (getCell(j, k) != NULL){
				//int temp = getCell(j, k) - 1;
				//col[j][temp] = true;
				//rows[k][temp] = true;
			//}
		}
	}
}

void board::printConflicts(){

}