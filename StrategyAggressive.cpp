#include "StrategyAggressive.h"
#include "Player.h"

StrategyAggressive::StrategyAggressive(Player* inputPlayer){
    player = inputPlayer;
}


void StrategyAggressive::reinforceAtStart(int x){

    int countryIndex = 0;
    vector <Country*> countries = player->getCountriesOwned();
    int max = 0;


    for (unsigned long i = 0; i < countries.size(); i++) { //checks the player's countries, finds the one with the highest number of troops
        if (!player->getAdjAttackable(countries.at(i)).empty() && countries.at(i)->getArmyValue()>max) {
           max = countries.at(i)->getArmyValue();
           countryIndex = i;
         }
    }

        player->reinforce(countries.at(countryIndex),x);

}



void StrategyAggressive::reinforce(){
    int totalReinforcements = player->getReinforcementsPerTurn() + player->getHandOfCards()->automaticExchange(player);
    int countryIndex = 0;
    vector <Country*> countries = player->getCountriesOwned();
    int max = 0;


    for (unsigned long i = 0; i < countries.size(); i++) {  //checks the player's countries, finds the one with the highest number of troops
        if (!player->getAdjAttackable(countries.at(i)).empty() && countries.at(i)->getArmyValue()>max) {
           max = countries.at(i)->getArmyValue();
           countryIndex = i;
         }
    }

        player->reinforce(countries.at(countryIndex),totalReinforcements);

}


void StrategyAggressive::attack(){
    bool attacking = true;

    Country* source;
    Country* target;
    string response;
    vector <Country*> attackable; //vector of attackable indices of countries from a given territory
    vector <Country*> attackReady;

    while (attacking) {
        //need to reset these values when we are beginning a 2nd attack
        source = NULL;
        target = NULL;
        attackable.clear();
        attackReady.clear();

       vector <Country*> countries = player->getCountriesOwned();
       int countryIndex = -1;
       int max = 0;

       for (unsigned long i = 0; i < countries.size(); i++) { //will find an attackable country with more than 1 troops
            if (!player->getAdjAttackable(countries.at(i)).empty() && countries.at(i)->getArmyValue()>max && countries.at(i)->getArmyValue()>1) {
                max = countries.at(i)->getArmyValue();
                countryIndex = i;
            }
        }


       if(countryIndex == -1){
            attacking = false;
            break;
       }
        source = countries.at(countryIndex);
        attackable = player->getAdjAttackable(source);
        target = attackable.at(0);

        //cout << "Attacking " << source->getCountryName() << " from " << target->getCountryName() << endl;
        player->ui->consoleOut( "Aggressive AI attacks! Source: " + source->getCountryName() + " Target: " + target->getCountryName() );

        if (player->attack(target, source) && source->getArmyValue()>1) { //if the attack succeeds, attack will return true; and we need the source to have more than 1 army

                int transferMax = source->getArmyValue() - 1;
                player->fortify(target, transferMax, source);
        }
    }

}


void StrategyAggressive::fortify(){
    unsigned long sourceCountryIndex = -1;
    int amount = 1;
    vector<Country*> countries = player->getCountriesOwned();
    Country* target;

    for (unsigned long i = 0; i < countries.size(); i++) {
        for(unsigned long j = 0; j< player->getAdjCountriesOwned(countries.at(i)).size(); j++){

            if (countries.at(i)->getArmyValue() > 1 && !player->getAdjAttackable(player->getAdjCountriesOwned(countries.at(i)).at(j)).empty()) { //if there is a territory with 2+ AV surrounding a territory that can attack
                sourceCountryIndex = i;
                target = player->getAdjCountriesOwned(countries.at(i)).at(j);
                amount = countries.at(i)->getArmyValue()- 1;
                break;
            }
        }
    }

    if(sourceCountryIndex!=-1 && target!=NULL){
        //cout << "forting " << countries.at(sourceCountryIndex)->getCountryName() << " to " << target->getCountryName() << " with " << amount << endl;
        player->fortify(target, amount, countries.at(sourceCountryIndex));

    }

    else{
        player->ui->consoleOut(player->getPlayerName() + " cannot find a suitable fortification.");
    }

}

//Aggressive bot always rolls max
int StrategyAggressive::getDice(int max){
    return max;
}

bool StrategyAggressive::isHumanStrategy(){
    return false;
}
