#include "Board.h"
using namespace std;

int main()
{
	cout << "----------------------------------" << endl << "PUZZLE 1" << endl << endl;
	ifstream fin;

	// Read the sample grid from the file.
	string fileName = "sudoku1.txt";
	string file2 = "sudoku2.txt";
	string file3 = "sudoku3.txt";

	fin.open(fileName.c_str());
	if (!fin)
	{
		cerr << "Cannot open " << fileName << endl;
		exit(1);
	}

	try
	{
		board b1(SquareSize);

		while (fin && fin.peek() != 'Z')
		{
			b1.initialize(fin);
			b1.print();
			cout << endl << endl << "Attempting to solve: " << endl;
			b1.solve();
			b1.print();
		}
	}
	catch (indexRangeError &ex)
	{
		cout << ex.what() << endl;
		exit(1);
	}
	fin.close();
	
	cout << endl << "----------------------------------" << endl << "PUZZLE 2" << endl << endl;
	fin.open(file2.c_str());
	if (!fin)
	{
		cerr << "Cannot open " << fileName << endl;
		exit(1);
	}

	try
	{
		board b2(SquareSize);

		while (fin && fin.peek() != 'Z')
		{
			b2.initialize(fin);
			b2.print();
			cout << endl << endl << "Attempting to solve: " << endl;
			b2.solve();
			b2.print();
		}
	}
	catch (indexRangeError &ex)
	{
		cout << ex.what() << endl;
		exit(1);
	}
	fin.close();

	cout << endl << "----------------------------------" << endl << "PUZZLE 3" << endl << endl;
	fin.open(file3.c_str());
	if (!fin)
	{
		cerr << "Cannot open " << fileName << endl;
		exit(1);
	}

	try
	{
		board b3(SquareSize);

		while (fin && fin.peek() != 'Z')
		{
			b3.initialize(fin);
			b3.print();
			cout << endl << endl << "Attempting to solve: " << endl;
			b3.solve();
			b3.print();
		}
	}
	catch (indexRangeError &ex)
	{
		cout << ex.what() << endl;
		exit(1);
	}
}