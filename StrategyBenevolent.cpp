#include "StrategyBenevolent.h"
#include "Player.h"

StrategyBenevolent::StrategyBenevolent(Player* inputPlayer){
    player = inputPlayer;
}

void StrategyBenevolent::reinforceAtStart(int x){
    int totalReinforcements = x;
    int countryIndex = 0;
    vector <Country*> countries = player->getCountriesOwned();
    int min = 20000;

    while (totalReinforcements > 0) {
        for (int i = 0; i < countries.size(); i++) {
            if (countries.at(i)->getArmyValue()<min) {
                min = countries.at(i)->getArmyValue();
                countryIndex = i;
            }
        }
        player->reinforce(countries.at(countryIndex),1);
        totalReinforcements--;
    }
}

void StrategyBenevolent::reinforce(){
    int totalReinforcements = player->getReinforcementsPerTurn() + player->getHandOfCards()->automaticExchange(player);
    int countryIndex = 0;
    vector <Country*> countries = player->getCountriesOwned();
    int min = 20000;

    while (totalReinforcements > 0) {
        for (unsigned long i = 0; i < countries.size(); i++) {
            if (countries.at(i)->getArmyValue()<min) {
                min = countries.at(i)->getArmyValue();
                countryIndex = i;
            }
        }
        player->reinforce(countries.at(countryIndex),1);
        totalReinforcements--;
    }
}

void StrategyBenevolent::attack(){
    player->ui->consoleOut("Benevolent AI refuses to attack");
}


void StrategyBenevolent::fortify(){
    unsigned long sourceCountryIndex = -1;
    int amount = 1;
    vector<Country*> countries = player->getCountriesOwned();
    Country* target;

    for (unsigned long i = 0; i < countries.size(); i++) {
        for(unsigned long j = 0; j< player->getAdjCountriesOwned(countries.at(i)).size(); j++){

            if (countries.at(i)->getArmyValue()+1 > player->getAdjCountriesOwned(countries.at(i)).at(j)->getArmyValue()) {
                sourceCountryIndex = i;
                target = player->getAdjCountriesOwned(countries.at(i)).at(j);
                amount = (countries.at(i)->getArmyValue() - player->getAdjCountriesOwned(countries.at(i)).at(j)->getArmyValue())/2;
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

//Benevolent bot always rolls minimum
int StrategyBenevolent::getDice(int max){
    return 1;
}

bool StrategyBenevolent::isHumanStrategy(){
    return false;
}
