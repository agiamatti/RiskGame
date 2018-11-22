#include "Deck.h"
//Circular Dependency
#include "Player.h"
#include "Country.h"

// Defualt Constructor. Not used but was required by another member if the team
Hand::Hand() {
    // ui->consoleOut( "Calling default constructor
}

// This is the hand constructor that will be used at the start of the game
// It creates a hand of five random cards drawn from the top of the deck
Hand::Hand(RiskGUI* ui_in, Deck* d) {
    ui = ui_in;
    deck = d;
}

// Simple method to show a players hand
// Used when choosing cards to form a set
void Hand::showHand() {
    if(hand.size()>0)
        ui->consoleOut("Showing Hand:");
	unsigned long currentHandSize = hand.size();
	for (unsigned int i = 0; i < currentHandSize; i++) {
        ui->consoleOut("Card #" + to_string(i+1) + ": " + hand[i].toString());
	}
}

void Hand::printHand() {
    cout<< "Showing Hand:"<<endl;
    unsigned long currentHandSize = hand.size();
    for (unsigned int i = 0; i < currentHandSize; i++) {
        cout<<"Card #" + to_string(i+1) + ": " + hand[i].toString()<<endl;
    }
}


void Hand::drawCardFromDeck(){
    hand.push_back(deck->draw());
}

// This method allows the player to exchange cards in their hand for armies
int Hand::exchange(Player* p) {
	
	// Total armies the player will receive
	int totalArmies = 0;

	// Create variables used during the loop
	Card set[3];
    int c1Index, c2Index, c3Index;
	bool ownedFlag = false;
    bool mustExchange;

    // If the player's hand has more than five cards they must exchange
    if (hand.size() > 5)
        mustExchange = true;

    else{
        mustExchange = false;
    }

    if(!mustExchange){
        ui->consoleOut("Do you want to perform a card exchange? Enter \"Yes\" to perform a card exchange, or anything else to stop.");
        string response = ui->getResponse();
        if (response.find("Yes")==string::npos){
            return 0;
        }
    }


   int counter = 0;
   bool exchangeOn = true;
   while (hand.size()>2 && exchangeOn) {

       if(counter>1){
           ui->consoleOut("Do you want to perform continue card exchange? Enter \"Yes\" to perform a card exchange, or anything else to stop.");
           string response = ui->getResponse();
           if (response.find("Yes")==string::npos){
               exchangeOn = false;
               continue;
           }
       }

        // Show hand so that the player can choose cards during the first iteration
        showHand();

        // When selecting cards, enter three numbers separated by spaces
        ui->consoleOut("Select 3 cards to form a set: ");

        // Get the card indexs in the player's hand
        c1Index = ui->getIndex(1,hand.size(),"card index") - 1;
        c2Index = ui->getIndex(1,hand.size(),"card index") - 1;
        c3Index = ui->getIndex(1,hand.size(),"card index") - 1;

        if(c1Index==c2Index || c2Index==c3Index||c1Index==c3Index){
            ui->consoleOut("Each index must be unique. Please try again.");
            continue;
        }

        bool threeOfAKind = hand[c1Index].getType() == hand[c2Index].getType() && hand[c2Index].getType() == hand[c3Index].getType();
        bool oneOfEach = hand[c1Index].getType() != hand[c2Index].getType() && hand[c1Index].getType() != hand[c3Index].getType() && hand[c2Index].getType() != hand[c3Index].getType();

			if (threeOfAKind || oneOfEach) {
				// Display a message indicating which type of set was formed
				if (threeOfAKind)
                    ui->consoleOut("Three of a kind set formed");
				else if (oneOfEach)
                    ui->consoleOut("One of each set formed");

                // Add territory control detection when it gets implimented in later assignments
                vector<Country*> playerCountries = p->getCountriesOwned();

				if (!ownedFlag) {
					for (unsigned int i = 0; i < playerCountries.size(); i++) {
						if (hand[c1Index].getCountry() == playerCountries[i]->getCountryName() ||
							hand[c2Index].getCountry() == playerCountries[i]->getCountryName() ||
							hand[c3Index].getCountry() == playerCountries[i]->getCountryName()) {

                            ui->consoleOut( "You have received +2 army bonus for country: " + playerCountries.at(i)->getCountryName());
							ownedFlag = true;
							totalArmies += 2;
							break;
						}
					}
				}

                // Calculate the amount of armies earned
                deck->incrementsTotalExchanges();
                totalArmies = totalArmies + deck->getExchangeBonus();
                returnCardToDeck(removeCard(c1Index));
                returnCardToDeck(removeCard(c2Index));
                returnCardToDeck(removeCard(c3Index));
			}
			// If the selected cards do not form a set
			else
                ui->consoleOut( "Those cards do not form a set");

    counter++;
    }

	return totalArmies;
}

// This method allows automatic players to exchange cards in their hand for armies
int Hand::automaticExchange(Player* p) {

    // Total armies the player will receive
    int totalArmies = 0;

    // Create variables used during the loop
    int c1Index = 1, c2Index = 2, c3Index = 3;
    bool canExchange;
    bool ownedFlag = false;

    // Show hand so that the player can choose cards during the first iteration
    showHand();

    // If the player's hand has more than five cards they must exchange
    if (hand.size() > 5)
        canExchange = true;

    else{
        canExchange = false;
        return 0;
    }

        bool threeOfAKind = false;
        bool oneOfEach = false;

        for(c1Index=0; c1Index<3; c1Index++ ){
            for(c2Index =c1Index+1; c2Index <4; c2Index++){
                for(c3Index = c2Index+1; c3Index<5;c3Index++){
                    threeOfAKind = hand[c1Index].getType() == hand[c2Index].getType() && hand[c2Index].getType() == hand[c3Index].getType();
                    oneOfEach = hand[c1Index].getType() != hand[c2Index].getType() && hand[c1Index].getType() != hand[c3Index].getType() && hand[c2Index].getType() != hand[c3Index].getType();

                    if((threeOfAKind || oneOfEach)){
                        goto label1; //better in this case than break
                    }
                }
            }
        }

        label1:
        // Display a message indicating which type of set was formed
        if (threeOfAKind)
            ui->consoleOut("Three of a kind set formed");
        else if (oneOfEach)
            ui->consoleOut("One of each set formed");


        // Add territory control detection when it gets implemented in later assignments
        vector<Country*> playerCountries = p->getCountriesOwned();

        if (!ownedFlag) {
            for (unsigned int i = 0; i < playerCountries.size(); i++) {
                if (hand[c1Index].getCountry() == playerCountries[i]->getCountryName() ||
                        hand[c2Index].getCountry() == playerCountries[i]->getCountryName() ||
                        hand[c3Index].getCountry() == playerCountries[i]->getCountryName()) {

                    ui->consoleOut( "You have received +2 army bonus for country: " + playerCountries.at(i)->getCountryName());
                    ownedFlag = true;
                    totalArmies += 2;
                    break;
                }
            }
        }

        // Calculate the amount of armies earned
        deck->incrementsTotalExchanges();
        totalArmies = totalArmies + deck->getExchangeBonus();
        cout << "Exchanging  " << totalArmies << endl;
        cout << " Hand size " << hand.size() << " indices " << c1Index << c2Index << c3Index << endl;
        returnCardToDeck(removeCard(c3Index));
        returnCardToDeck(removeCard(c2Index));
        returnCardToDeck(removeCard(c1Index));
        //deck->demonstrateCorrectness();

        // If the player cannot possibly form another set
        if (hand.size() < 6)
            return totalArmies;
        // Otherwise show hand and give the option to form another set
        else
            return totalArmies + automaticExchange(p); //recursive call if more than 5 cards remain after exchanging
}


// Adds a card to the player's hand
// The card parameter is generated with deck.draw()
void Hand::addCard(Card c) {
	hand.push_back(Card(c.getCountry(), c.getType()));
}

//returns a card to deck, typically after exchanging it
void Hand::returnCardToDeck(Card c){
    deck->returnCard(c);
}

//Removes the last card from player's hand; DO NOT use alone, as we are losing cards permanently from the deck
Card Hand::removeCard(){
    Card c = hand.back();
    hand.pop_back();
    return c;
}

//Removes a card from player's hand from a give index; DO NOT use alone, as we are losing cards permanently from the deck
Card Hand::removeCard(int index){
    Card c = hand.at(index);
    hand.erase(hand.begin() + index);
    return c;
}

//method for taking all the cards of a defeated player
void Hand::takeHand(Hand* otherHand){
    int size = otherHand->getHandSize();
    for(int i = 0; i<size; i++){
       addCard(otherHand->removeCard()); //adds each card to this hand, and takes it from the other hand
    }
}

int Hand::getHandSize(){
    return hand.size();
}

Hand::~Hand() {
}
