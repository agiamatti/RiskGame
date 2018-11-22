#pragma once
#include "RiskGUI.h"
#include "Deck.h"
#include "Hand.h"
#include "Dice.h"
#include "StrategyBenevolent.h"
#include "StrategyAggressive.h"
#include "StrategyHuman.h"

class Country;
class Strategy;

class Player{

public:
    //public attribute
    RiskGUI* ui;

    //constructors
    Player(RiskGUI* ui_in, Deck& deck);					// the parametrized constructor; the name will be asked in the constructor
    Player(RiskGUI* ui_in, Deck& deck, string playerName); // the other parametrized constructor
    ~Player();

    //attributes and other parametric methods
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

    //observer methods
    void setFlag(int x);
    int getFlag();
    void setTargetedCountry(Country * c);
    Country getTargetedCountry();
    void setSourceCountry(Country * c);
    Country getSourceCountry();
    void setOther(int y);
    int getOther();
    double getPercentWorldOwned();
    void setPercentWorldOwned(int totalCountries);
    void worldDomination();

    //Strategy and action methods
    void setStrategy(Strategy* inputStrat);
    bool hasHumanStrategy();
    void reinforce();
	bool reinforce(Country* territory, int reinforcements);
    void attack();
	bool attack(Country* target, Country* source);
    void fortify();
	bool fortify(Country* target, int fortifications, Country* source);


	void printHandOfCards();

	bool ownsCountry(Country* country);
	int* roll(int num);

private:
    string playerName;					// the name of the player
    Hand* hand;							// the hand of cards owned by the player
    Dice* dice;							// the dice facility owned by the player
    int other;							// for the observer pattern
    int flag;				            // for the observer pattern
    double percentWorldOwned;			// for the observer pattern
    Country* targetedCountry;			// for the observer pattern
    Country* sourceCountry;				// for the observer pattern
    int reinforcementsPerTurn;			// reinforcements per turn given to player
    vector <Country*> countriesOwned;	// the Countries owned by the player
    Strategy* strategy;

};
