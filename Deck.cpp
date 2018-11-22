#include "Deck.h"

using namespace std;

Deck::Deck(){

}

// This is the constructor that is used during the game
// It uses the info vector to get the list of country cards that need to be created 
Deck::Deck(vector<Info> info) {
	// Set the total number of card exchanges to zero
	totalExchanges = 0;

	// Create the country and type variables which will be assigned 
	// values during each pass through the loop
	string country;
	Type type;

	// Add a wild card to the bottom of the deck
	// This allows the deck.insert() method to work properly
	Card newCard("Wild Card", WILD);
	deck.push_back(newCard);

	// Initialize the random seed so that a new deck is generated each game
	srand(time(NULL));

	// This counter is used to control the type distribution
	// It is also used as the index when accessing the info vector
	int counter = 0;

	// This while loop is used to populate the deck with all of the country cards
	while (deck.size() <= info.size()) {

		// Generate an even distribution of types
		switch (counter % 3) {
		case 0: type = INF;
			break;
		case 1: type = CAV;
			break;
		case 2: type = ART;
			break;
		default: type = WILD;
		}

		// Generate a random index to insert the card at
		int index = rand() % deck.size();

		// Get the current card's country name
		country = info[counter].getCountry();

		// Create a new card using the current country name and type
		Card newCard(country, type);

		// Insert the card at a random index
		deck.insert(deck.begin() + index, newCard);

		// Increment the counter for the next iteration
		counter++;
	}

	// Remove the wild card from the bottom of the deck
	deck.pop_back();
}

// Returns the total number of card exchanges
// This is used when calculating the number of armies a player recieves
int Deck::getTotalExchanges() { 
	return totalExchanges; 
}

// Called after each successful card exchange
void Deck::incrementsTotalExchanges() { 
	totalExchanges++; 
}

int Deck::getExchangeBonus(){
    if (totalExchanges ==1)
        return 4;
    if (totalExchanges ==2)
        return 6;
    if (totalExchanges ==3)
        return 8;
    if (totalExchanges ==4)
        return 10;
    if (totalExchanges ==5)
        return 12;
    if (totalExchanges ==6)
        return 15;
    if (totalExchanges >6)
        return (totalExchanges-6)*5+15;
}

// Displays all of the cards in the deck
void Deck::showDeck() {
	for (unsigned int i = 0; i < deck.size(); i++) {
		cout << "Card #" << i << ": " << deck[i].toString() << endl;
	}
}

// Uses the deck vector's built in size function
unsigned int Deck::size() {
	return deck.size(); 
}

// Demonstrates that number of cards created is equal to the number of countries
// Also shows that there is an even distribution of types
// Created for the assignment demo
void Deck::demonstrateCorrectness() {
	int infCount, cavCount, artCount;
	infCount = cavCount = artCount = 0;
	cout << "Demonstrating Deck Correctness" << endl;
	cout << "Size of deck = " << deck.size() << endl;
	for (unsigned int i = 0; i < deck.size(); i++) {
		cout << "Card #" << i << " " << deck[i].toString() << endl;
		switch (deck[i].getType()) {
		case 0: infCount++;
			break;
		case 1: cavCount++;
			break;
		case 2: artCount++;
			break;
		default: cout << "Some error in demonstrate correctness method" << endl;
		}
	}
	cout << "Type Totals: Infantry = " << infCount << ", Cavalry = " << cavCount
		<< ", Artilley = " << artCount << endl;
}

// Removes and returns the top card of the deck
Card Deck::draw() {
	Card c = deck.back();
	deck.pop_back();
	return c;
}

void Deck::returnCard(Card c){
    deck.push_back(c);
}

// Simple message to indicate the deck destructor has been called
Deck::~Deck() { 
	//cout << "Calling Deck Destructor" << endl; 
}
