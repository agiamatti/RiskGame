#pragma once

#include<iostream>
#include<string>
#include<vector>
#include<time.h>

#include "Card.h"
#include "Info.h"



using namespace std;

class Deck {
	int totalExchanges; // A running counter of the number of card exchanges
	vector<Card> deck; // The deck of cards is implimented as a vector of card objects
public:
	Deck(vector<Info> info); // Parameterized Constructor. Used at the start of the game
	int getTotalExchanges();
	void incrementsTotalExchanges();
	void showDeck();
	Card draw();
	unsigned int size();
	void demonstrateCorrectness();
	~Deck();
};
