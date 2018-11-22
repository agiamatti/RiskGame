#include "ObserverView.h"

ObserverView::ObserverView(){
}

ObserverView::ObserverView(RiskGUI* x){
    ui = x;
    ui->Attach(this);

}

void ObserverView::Update() {
    //Called by Notify() when state of Subject changes
    display();
}

void ObserverView::display() {
    ui->update();
//   cout<<"Better Work" + to_string(5) << endl;
    if(ui->getPlayerAtCurrentTurn()!=NULL){

            // =================================== Reinforce =================================== //

            if (ui->getPlayerAtCurrentTurn()->getFlag() == 9) {
                string bonus = ui->getPlayerAtCurrentTurn()->getPlayerName() + " has the following continent bonus: ";
                if (ui->getPlayerAtCurrentTurn()->getOther() == 0) {
                bonus = bonus + "none.";
                }
                else{
                    bonus = bonus + to_string(ui->getPlayerAtCurrentTurn()->getOther()) + ".";
                }
                ui->consoleOut(bonus);
            }


            if (ui->getPlayerAtCurrentTurn()->getFlag() == 1) {
                ui->consoleOut(ui->getPlayerAtCurrentTurn()->getPlayerName() + "'s reinforcement phase.");

            }

            if (ui->getPlayerAtCurrentTurn()->getFlag() == 2) {
                ui->consoleOut( ui->getPlayerAtCurrentTurn()->getPlayerName() + " is reinforcing " + ui->getPlayerAtCurrentTurn()->getTargetedCountry().getCountryName() + " with " + to_string(ui->getPlayerAtCurrentTurn()->getOther()) + " reinforcements. New army value: " + to_string(ui->getPlayerAtCurrentTurn()->getTargetedCountry().getArmyValue()));
            }

            // =================================== Fortify =================================== //

            if (ui->getPlayerAtCurrentTurn()->getFlag() == 3) {
                ui->consoleOut(ui->getPlayerAtCurrentTurn()->getPlayerName() + "'s fortification phase.");
            }

            if (ui->getPlayerAtCurrentTurn()->getFlag() == 4) {
                ui->consoleOut(ui->getPlayerAtCurrentTurn()->getPlayerName() + " is fortifying " + ui->getPlayerAtCurrentTurn()->getTargetedCountry().getCountryName() + " with " + to_string(ui->getPlayerAtCurrentTurn()->getOther()) + " armies from "
                    + ui->getPlayerAtCurrentTurn()->getSourceCountry().getCountryName() + ". " + ui->getPlayerAtCurrentTurn()->getSourceCountry().getCountryName() + " army value: " + to_string(ui->getPlayerAtCurrentTurn()->getSourceCountry().getArmyValue()) +
                    ", " + ui->getPlayerAtCurrentTurn()->getTargetedCountry().getCountryName() + " army value: " + to_string(ui->getPlayerAtCurrentTurn()->getTargetedCountry().getArmyValue()) );
            }

            // =================================== Attack =================================== //

            if (ui->getPlayerAtCurrentTurn()->getFlag() == 5) {
                ui->consoleOut(ui->getPlayerAtCurrentTurn()->getPlayerName() +  "'s attack phase");
            }

            if (ui->getPlayerAtCurrentTurn()->getFlag() == 6) {
                ui->consoleOut( ui->getPlayerAtCurrentTurn()->getPlayerName() + " is attacking " + ui->getPlayerAtCurrentTurn()->getTargetedCountry().getPlayer()->getPlayerName() + "'s " + ui->getPlayerAtCurrentTurn()->getTargetedCountry().getCountryName() + " from " + ui->getPlayerAtCurrentTurn()->getSourceCountry().getCountryName() + "!");
            }

            if (ui->getPlayerAtCurrentTurn()->getFlag() == 7) {
                 ui->consoleOut(ui->getPlayerAtCurrentTurn()->getPlayerName() + "'s " + ui->getPlayerAtCurrentTurn()->getSourceCountry().getCountryName() + " with army value " + to_string(ui->getPlayerAtCurrentTurn()->getSourceCountry().getArmyValue()) + " is attacking " + ui->getPlayerAtCurrentTurn()->getTargetedCountry().getPlayer()->getPlayerName() + "'s " + ui->getPlayerAtCurrentTurn()->getTargetedCountry().getCountryName() + " with army value " + to_string(ui->getPlayerAtCurrentTurn()->getTargetedCountry().getArmyValue()) + ".");

            }

            // ============================== Resetting some variables & Clearing  ============================== //

            ui->getPlayerAtCurrentTurn()->setFlag(0);
            ui->getPlayerAtCurrentTurn()->setOther(0);
    }
}

ObserverView::~ObserverView(){

    ui->Detach(this);

}
