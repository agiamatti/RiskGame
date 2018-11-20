#include "ObserverView.h"

ObserverView::ObserverView(){
}

ObserverView::ObserverView(RiskGUI* x)
{
    _subject = x;
    _subject->Attach(this);

}

void ObserverView::Update() {
    //Called by Notify() when state of Subject changes
    display();
};

void ObserverView::display() {
    cout<<"beter\n";
    _subject->update();
//    if(_subject->getPlayerAtCurrentTurn()!=NULL){
//        int clear = 0;

//            // =================================== Reinforce =================================== //

//            if (_subject->getPlayerAtCurrentTurn()->getFlag() == 9) {
//                string bonus = _subject->getPlayerAtCurrentTurn()->getPlayerName() + " has the following continents: ";
//                if (_subject->getPlayerAtCurrentTurn()->getOther() == 0) {
//                bonus = bonus + "none.";
//                }
//                cout << bonus << endl;
//            }


//            if (_subject->getPlayerAtCurrentTurn()->getFlag() == 1) {
//                cout << _subject->getPlayerAtCurrentTurn()->getPlayerName() << "'s reinforcement phase." <<endl;
//            }

//            if (_subject->getPlayerAtCurrentTurn()->getFlag() == 2) {
//                cout << _subject->getPlayerAtCurrentTurn()->getPlayerName() << " is reinforcing " << _subject->getPlayerAtCurrentTurn()->getTargetedCountry().getCountryName() << " with " << _subject->getPlayerAtCurrentTurn()->getOther() << " reinforcements. New army value: " << _subject->getPlayerAtCurrentTurn()->getTargetedCountry().getArmyValue() << endl;
//            }

//            // =================================== Fortify =================================== //

//            if (_subject->getPlayerAtCurrentTurn()->getFlag() == 3) {
//                cout << _subject->getPlayerAtCurrentTurn()->getPlayerName() << "'s fortification phase." << endl;
//            }

//            if (_subject->getPlayerAtCurrentTurn()->getFlag() == 4) {
//                cout << _subject->getPlayerAtCurrentTurn()->getPlayerName() << " is fortifying " << _subject->getPlayerAtCurrentTurn()->getTargetedCountry().getCountryName() << " with " << _subject->getPlayerAtCurrentTurn()->getOther() << " armies from "
//                    << _subject->getPlayerAtCurrentTurn()->getSourceCountry().getCountryName() << ". " << _subject->getPlayerAtCurrentTurn()->getSourceCountry().getCountryName() << " army value: " << _subject->getPlayerAtCurrentTurn()->getSourceCountry().getArmyValue() <<
//                    " " << _subject->getPlayerAtCurrentTurn()->getTargetedCountry().getCountryName() << " army value: " << _subject->getPlayerAtCurrentTurn()->getTargetedCountry().getArmyValue() << endl;
//            }

//            // =================================== Attack =================================== //

//            if (_subject->getPlayerAtCurrentTurn()->getFlag() == 5) {
//                cout << _subject->getPlayerAtCurrentTurn()->getPlayerName() <<  "'s attack phase" << endl;
//            }

//            if (_subject->getPlayerAtCurrentTurn()->getFlag() == 6) {
//               // cout << _subject->getPlayerAtCurrentTurn()->getPlayerName() << " is attacking " << _subject->getPlayerAtCurrentTurn()->getTargetedCountry().getPlayer()->getPlayerName() << "'s " << _subject->getPlayerAtCurrentTurn()->getTargetedCountry().getCountryName() << " from " << _subject->getPlayerAtCurrentTurn()->getSourceCountry().getCountryName() << "!" << endl;

//            }

//            if (_subject->getPlayerAtCurrentTurn()->getFlag() == 7) {
//                cout << _subject->getPlayerAtCurrentTurn()->getPlayerName() << "'s " << _subject->getPlayerAtCurrentTurn()->getSourceCountry().getCountryName() << " with army value " << _subject->getPlayerAtCurrentTurn()->getSourceCountry().getArmyValue() << " is attacking " << _subject->getPlayerAtCurrentTurn()->getTargetedCountry().getPlayer()->getPlayerName() << "'s " + _subject->getPlayerAtCurrentTurn()->getTargetedCountry().getCountryName() << " with army value " << _subject->getPlayerAtCurrentTurn()->getTargetedCountry().getArmyValue() << "." << endl;

//            }

//            if (_subject->getPlayerAtCurrentTurn()->getFlag() == 8) {
//                _subject->getPlayerAtCurrentTurn()->setPercentWorldOwned(_subject->getPlayerAtCurrentTurn()->getOther());
//            }

//            // ============================== Resetting some variables & Clearing  ============================== //

//            _subject->getPlayerAtCurrentTurn()->setFlag(0);
//            _subject->getPlayerAtCurrentTurn()->setOther(0);
//    }
};

ObserverView::~ObserverView()
{

    _subject->Detach(this);

}
