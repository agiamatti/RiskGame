#pragma once

#include "Card.h"
#include "Deck.h"


class Player;
class Country;

class Hand {
	// The player's hand of cards is implimented as a vector of cards
	vector<Card> hand;
public:
	Hand(); 
	Hand(Deck& deck); 
	void showHand(); 
	void addCard(Card c); // Manually adds a card to a player's hand
	int exchange(Deck& d, Player& p); // int represents number of units
	~Hand(); 
};
