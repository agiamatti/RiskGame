#pragma once

#include "Card.h"
#include "Deck.h"
#include "RiskGUI.h"



class Player;
class Country;

class Hand {
public:
	Hand(); 
    Hand(RiskGUI* ui_in, Deck* deck);
    ~Hand();
    // int represents number of units in exchange methods
    int exchange( Player* p); //user exchange
    int automaticExchange(Player* p); //automatic exchange
    void takeHand(Hand* otherHand);
	void showHand(); 
    void printHand();
	void addCard(Card c); // Manually adds a card to a player's hand
    Card removeCard(int index); //do not use alone as we are losing cards if the card is not returned to another hand or the deck
    Card removeCard(); //do not use alone as we are losing cards if the card is not returned to another hand or the deck
    void drawCardFromDeck();
    void returnCardToDeck(Card c);
    int getHandSize();

private:
    RiskGUI* ui; //ui
    vector<Card> hand; // The player's hand of cards is implimented as a vector of cards
    Deck* deck;
};
