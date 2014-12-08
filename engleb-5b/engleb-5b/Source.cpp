// Project 5

#include <iostream>
#include <limits.h>
#include "d_except.h"
#include <list>
#include <fstream>
#include "d_matrix.h"
#include "graph.h"
#include <queue>

using namespace std;

struct solution		//solution struct
{
	string directions;
	int moves;
} ;
vector<solution> paths;

struct treeNode{
	solution* current;
	treeNode* left = NULL;
	treeNode* right = NULL;
};

class tree{
public:
	treeNode head;

	treeNode vectorToTree();
};


class maze
{
public:
	maze(ifstream &fin);
	void print(int, int, int, int);
	bool isLegal(int i, int j);

	void setMap(int i, int j, int n);
	int getMap(int i, int j) const;
	void mapMazeToGraph(graph &g);
	int getRows(){ return rows; }
	int getCols(){ return cols; }

	void queueVertices(treeNode, queue<treeNode>);
	void findPathRecursive();
	void findShortestPath1();
	void findShortestPath2();
	void findShortestPath3();

private:
	int rows; // number of rows in the maze
	int cols; // number of columns in the maze

	matrix<bool> value;
	matrix<int> map;      // Mapping from maze (i,j) values to node index values

	void findPathRecursive(int curri, int currj, int goali, int goalj, graph g, int moves, string directions);

	int findShortestPath1(treeNode head);
	int findShortestPath1(treeNode *head);
	int findShortestPath2(treeNode head);
	int findShortestPath3(treeNode head);
};

void maze::setMap(int i, int j, int n)
// Set mapping from maze cell (i,j) to graph node n. 
{
	map[i][j] = n;
}

int maze::getMap(int i, int j) const
// Return mapping of maze cell (i,j) in the graph.
{
	return map[i][j];
}

maze::maze(ifstream &fin)
// Initializes a maze by reading values from fin.  Assumes that the
// number of rows and columns indicated in the file are correct.
{
	fin >> rows;
	fin >> cols;

	char x;

	value.resize(rows, cols);
	for (int i = 0; i <= rows - 1; i++)
	for (int j = 0; j <= cols - 1; j++)
	{
		fin >> x;
		if (x == 'O')
			value[i][j] = true;
		else
			value[i][j] = false;
	}

	map.resize(rows, cols);
}

void maze::print(int goalI, int goalJ, int currI, int currJ)
// Print out a maze, with the goal and current cells marked on the
// board.
{
	cout << endl;

	if (goalI < 0 || goalI > rows || goalJ < 0 || goalJ > cols)
		throw rangeError("Bad value in maze::print");

	if (currI < 0 || currI > rows || currJ < 0 || currJ > cols)
		throw rangeError("Bad value in maze::print");

	for (int i = 0; i <= rows - 1; i++)
	{
		for (int j = 0; j <= cols - 1; j++)
		{
			if (i == goalI && j == goalJ)
				cout << "*";
			else
			if (i == currI && j == currJ)
				cout << "+";
			else
			if (value[i][j])
				cout << " ";
			else
				cout << "X";
		}
		cout << endl;
	}
	cout << endl;
}

bool maze::isLegal(int i, int j)
// Return the value stored at the (i,j) entry in the maze.
{
	if (i < 0 || i > rows || j < 0 || j > cols)
		throw rangeError("Bad value in maze::isLegal");

	return value[i][j];
}

void maze::mapMazeToGraph(graph &g)
// Create a graph g that represents the legal moves in the maze m.
{
	int nodeIndex = 1;
	for (int i = 0; i < getRows(); i++){
		for (int j = 0; j < getCols(); j++){
			if (value[i][j] == true){
				node *n = new node();
				n->setId(nodeIndex);
				g.addNode(*n);
				setMap(i, j, nodeIndex);
				nodeIndex++;
			}
		}
	}
	g.printNodes();

	for (int i = 0; i < getRows(); i++){
		for (int j = 0; j < getCols(); j++){
			if (i != getRows() - 1){
				if (getMap(i, j) > 0 && getMap(i + 1, j) > 0)
					g.addEdge(getMap(i, j) - 1, getMap(i + 1, j) - 1);
			}
			if (j != getCols() - 1){
				if (getMap(i, j) > 0 && getMap(i, j + 1) > 0)
					g.addEdge(getMap(i, j) - 1, getMap(i, j + 1) - 1);
			}
		}
	}
	g.printEdges();


}

void maze::findPathRecursive(){
	graph g;
	mapMazeToGraph(g);
	findPathRecursive(0, 0, getRows() - 1, getCols() - 1, g, 0, "");
	for (int i = 0; i<paths.size(); i++){
		cout << paths[i].directions << endl;
		cout << paths[i].moves << endl;
		cout << "\n\n";
	}
}

void maze::findPathRecursive(int curri, int currj, int goali, int goalj, graph g, int moves,string directions){
	print(goali, goalj, curri, currj);
	cout << "\n\n";
	int current = getMap(curri, currj) - 1;
	g.visit(current);
	//g.printNodes();

	if (current == getMap(goali, goalj) - 1){
		directions = directions + " solved.";
		solution path;
		path.directions = directions;
		path.moves = moves;
		paths.push_back(path);
		return;
	}

	for (int next = 1; next <= g.numNodes(); next++)
	{
		if (g.getNode((next)-1).isVisited())
			continue;
		if (g.isEdge(current, next - 1) || g.isEdge(next - 1, current))
		{
			int nexti;
			int nextj;
			if (currj != goalj){
				if (getMap(curri, currj + 1) == next){				//Right
					nexti = curri;
					nextj = currj + 1;
					directions = directions + "go right, ";
				}
			}
			if (curri != goali){
				if (getMap(curri + 1, currj) == next){			//Down
					nexti = curri + 1;
					nextj = currj;
					directions = directions + "go down, ";
				}
			}
			if (currj != 0){
				if (getMap(curri, currj - 1) == next){				//Left
					nexti = curri;
					nextj = currj - 1;
					directions = directions + "go left, ";
				}
			}
			if (currj != 0){
				if (getMap(curri - 1, currj) == next){				//UP
					nexti = curri - 1;
					nextj = currj;
					directions = directions + "go up, ";
				}
			}
			findPathRecursive(nexti, nextj, goali, goalj, g, moves+1,directions);
		}
	}
}

void maze::findShortestPath1(){
	tree treePath;
	treeNode current = treePath.vectorToTree();

	int shortest = findShortestPath1(current);

	cout << "The shortest path has " << shortest << " moves" << endl;
}
void maze::findShortestPath2(){
	tree treePath;
	treeNode current = treePath.vectorToTree();

	int shortest = findShortestPath2(current);

	cout << "The shortest path has " << shortest << " moves" << endl;
}
void maze::findShortestPath3(){
	tree treePath;
	treeNode current = treePath.vectorToTree();

	int shortest = findShortestPath3(current);

	cout << "The shortest path has " << shortest << " moves" << endl;
}
int maze::findShortestPath1(treeNode head){
	//dfs code here
	int shortest = (head.current)->moves;
	int current = findShortestPath1(head.left);
	if (current < shortest){ return current; }
	current = findShortestPath1(head.right);
	return 	current;
}
int maze::findShortestPath1(treeNode *head){ // overloaded function for pointer type parameter
	int shortest = head->current->moves;
	int current = findShortestPath1(head->left);
	if (current < shortest){ return current; }
	current = findShortestPath1(head->right);
	return current;
}
int maze::findShortestPath2(treeNode head){
	//bfs code here
	int shortest = head.current->moves;
	queue<treeNode> queue;
	queue.push(head);
	while (!queue.empty()){
		treeNode current = queue.front();
		queue.push(*current.left);
		queue.push(*current.right);
		queue.pop();
		if (current.current->moves < shortest){ shortest = current.current->moves; }
	}

	return shortest;
}
int maze::findShortestPath3(treeNode head){
	// Dijkstra's Algorithm code here
	int shortest = 9999999; //arbitrary large size
	treeNode temp;
	queue<treeNode> vertices;
	queueVertices(head, vertices);

	while (!vertices.empty()){
		temp = vertices.front();
		if (temp.current->moves < shortest){ shortest = temp.current->moves; }
		vertices.pop();
	}

	return shortest;
}

void maze::queueVertices(treeNode node, queue<treeNode> vertices){
	vertices.push(node);
	if (node.left != NULL){
		queueVertices(*node.left, vertices);
	}
	if (node.right != NULL){
		queueVertices(*node.right, vertices);
	}
}

treeNode tree::vectorToTree(){
	int size = paths.size();
	int counter = 0;

	treeNode *curr = new treeNode;
	curr->current = &(paths[counter]);
	counter++;
	treeNode *index = curr;

	while (true){

		if (counter < size){
			treeNode *left = new treeNode;
			index->left = left;
			left->current = &(paths[counter]);
			//cout << paths[counter].moves << endl;
			counter++;				
		}		
		if (counter < size){
			treeNode *right = new treeNode;
			index->right = right;
			right->current = &(paths[counter]);
			//cout << paths[counter].moves << endl;
			counter++;
		}
		else{
			break;
		}
			index = index->left;	
	}
	return *curr;
}

int main()
{
	char x;
	ifstream fin;

	// Read the maze from the file.
	string fileName = "maze1.txt";

	fin.open(fileName.c_str());
	if (!fin)
	{
		cerr << "Cannot open " << fileName << endl;
		exit(1);
	}

	try
	{

		graph g;
		while (fin && fin.peek() != 'Z')
		{
			maze m(fin);
			int i = m.getRows() - 1;
			int j = m.getCols() - 1;
			m.print(i, j, 0, 0);
			m.findPathRecursive();
			m.findShortestPath3();

		}


	}

	catch (indexRangeError &ex)
	{
		cout << ex.what() << endl; exit(1);
	}
	catch (rangeError &ex)
	{
		cout << ex.what() << endl; exit(1);
	}
	getchar();
}
