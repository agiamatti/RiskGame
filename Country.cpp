#include "Country.h"
#include "Player.h"

    // Constructor

    Country::Country() {
    }

    Country::Country(const string &countryName, Player* player, int armyValue, const string &continent, int GUIx, int GUIy):
        countryName(countryName),
        armyValue(armyValue),
        continent(continent),
        GUIx(GUIx),
        GUIy(GUIy),
        flag(0){
        setPlayer(player); //need to use setter to add to player's Countries Owned list too
    }


    // Accessor Methods

    const string & Country::getCountryName() {
        return countryName;
    }

    Player* Country::getPlayer() {
        return player;
    }


    int Country::getArmyValue() {
        return armyValue;
    }


    const string & Country::getContinent(){
        return continent;
    }

    vector<Country *> & Country::getAdjCountries() {
        return adjCountries;
    }

    Country* Country::getNeighbor(int index) {
        return adjCountries[index];
    }

    int Country::getFlag(){
        return flag;
    }

    int Country::getGUIx(){
        return GUIx;
    }

    int Country::getGUIy(){
        return GUIy;
    }



    // Mutator Methods

    void Country::setCountryName(const string &countryName) {
        Country::countryName = countryName;
    }

    void Country::setPlayer(Player* player) {
        Country::player = player;
        if (player != NULL) {
            player->addCountriesOwned(this); //adds it to player's list too
        }
    }

    void Country::setPlayerNR(Player* player) {
        Country::player = player;			// does NOT add is too player's list as it is the one calling this method
    }

    void Country::setArmyValue(int armyValue) {
        Country::armyValue = armyValue;
    }

    void Country::setContinent(const string &continent) {
        Country::continent = continent;
    }

    void Country::setAdjCountries(const vector<Country *> &adjCountries) {
        Country::adjCountries = adjCountries;
    }

    void Country::setFlag(int x){
        Country::flag = x;
    }

    void Country::setGUIx(int x){
        GUIx = x;
    }

    void Country::setGUIy(int y){
        GUIy = y;
    }

    // Other Methods

    void Country::addNeighborCountry(Country* country) {
        adjCountries.push_back(country);
    }


    //checks if a country is adjacent
    bool Country::isNeighbor(Country* country) {
        if (adjCountries.empty()) {
            return false;
        }
        for (int i = 0; i < adjCountries.size(); i++) {
            if (adjCountries[i]->getCountryName() == country->getCountryName()) {
                return true;
            }
        }
        return false;
    }

    //printing method
    void Country::printCountryDetails() {
        cout << "Country: " << countryName << endl;
        cout << "Continent: " << continent << endl;
        cout << "Player owner: " << player->getPlayerName() << endl;
        cout << "Army Value: " << armyValue << endl;
        cout << "GUI x and y values: " <<GUIx << "  " << GUIy <<endl;
        cout << "Adjacent countries are: ";
        for (Country *c : adjCountries) {
            cout << c->getCountryName() << " ";
        }
        cout << endl;
    }

    Country::~Country()
    {
    }
