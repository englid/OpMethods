#include "d_except.h"
#include "d_node.h"
#include "card.h"
#include <iostream>
#include <string>

using namespace std;

class deck{
	friend ostream& operator<< (ostream& ostr, const deck& t);
private:
	//node <card>* head;
public:
	node <card>* head = NULL;
	deck();
};

deck::deck(){
	int value = 1;
	int suit = 1;
	node <card>* current = head;
	card newCard;
	node <card>* newNode;

	newCard = card(value, suit);
	newNode = new node<card>(newCard, head);
	head = newNode;
	current = head->next;

	for (suit; suit < 5; suit++){
		for (value; value < 14; value++){
			//newCard = card(value, suit);
			//newNode = new node<card>(newCard, current); // (newCard, head);
			//current = current->next;
			//cout << newCard << endl;
			newCard = card(value, suit);
			cout << newCard << endl;
		}
	}
}

ostream& operator<< (ostream& ostr, deck& t){
	if (t.head == NULL){ return ostr; }
	ostr << t.head << endl;
	node <card>* current = t.head;
	while (current->next != NULL){
		current = current->next;
		ostr << current << endl;
	}
	return ostr;
}