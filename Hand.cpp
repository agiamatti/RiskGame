#include "Deck.h"
#include "Player.h"
#include "Country.h"

// Defualt Constructor. Not used but was required by another member if the team
Hand::Hand() {
	// cout << "Calling default constructor
}

// This is the hand constructor that will be used at the start of the game
// It creates a hand of five random cards drawn from the top of the deck
Hand::Hand(Deck& deck) {
	const unsigned int HAND_SIZE = 5;
	for (unsigned int i = 0; i < HAND_SIZE; i++) {
		hand.push_back(deck.draw());
	}
}

// Simple method to show a players hand
// Used when choosing cards to form a set
void Hand::showHand() {
	cout << "Showing Hand" << endl;
	unsigned long currentHandSize = hand.size();
	for (unsigned int i = 0; i < currentHandSize; i++) {
		cout << "Card #" << i << ": " << hand[i].toString() << endl;
	}
}

// This method allows the player to exchange cards in their hand for armies
int Hand::exchange(Deck& d, Player& p) {
	
	// Total armies the player will receive
	int totalArmies = 0;

	// Create variables used during the loop
	bool createSet;
	Card set[3];
	int c1Index, c2Index, c3Index;
	bool ownedFlag = false;
	
	// Show hand so that the player can choose cards during the first iteration
	showHand(); 

	do {
		// If the player's hand has more than five cards they must exchange
		if (hand.size() < 5) {
			cout << "Would you like to exchange cards for armies? 0/1 ";
			cin >> createSet;

			if (!createSet) {
				cout << "No cards exchanged" << endl;
				return 0;
			}
		}
		else
			createSet = true;

		// When selecting cards, enter three numbers separated by spaces
		cout << "Select 3 cards to form a set: ";

		// Get the card indexs in the player's hand
		bool badIndex = false;
		cin >> c1Index; 
		if (c1Index < 0 || c1Index > hand.size() - 1)
			badIndex = true;
		cin >> c2Index;
		if (c2Index < 0 || c2Index > hand.size() - 1)
			badIndex = true;
		cin >> c3Index;
		if (c3Index < 0 || c3Index > hand.size() - 1)
			badIndex = true;


		if (badIndex)
			cout << "Error: Bad Index. Enter indexes from 0 - " << hand.size() - 1 << endl; 
		else {
			bool threeOfAKind = hand[c1Index].getType() == hand[c2Index].getType() && 
				hand[c2Index].getType() == hand[c3Index].getType();
			bool oneOfEach = hand[c1Index].getType() != hand[c2Index].getType() && 
				hand[c1Index].getType() != hand[c3Index].getType() && hand[c2Index].getType() != hand[c3Index].getType();

			if (threeOfAKind || oneOfEach) {
				// Display a message indicating which type of set was formed
				if (threeOfAKind)
					cout << "Three of a kind set formed" << endl;
				else if (oneOfEach)
					cout << "One of each set formed" << endl;

				// Calculate the amount of armies earned
				totalArmies += (4 + (2 * d.getTotalExchanges()));

				// Add territory control detection when it gets implimented in later assignments
				vector<Country*> playerCountries = p.getCountriesOwned(); 

				if (!ownedFlag) {
					for (unsigned int i = 0; i < playerCountries.size(); i++) {
						if (hand[c1Index].getCountry() == playerCountries[i]->getCountryName() ||
							hand[c2Index].getCountry() == playerCountries[i]->getCountryName() ||
							hand[c3Index].getCountry() == playerCountries[i]->getCountryName()) {

							cout << "Army bonus for owned country" << endl;
							ownedFlag = true;
							totalArmies += 2;
							break;
						}
					}
				}

				d.incrementsTotalExchanges();

				// Order the indexes 
				int indexes[3];
				// A > B
				if (c1Index > c2Index) {
					// A > C && A > B
					if (c1Index > c3Index) {
						indexes[0] = c1Index; // A
						// A > B && A > C && B > C
						if (c2Index > c3Index) {
							indexes[1] = c2Index; // B
							indexes[2] = c3Index; // C
						}
						// A > B && A > C && C > B
						else {
							indexes[1] = c3Index; // C
							indexes[2] = c2Index; // B
						}
					}
					// A > B && A < C
					else {
						indexes[0] = c3Index; // C
						indexes[1] = c1Index; // A
						indexes[2] = c2Index; // B
					}
				}
				// B > A
				else if (c2Index > c1Index) {
					// B > A && B > C
					if (c2Index > c3Index) {
						indexes[0] = c2Index; // B
						// B > A && B > C && A > C
						if (c1Index > c3Index) {
							indexes[1] = c1Index; // A
							indexes[2] = c3Index; // C
						}
						// B > A && B > C && C > A
						else {
							indexes[1] = c3Index; // C
							indexes[2] = c1Index; // A
						}
					}
					// B > A && B < C
					else {
						indexes[0] = c3Index; // C
						indexes[1] = c2Index; // B
						indexes[2] = c1Index; // A
					}
				}
				// Shouldnt need another case 

				hand.erase(hand.begin() + indexes[0]);
				hand.erase(hand.begin() + indexes[1]);
				hand.erase(hand.begin() + indexes[2]);

				// If the player cannot possibly form another set
				if (hand.size() < 3)
					return totalArmies;
				// Otherwise show hand and give the option to form another set
				else
					showHand();
			}
			// If the selected cards do not form a set
			else
				cout << "Those cards do not form a set" << endl;
		}
	} while (createSet);

	return totalArmies;
}

// Adds a card to the player's hand
// The card parameter is generated with deck.draw()
void Hand::addCard(Card c) {
	hand.push_back(Card(c.getCountry(), c.getType()));
}

Hand::~Hand() {
	// cout << "Destroying player hand" << endl;
}
