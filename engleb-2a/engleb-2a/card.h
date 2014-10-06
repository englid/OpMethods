#include <iostream>
#include <string>
using namespace std;

class card{
	friend ostream& operator<< (ostream& ostr, const card& t);
private:
	int value;
	int suit;
public:
	card(int v, int s);
	card(){};
	int getValue(){ return value; }
	void setValue(int v){ value = v; }
	int getSuit(){ return suit; }
	void setSuit(int s){ suit = s; }
};

ostream& operator<< (ostream& ostr, card& t){
	ostr << "Card: ";
	if (t.getValue() == 1){
		ostr << "Ace";
	}
	else if (t.getValue() >= 11){
		switch (t.getValue()){
		case 11:
			ostr << "Jack";
			break;
		case 12:
			ostr << "Queen";
			break;
		case 13:
			ostr << "King";
			break;
		}
	}
	else{
		ostr << t.getValue();
	}
	switch (t.getSuit()){
	case 1:
		ostr << " of Clubs";
		break;
	case 2:
		ostr << " of Diamonds";
		break;
	case 3:
		ostr << " of Hearts";
		break;
	case 4:
		ostr << " of Spades";
		break;
		return ostr;
	}
}

card::card(int v, int s){
	value = v;
	suit = s;
}