#pragma once
#include "Deck.h"
#include "Hand.h"
#include "Dice.h"
#include "RiskGUI.h"
#include "StrategyBenevolent.h"
#include "StrategyAggressive.h"
#include "StrategyHuman.h"

class Country;
class Strategy;
class Player {

public:
    //public attribute
    RiskGUI* ui;

    Player(RiskGUI* ui_in, Deck& deck);					// the parametrized constructor; the name will be asked in the constructor
    Player(RiskGUI* ui_in, Deck& deck, string playerName); // the other parametrized constructor
    ~Player();
    void setStrategy(Strategy* inputStrat);
	const string getPlayerName() const;
	void setPlayerName(string name);
	void addCountriesOwned(Country* country);
	bool removeCountriesOwned(Country* country);
    Hand* getHandOfCards(); //TODO const
	void setHandOfCards(Hand* cards);
	const Dice* getDice() const;
    int getNumberOfCountriesOwned() const;
	void calculateReinforcementsPerTurn(vector <Continent> continents); // must be called at the beginning of each turn for the player
	int getReinforcementsPerTurn();
    vector <Country*> getCountriesOwned();
	void printCountriesOwned();
	vector <Country*> getAdjCountriesOwned(Country* source);
	void printAdjCountries(Country* source);
	vector <Country*> getAdjAttackable(Country* source);
	void printAdjAttackable(Country* source);
	vector <Country*> getAttackReady();
	void printAttackReady();

    void reinforce();
	bool reinforce(Country* territory, int reinforcements);
    void attack();
	bool attack(Country* target, Country* source);
    void fortify();
	bool fortify(Country* target, int fortifications, Country* source);


	void printHandOfCards();

	bool ownsCountry(Country* country);
	int* roll(int num);
    //int getIndex(int start, int end, string item);

private:
	string playerName;					// the name of the player
	vector <Country*> countriesOwned;	// the Countries owned by the player
	Hand* hand;							// the hand of cards owned by the player
	Dice* dice;							// the dice facility owned by the player
	int reinforcementsPerTurn;			// reinforcements per turn given to player
    Strategy* strategy;

};
