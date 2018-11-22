#include "Player.h"
#include "Country.h"


// the parametrized constructor; the name is asked in the constructor
Player::Player(RiskGUI* ui_in, Deck* deck){
    hand = new Hand(ui_in, deck);
	dice = new Dice();
	reinforcementsPerTurn = 3;
    ui = ui_in;
    ui->consoleOut( "Please print your name in the console: ");
    playerName = ui->getResponse();
}

// the other parametrized constructor
Player::Player(RiskGUI* ui_in, Deck* deck, string playerName){
    hand = new Hand(ui_in, deck);
	dice = new Dice();
	reinforcementsPerTurn = 3;
    ui = ui_in;
	setPlayerName(playerName);
    strategy = new StrategyHuman(this);

}

// the destructor of the player object; manually deleting the hand, the dice, and all the countries in the countries owned list
Player::~Player(){
	delete hand;
	delete dice;
    //delete strategy;
}

//setting particular strategy
void Player::setStrategy(Strategy* inputStrat){
    strategy = inputStrat;
}

Strategy* Player::getStrategy(){
    return strategy;
}

bool Player::hasHumanStrategy(){
    return strategy->isHumanStrategy();
}


//Observer methods
void Player::setFlag(int x){
    flag = x;
}

int Player::getFlag(){
    return flag;
}

void Player::setTargetedCountry(Country* c){
    targetedCountry = c;
}

Country Player::getTargetedCountry(){
    return *targetedCountry;
}

void Player::setSourceCountry(Country * c){
    sourceCountry = c;
}

Country Player::getSourceCountry(){
    return *sourceCountry;
}

void Player::setOther(int y){
    other = y;
}

int Player::getOther(){
    return other;
}

//public method of obtaining player name
const string Player::getPlayerName() const {
	return playerName;
}

//public method for setting the player name
void Player::setPlayerName(string name) {
	Player::playerName = name;
}

//public method for adding countries; better to use Country::setPlayer()
void Player::addCountriesOwned(Country* country) {
	countriesOwned.push_back(country);
	country->setPlayerNR(this);

}

// public method for deleting countries
bool Player::removeCountriesOwned(Country* country) {
	for (unsigned int i = 0; i < countriesOwned.size(); i++) {
		if (country->getCountryName() == countriesOwned.at(i)->getCountryName()) {
			countriesOwned.erase(countriesOwned.begin() + i);
			return true;
		}
	}
	return false;
}

// Returns the player's hand of cards
Hand* Player::getHandOfCards() {
	return hand;
}

// Replaces the player's hand of cards
void Player::setHandOfCards(Hand* cardHand) {
	hand = cardHand;
}

// Return's the player's dice facility
const Dice* Player::getDice() const {
	return dice;
}

// shows the number of countries owned by the player
int Player::getNumberOfCountriesOwned() const {
	return countriesOwned.size();
}

// the calculateReinforcementsPerTurn() method should be invoked for each player at the beginning of the turn
void Player::calculateReinforcementsPerTurn(vector <Continent> continents) {
    drawCardTurn = false; // at the beginning of each turn it is set to false
	reinforcementsPerTurn = getNumberOfCountriesOwned() / 3;

	if (reinforcementsPerTurn < 3) {
		reinforcementsPerTurn = 3;
	}

    string bonus = playerName + " has the following continents: ";
	int continentsBonus = 0;
	int terrPerCont;

	for (unsigned int i = 0; i < continents.size(); i++) {
		terrPerCont = 0;
		for (int j = 0; j < continents.at(i).getSizeOfCountriesInContinent(); j++) {
			for (unsigned int k = 0; k < countriesOwned.size(); k++) {
				if (continents.at(i).getCountriesInContinent(j) == countriesOwned.at(k)->getCountryName()) {
					terrPerCont++;
				}
			}
		}

		if (terrPerCont == continents.at(i).getSizeOfCountriesInContinent()) {
			continentsBonus = continentsBonus + continents.at(i).getContinentValue();
            bonus = bonus + " " + continents.at(i).getContinentName() + " ";
		}
	}

    reinforcementsPerTurn = reinforcementsPerTurn + continentsBonus;
    if (continentsBonus == 0) {
        bonus = bonus + "none.";
    }
    ui->consoleOut(bonus);
    setFlag(9); setOther(continentsBonus);
}

//returns the number of reinforcements per turn for the player
int Player::getReinforcementsPerTurn() {
	return reinforcementsPerTurn;
}

//returns the countries owned by the player
vector <Country*> Player::getCountriesOwned() {
	return countriesOwned;
}

//returns the adjacent countries owned by the player for a country
vector <Country*> Player::getAdjCountriesOwned(Country* source) {
    vector <Country*> neighbors = source->getAdjCountries(); //uses method from country
	vector <Country*> ownNeighbors;
	
	for (unsigned int i = 0; i < neighbors.size(); i++) {
		if (ownsCountry(neighbors.at(i))) {
			ownNeighbors.push_back(neighbors.at(i));
		}
	}
	return ownNeighbors;
}

void Player::printAdjCountries(Country* source) {
    ui->consoleOut( "Adjacent countries to " + source->getCountryName() + ":" );
	for (unsigned int i = 0; i < getAdjCountriesOwned(source).size(); i++) {
        ui->consoleOut( to_string(i + 1) + ". " + getAdjCountriesOwned(source).at(i)->getCountryName() + ", army score: " +  to_string((source->getAdjCountries()).at(i)->getArmyValue()) + "." );
	}
}

//returns a vector of attackable territories (countries the player can attack from a given source), and prints the indicies to it
vector <Country*> Player::getAdjAttackable(Country* source) {
	vector <Country*> intArr;
    vector <Country*> initialList = source->getAdjCountries();
	for (unsigned int i = 0; i < initialList.size(); i++) {
		if (!ownsCountry(initialList.at(i))) {
			intArr.push_back(initialList.at(i));
		}
	}

	return intArr;

}

void Player::printAdjAttackable(Country* source) {
	vector <Country*> attackable = getAdjAttackable(source);
	for (unsigned int i = 0; i < attackable.size(); i++) {
        ui->consoleOut( to_string(i + 1) + ". " + attackable.at(i)->getCountryName() + ", army score: " +  to_string(attackable.at(i)->getArmyValue()) );
	}
}

//returns the countries that the player is able to launch an attack from: countries with greater than 1 army value, and that have neighboring countries that are not owned by the player
//pass 0 for normal mode
vector <Country*> Player::getAttackReady() {
    vector <Country*> attackReady;
    for (unsigned int i = 0; i < countriesOwned.size(); i++) {
		if (countriesOwned.at(i)->getArmyValue()>1 && !getAdjAttackable(countriesOwned.at(i)).empty()) {
			attackReady.push_back(countriesOwned.at(i));
		}
	}
	return attackReady;
}

void Player::printAttackReady() {
	vector <Country*> attackReady = getAttackReady();
	for (unsigned int i = 0; i < attackReady.size(); i++) {
        ui->consoleOut( to_string(i + 1) + ". " + attackReady.at(i)->getCountryName() + ", army score: " +  to_string(attackReady.at(i)->getArmyValue()) );
	}
}


//reinforce at the start of the game
void Player::reinforceAtStart(int x) {
    setFlag(1); ui->Notify();
    strategy->reinforceAtStart(x);
}

//reinforce calling the strategy's reinforce
void Player::reinforce() {
    setFlag(1); ui->Notify();
    strategy->reinforce();
}

// Game method for reinforcing a territory
bool Player::reinforce(Country* territory, int reinforcements) {
	for (unsigned int i = 0; i<countriesOwned.size(); i++) {
		if (countriesOwned[i]->getCountryName() == territory->getCountryName()) {
			territory->setArmyValue(territory->getArmyValue() + reinforcements);
            setFlag(2); setTargetedCountry(territory); setOther(reinforcements); ui->Notify();
			return true;
		}
	}

	return false;
}


//Self-sufficient attack method
void Player::attack() {
    setFlag(5); ui->Notify();
    strategy->attack();
}

//Game method for attacking an enemy territory from one of your own territories; returns 0 for failed attack, 1-3 for winning attacker dice
int Player::attack(Country* target, Country* source) {
	if (!ownsCountry(target) && target->isNeighbor(source) && source->getArmyValue()>1) { //army value must be larger than 1 to attack
        setSourceCountry(source); setTargetedCountry(target); setFlag(6); ui->Notify();

		int ctr = 1;

        while (source->getArmyValue() > 1 && target->getArmyValue()>0) {
			// to make sure we get correct input from attacker and defender

			int maxRollsA = 0;
			int maxRollsD = 0;
			int rollA = 0;
			int rollD = 0;
            int winningDice = 0;                    // the dice that won the attack
			
			//setting maximum rolls for defender and attacker
			if (source->getArmyValue() > 3) {
				maxRollsA = 3;
			}

			else {
                maxRollsA = source->getArmyValue()-1;
			}

			if (target->getArmyValue() > 2) {
				maxRollsD = 2;
			}

			else {
				maxRollsD = target->getArmyValue();
			}



            int* attackerRoll;
            int* defenderRoll;
            string attackerRollString = "";
            string defenderRollString = "";

            //Traditional Dice Mode DICE_MODE == 0
            if (ctr > 1 && ui->getDiceMode()==0 && strategy->isHumanStrategy()) {
                ui->consoleOut( "Do you want to continue attacking? Enter 'no' to stop." );
				string response;
                response = ui->getResponse();
				if (response == "no") {
                    return 0;
				}
			}
			

            if(ui->getDiceMode()==0){
                setFlag(7); ui->Notify();
                ui->consoleOut( "The attacker can use 1 to " +  to_string(maxRollsA) + " dice rolls. How many armies does the attacker want to use in attack #" +  to_string(ctr) + "?" );
                rollA = strategy->getDice(maxRollsA);

                winningDice = rollA;
                attackerRoll = roll(rollA);

                ui->consoleOut( "The defender can use 1 to " +  to_string(maxRollsD) + " dice rolls. How many armies does the defender want to use in attack #" +  to_string(ctr) + "?" );
                rollD = target->getPlayer()->getStrategy()->getDice(maxRollsD);

                defenderRoll = roll(rollD);

                for (int i = 0; i<rollA; i++){
                    attackerRollString = attackerRollString + " " + to_string(attackerRoll[i]);
                }

                for (int i = 0; i<rollD; i++){
                    defenderRollString = defenderRollString + " " + to_string(defenderRoll[i]);
                }
            }

            else{ //DICE_MODE 1 - AUTOMATIC DICE to MAX
                cout<<"shalala dice2"<<endl;
                attackerRoll = roll(maxRollsA);
                defenderRoll = roll(maxRollsD);
                winningDice = rollA = maxRollsA;
                rollD = maxRollsD;

                for (int i = 0; i<maxRollsA; i++){
                    attackerRollString = attackerRollString + " " + to_string(attackerRoll[i]);
                }

                for (int i = 0; i<maxRollsD; i++){
                    defenderRollString = defenderRollString + " " + to_string(defenderRoll[i]);
                }
            }



            ui->consoleOut( "Attack #" +  to_string(ctr) + "\tAttacker rolled: " + attackerRollString + "\tHighest: " +  to_string(*attackerRoll));
            ui->consoleOut( "\tDefender rolled: " + defenderRollString + "\tHighest: " +  to_string(*defenderRoll) );

			// comparing first roll
			if (attackerRoll[0] > defenderRoll[0]) {
				if (target->getArmyValue() < 2) {
                    ui->consoleOut( getPlayerName() + " has conquered " + target->getCountryName() );
                    Player* targetPlayer = target->getPlayer();
					target->getPlayer()->removeCountriesOwned(target); //removeCountriesOwned(target) from the owner; attack is over
					target->setPlayer(this); //setPlayer() calls addCountriesOwned()
					source->setArmyValue(source->getArmyValue() - 1); //you lose an army to fortify your new territory

                    if (!drawCardTurn){ //drawing one card if you haven't this turn due to conquest
                        hand->drawCardFromDeck();
                        drawCardTurn = true;
                    }

                    if(targetPlayer->getNumberOfCountriesOwned()==0){
                        hand->takeHand(targetPlayer->getHandOfCards()); //if the enemy is entirely defeated, take their cards
                    }


                    return winningDice-1;
				}
				target->setArmyValue(target->getArmyValue() - 1);	//target loses an army
			}

			else {
				source->setArmyValue(source->getArmyValue() - 1);
                winningDice--; //the attacker has one fewer army
			}

			//comparing second roll if it exists
			if (rollA > 1 && rollD > 1 && source->getArmyValue()>1) { //must make sure that source has an army value greater than 1
				if (attackerRoll[1] > defenderRoll[1]) {
					if (target->getArmyValue() < 2) {
                        ui->consoleOut( getPlayerName() + " has conquered " + target->getCountryName() );
                        Player* targetPlayer = target->getPlayer();
						target->getPlayer()->removeCountriesOwned(target); //removeCountriesOwned(target) from the owner; attack is over
						target->setPlayer(this); //setPlayer() calls addCountriesOwned()
						source->setArmyValue(source->getArmyValue() - 1); //you lose an army to fortify your new territory

                        if (!drawCardTurn){ //drawing one card if you haven't this turn due to conquest
                            hand->drawCardFromDeck();
                            drawCardTurn = true;
                        }

                        if(targetPlayer->getNumberOfCountriesOwned()==0){
                            hand->takeHand(targetPlayer->getHandOfCards()); //if the enemy is entirely defeated, take their cards
                        }

                        return winningDice-1;
					}
					target->setArmyValue(target->getArmyValue() - 1);	//target loses an army
				}

				else {
					source->setArmyValue(source->getArmyValue() - 1);
				}
			}

			ctr++;


		}

        return 0;
	}

    ui->consoleOut( getPlayerName() + " cannot attack " + target->getCountryName() + " from " + source->getCountryName() );
	if (!target->isNeighbor(source)) {
        ui->consoleOut( " as the two countries are not adjacent" );
	}

	if (source->getArmyValue()<2) {
        ui->consoleOut( " as the source does not have enough troops to attack" );
	}

	if (!ownsCountry(target)) {
        ui->consoleOut( " as you own the target country." );
	}

	return false;
}


//Self-suficient fortify() method, calls the parametrized fortify
void Player::fortify() {
    drawCardTurn = false; //turns drawCard false for the next turn
    setFlag(3); ui->Notify();
    strategy->fortify();
}

// Game method for fortifying a territory from troops from another adjacent one
bool Player::fortify(Country* target, int fortifications, Country* source) {

    if (source->getArmyValue()<fortifications || !ownsCountry(target) || !ownsCountry(source) || !source->isNeighbor(target)) {
        ui->consoleOut( "Invalid fortification" );
        return false;
    }

    for (unsigned int i = 0; i<countriesOwned.size(); i++) {
        if (countriesOwned[i]->getCountryName() == target->getCountryName()) {
            target->setArmyValue(target->getArmyValue() + fortifications);
            source->setArmyValue(source->getArmyValue() - fortifications);
            setSourceCountry(source); setTargetedCountry(target); setOther(fortifications) ;setFlag(4); ui->Notify();
            return true;
        }
    }

    return false;
}


// method for checking if a player owns a country. Assumes no duplicate country names, as is expected in a game of Risk
bool Player::ownsCountry(Country* country) {
	for (unsigned int i = 0; i<countriesOwned.size(); ++i) {
		if (countriesOwned[i] == country) {
			return true;
		}
	}
	return false;
}

// player method for printing countries owned
void Player::printCountriesOwned() {
    unsigned long size = countriesOwned.size();
    ui->consoleOut( "Countries owned by " + getPlayerName() );
	if (size == 0) {
        ui->consoleOut( "No countries owned." );
	}

	else {
		for (int i = 0; i < size; i++) {
            ui->consoleOut( to_string(i + 1) + ". " + countriesOwned.at(i)->getCountryName() + ", army score: " +  to_string(countriesOwned.at(i)->getArmyValue()) );
		}
	}
}

//player method to print the hand of cards
void Player::printHandOfCards() {
	hand->showHand();
}

// player method rolling the dice; int num is how many dice are desired to roll; 2 as defender, and 3 as attacker
int* Player::roll(int num) {
	return dice->roll(num);
}

