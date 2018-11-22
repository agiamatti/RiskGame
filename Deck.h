#pragma once

#include<iostream>
#include<string>
#include<vector>
#include<time.h>

#include "Card.h"
#include "Info.h"

using namespace std;

class Deck {
public:
	Deck(vector<Info> info); // Parameterized Constructor. Used at the start of the game
    Deck();
	int getTotalExchanges();
	void incrementsTotalExchanges();
    int getExchangeBonus();
	void showDeck();
	Card draw();
    void returnCard(Card c);
	unsigned int size();
	void demonstrateCorrectness();
	~Deck();

private:
    int totalExchanges; // A running counter of the number of card exchanges
    vector<Card> deck; // The deck of cards is implimented as a vector of card objects
};
