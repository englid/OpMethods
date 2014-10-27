#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

int partition(int f, int l, string list[]);

class dictionary{
private:
public:
	dictionary(string fileName);
	vector<string> list;
	void selectionSort();
	void quickSort();
	void quickSort(int l, int f, vector<string> temp);
	void swap(int i, int m);
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
	quickSort(0, list.size() - 1, list);
}

int partition(int f, int l, vector<string> temp){
	int pivotIndex = f;
	for (int i = f + 1; i <= l; i++){
		if (temp[i].compare(temp[pivotIndex]) < 0){
			pivotIndex++;
			swap(i, pivotIndex);
		}
	}
	swap(f, pivotIndex);
	return pivotIndex;
}

void dictionary::quickSort(int f, int l, vector<string> temp){
	if (f < l){
		int pivotIndex = partition(f, l, temp);
		quickSort(f, pivotIndex - 1, temp);
		quickSort(pivotIndex + 1, l, temp);
	}
}