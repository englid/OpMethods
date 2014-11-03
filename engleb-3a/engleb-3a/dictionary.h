#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;



class dictionary{
private:
public:
	dictionary(string fileName);
	vector<string> list;
	void selectionSort();
	void quickSort();
	void quickSort(int l, int f, vector<string> temp);
	int partition(int f, int l, vector<string> temp);
	void swap(int i, int m);
	int dictionary::binarySearchByLetter(char word, vector<string> dictionary, int bottom, int top);
	void print();
};

dictionary::dictionary(string fileName){
	string newWord;
	ifstream fin;
	fin.open(fileName);
	if (!fin){ cout << "error"; }
	while (fin.good()){
		fin >> newWord;
		if (newWord.length() >= 5){
			list.push_back(newWord);
		}
	}
}

void dictionary::selectionSort(){
	int n = list.size();
	for (int i = 0; i < n - 1; i++){
		int min = i;
		for (int j = i + 1; j < n; j++){
			if (list[j].compare(list[min]) < 0){
				min = j;
			}
			if(i != min)
				swap(i, min);
		}
	}
}

void dictionary::swap(int i, int min){
	string temp = list[min];
	list[min] = list[i];
	list[i] = temp;
}

void dictionary::print(){
	for (int i = 0; i < list.size(); i++){
		cout << list[i] << endl;
	}
}

void dictionary::quickSort(){
	this->quickSort(0, list.size() - 1, list);
}

int dictionary::partition(int f, int l, vector<string> temp){
	int pivotIndex = f;
	for (int i = f + 1; i <= l; i++){
		if (temp[i].compare(temp[pivotIndex]) < 0){
			pivotIndex++;
			if (i != pivotIndex)
				swap(i, pivotIndex);
		}
	}
	if (f != pivotIndex){ swap(f, pivotIndex); }
	return pivotIndex;
}

void dictionary::quickSort(int f, int l, vector<string> temp){
	if (f < l){
		int pivotIndex = partition(f, l, temp);
		quickSort(f, pivotIndex - 1, temp);
		quickSort(pivotIndex + 1, l, temp);
	}
}

int dictionary::binarySearchByLetter(char word, vector<string> dictionary, int bottom, int top)  //returns -1 if no letter is found, else returns index where letter is found
{
	if (bottom > top)
	{
		return -1;
	}
	int middle = (bottom + top) / 2;
	if (word == list[middle][0])
	{
		return middle;
	}
	else if (word > list[middle][0])
	{
		return binarySearchByLetter(word, list, middle + 1, top);
	}
	else if (word < list[middle][0])
	{
		return binarySearchByLetter(word, list, bottom, middle - 1);
	}
	return -1;
}