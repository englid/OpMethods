#include <string>
#include <fstream>
#include <iostream>
#include "d_matrix.h"

class grid
{
private:
	int length;
	int width;
public:
	matrix<char> workGrid;
	grid(string fileName);
	int getLength();
	void setLength(int length);
	int getWidth();
	void setWidth(int width);

};

