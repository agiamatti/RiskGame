#include "Card.h"

//enum Type { INF, CAV, ART, WILD };

using namespace std;

// Defualt Constructor. Not used but was required by another member if the team
Card::Card() {
		country = "unset";
		type = Type::WILD;
}

// Parameterized Constructor. Used at the start of the game to populate the deck
Card::Card(string c, Type t) {
		country = c;
		type = t;
}

// Copy constructor. Used in the exchange method
Card::Card(const Card& c) {
	country = c.country;
	type = c.type;
}

// Accessors and Mutators
string Card::getCountry() { 
	return country; 
}

Type Card::getType() { 
	return type; 
}
	
void Card::setCountry(string c) { 
	country = c; 
}
	
void Card::setType(Type t) { 
	type = t; 
}
	
// Simple toString method
string Card::toString() {
	string typeName;
	switch (type) {
	case 0: typeName = "Infantry";
		break;
	case 1: typeName = "Cavalry";
		break;
	case 2: typeName = "Artillery";
		break;
	default: typeName = "Wild";
	}
	return  "Country: " + country + ", Type: " + typeName + ".";
}
	// Destructor
Card::~Card() { 
	//cout << "Calling Card Destructor" << endl; 
}
