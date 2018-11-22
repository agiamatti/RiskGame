#include "StrategyHuman.h"
#include "Player.h"

StrategyHuman::StrategyHuman(Player* inputPlayer){
    player = inputPlayer;
}

void StrategyHuman::reinforceAtStart(int x){

    int totalReinforcements = 1;
    int reinforcements;
    int reinforceIndex;

    player->printCountriesOwned();

    while (totalReinforcements > 0){
        player->ui->consoleOut( "Choose a country of yours to reinforce it by 1." );


        reinforceIndex = player->ui->getIndex(1, player->getNumberOfCountriesOwned(), "country index");

        player->ui->consoleOut( "Choose number of reinforcements to add to " + player->getCountriesOwned().at(reinforceIndex-1)->getCountryName() );
        player->ui->consoleOut( "Available reinforcements: " +  to_string(totalReinforcements) );


        reinforcements = player->ui->getIndex(0, totalReinforcements, "number of reinforcements");

        player->reinforce(player->getCountriesOwned().at(reinforceIndex-1), reinforcements);
        totalReinforcements = totalReinforcements - reinforcements;
    }


}

void StrategyHuman::reinforce(){

    int totalReinforcements = player->getReinforcementsPerTurn() + player->getHandOfCards()->exchange(player);
    int reinforcements;
    int reinforceIndex;

    player->printCountriesOwned(); //prints the countries owned for reference

    while (totalReinforcements > 0){
        player->ui->consoleOut( "Available reinforcements: " + to_string(totalReinforcements));
        player->ui->consoleOut( "Choose a country of yours to reinforce." );


        reinforceIndex = player->ui->getIndex(1, player->getNumberOfCountriesOwned(), "country index");

        player->ui->consoleOut( "Choose number of reinforcements to add to " + player->getCountriesOwned().at(reinforceIndex-1)->getCountryName() );
        player->ui->consoleOut( "Available reinforcements: " +  to_string(totalReinforcements) );


        reinforcements = player->ui->getIndex(0, totalReinforcements, "number of reinforcements");

        player->reinforce(player->getCountriesOwned().at(reinforceIndex-1), reinforcements);
        totalReinforcements = totalReinforcements - reinforcements;
    }

}

void StrategyHuman::attack(){
    bool attacking = true;
    int sourceIndex;
    int targetIndex;
    Country* source;
    Country* target;
    string response;
    vector <Country*> attackable; //vector of attackable indices of countries from a given territory
    vector <Country*> attackReady;

    while (attacking && !player->getAttackReady().empty()) {
        //need to reset these values when we are beginning a 2nd attack
        source = NULL;
        target = NULL;
        attackable.clear();
        attackReady.clear();

        player->ui->consoleOut( "Do you want to attack? Please enter 'no' to stop, or anything else to continue." );
        response = player->ui->getResponse();


        if (response == "no") {
            attacking = false;
            return;
        }

        //must print countries with an army value greater than 1
        player->ui->consoleOut( "Countries that " + player->getPlayerName() + " can attack from:");
        player->printAttackReady();

        attackReady = player->getAttackReady();
        player->ui->consoleOut( "Select a country to launch an attack." );
        sourceIndex = player->ui->getIndex(1, attackReady.size(), "country index");
        source = attackReady.at(sourceIndex - 1);

        attackable = player->getAdjAttackable(source);
        player->ui->consoleOut( "From " + source->getCountryName() + " select one country to attack." );
        player->printAdjAttackable(source);

        targetIndex = player->ui->getIndex(1, attackable.size(), "country index");
        target = attackable.at(targetIndex - 1);

        //ui->consoleOut( "Source: " + source->getCountryName() + " Target: " + target->getCountryName() );

        int transferAmount;
        int transferMax;


        int transferMin = player->attack(target, source);
        if (transferMin>0 && source->getArmyValue()>1) { //if the attack succeeds, attack will return true; and we need the source to have more than 1 army

                transferMax = source->getArmyValue() - 1;
                player->ui->consoleOut( "You can transfer at least " + to_string(transferMin)+ ", or up to " +  to_string(transferMax) + " from " + target->getCountryName() + " to " + source->getCountryName() + "." );
                transferAmount = player->ui->getIndex(transferMin, transferMax, "number of armies");

                player->fortify(target, transferAmount, source);
        }
    }

    if(player->getAttackReady().empty()){
        player->ui->consoleOut("You have no territories you can attack from.");
    }
}

void StrategyHuman::fortify(){
        string response;
        player->ui->consoleOut( "Do you want to fortify any territories? Please enter 'no' to end fortification phase and your turn." );
        response = player->ui->getResponse();

        if (response == "no") {
            return;
        }

        int armyValue = 0;
        int sourceCountryIndex = 0;
        int targetCountryIndex = 0;
        Country* target = NULL;
        Country* source = NULL;
        bool checkSource = false;

        player->printCountriesOwned();

        player->ui->consoleOut( "Select a country to withdraw troops from." );

        while (!checkSource) {

            sourceCountryIndex = player->ui->getIndex(1, player->getNumberOfCountriesOwned(), "country index");


            if (player->getCountriesOwned().at(sourceCountryIndex - 1)->getArmyValue() < 2) {
                player->ui->consoleOut( "You can only withdraw troops from a territory with greater than 1 army value. "); //cannot withdraw from a country with less than 1
            }

            else if (player->getAdjCountriesOwned(player->getCountriesOwned().at(sourceCountryIndex - 1)).size() == 0) {
                player->ui->consoleOut( "You do not own any adjacent countries where you can move troops from." );
            }

            else {
                checkSource = true;
            }

        }

        source = player->getCountriesOwned().at(sourceCountryIndex - 1);
        player->printAdjCountries(source);

        player->ui->consoleOut( "Select a target country that you want to fortify" );

        targetCountryIndex = player->ui->getIndex(1, player->getAdjCountriesOwned(source).size(), "country index");

        target = player->getAdjCountriesOwned(source).at(targetCountryIndex - 1);


        player->ui->consoleOut( "Enter army value for fortifcation: " );
        armyValue = player->ui->getIndex(0, source->getArmyValue()-1, "army value");

        player->fortify(target, armyValue, source);

}

// asks user for input if dice_mode is NOT set automatically to max
int StrategyHuman::getDice(int max){
    return player->ui->getIndex(1, max , "number");
}

bool StrategyHuman::isHumanStrategy(){
    return true;
}
