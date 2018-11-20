#include "StrategyAggressive.h"
#include "Player.h"

StrategyAggressive::StrategyAggressive(Player* inputPlayer){
    player = inputPlayer;
}


void StrategyAggressive::reinforce()
{
    int totalReinforcements = player->getReinforcementsPerTurn(); //+ player->getHandOfCards()->exchange(deck, player) + player.hand->exchange(deck, player);
    int countryIndex = 0;
    vector <Country*> countries = player->getCountriesOwned();
    int max = 0;

    while (totalReinforcements > 0) {
        for (int i = 0; i < countries.size(); i++) {
            if (!countries.at(i)->getPlayer()->getAdjAttackable(countries.at(i)).empty() && countries.at(i)->getArmyValue()>max) {
                max = countries.at(i)->getArmyValue();
                countryIndex = i;
            }
        }
        countries.at(countryIndex)->setArmyValue((countries.at(countryIndex)->getArmyValue() + 1));
        totalReinforcements--;
    }
}


void StrategyAggressive::attack()
{
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

       for (int i = 0; i < countries.size(); i++) {
            if (!countries.at(i)->getPlayer()->getAdjAttackable(countries.at(i)).empty() && countries.at(i)->getArmyValue()>max && countries.at(i)->getArmyValue()>1) {
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

        cout << "Attacking " << source->getCountryName() << " from " << target->getCountryName() << endl;
        player->ui->consoleOut( "Aggressive AI attacks! Source: " + source->getCountryName() + " Target: " + target->getCountryName() );

        if (player->attack(target, source) && source->getArmyValue()>1) { //if the attack succeeds, attack will return true; and we need the source to have more than 1 army

                int transferMax = source->getArmyValue() - 1;
                player->fortify(target, transferMax, source);
        }
    }

}


void StrategyAggressive::fortify()
{

    vector <Country*> countries = player->getCountriesOwned();
    int countryIndex = -1;
    int max = 0;

    for (int i = 0; i < countries.size(); i++) {
         if (!countries.at(i)->getPlayer()->getAdjAttackable(countries.at(i)).empty() && countries.at(i)->getArmyValue()>max && countries.at(i)->getArmyValue()>1) {
             max = countries.at(i)->getArmyValue();
             countryIndex = i;
         }
     }

    if(countryIndex>-1)
        vector <Country*> maxCountryNeighbors = countries.at(countryIndex)->getPlayer()->getAdjCountriesOwned(countries.at(countryIndex));



}

