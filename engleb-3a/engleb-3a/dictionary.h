#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class dictionary{
private:
public:
	dictionary();
	~dictionary();
	vector<string> list;
};

dictionary::dictionary(){
	string newWord;
	ifstream fin;
	fin.open("dictionary.txt");
	if (!fin){ cout << "error"; }
	while (fin.good()){
		fin >> newWord;
		if (newWord.length() >= 5){
			list.push_back(newWord);
		}
	}
}

dictionary::~dictionary(){
	cout << "Deleting dictionary.\t";
}