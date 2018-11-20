#pragma once

#include <string>
#include <iostream>

#include "Card.h"

using namespace std;

// This enum is used to represent the differnt type of risk cards
enum Type { INF, CAV, ART, WILD };

class Card {
	// Each card has two data members; a country and a type
	string country;
	Type type;
public:
	Card();
	Card(string c, Type t);
	Card(const Card& c);
	string getCountry();
	Type getType();
	void setCountry(string c);
	void setType(Type t);
	string toString();
	~Card();
};
