#include "StrategyBenevolent.h"
#include "Player.h"

StrategyBenevolent::StrategyBenevolent(Player* inputPlayer){
    player = inputPlayer;
}

void StrategyBenevolent::reinforce()
{
    int totalReinforcements = player->getReinforcementsPerTurn(); //+ player->getHandOfCards()->exchange(deck, player) + player.hand->exchange(deck, player);
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
        countries.at(countryIndex)->setArmyValue((countries.at(countryIndex)->getArmyValue() + 1));
        totalReinforcements--;
    }
}

void StrategyBenevolent::attack()
{
    player->ui->consoleOut("Benevolent AI refuses to attack");
}

void StrategyBenevolent::fortify()
{
//    int sourceCountryIndex = 0;
//    int targetCountryIndex = 0;
//    vector<Country*> countries = player->getCountriesOwned();
//    vector<Country*> adjCountries;

//    for (int i = 0; i < countries.size(); i++) {
//        if (countries.at(i)->getArmyValue() > countries.at(sourceCountryIndex)->getArmyValue() && !(countries.at(i)->getPlayer()->getAdjCountriesOwned(countries.at(i)).size() == 0)) {
//            sourceCountryIndex = i;
//        }
//    }

//    adjCountries = countries.at(sourceCountryIndex)->getPlayer()->getAdjCountriesOwned(countries.at(sourceCountryIndex));

//    for (int i = 0; i < adjCountries.size(); i++) {
//        if (adjCountries.at(i)->getArmyValue() < adjCountries.at(targetCountryIndex)->getArmyValue()) {
//            targetCountryIndex = i;
//        }
//    }

//    int army = (countries.at(sourceCountryIndex)->getArmyValue() - adjCountries.at(targetCountryIndex)->getArmyValue()) / 2;
//    countries.at(sourceCountryIndex)->setArmyValue(countries.at(sourceCountryIndex)->getArmyValue() - army);
//    adjCountries.at(targetCountryIndex)->setArmyValue(adjCountries.at(targetCountryIndex)->getArmyValue() + army);
}
