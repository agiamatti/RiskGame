#pragma once
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Player;
class Country{

public:
    //constructors and destructors
    Country();
    Country(const string &countryName, Player* player, int armyValue, const string &continent, int GUIx, int GUIy);
    const string &getCountryName();
    ~Country();

    //getters
    Player* getPlayer();
    int getArmyValue();
    vector<Country *> &getAdjCountries();
    Country* getNeighbor(int index);
    const string &getContinent();
    int getFlag();
    int getGUIx();
    int getGUIy();

    //setters
    void setCountryName(const string &countryName);
    void setPlayer(Player* player);
    void setPlayerNR(Player* player); //to be used exclusively by Player::addCountriesOwned()
    void setFlag(int x);
    void setArmyValue(int armyValue);
    void setContinent(const string &continent);
    void setAdjCountries(const vector<Country *> &adjCountries);
    void setGUIx(int x);
    void setGUIy(int y);


    void addNeighborCountry(Country* country);
    bool isNeighbor(Country* country);
    void printCountryDetails();


private:
    string countryName;
    Player* player;
    int armyValue;
    string continent;
    vector <Country*> adjCountries;
    int flag;
    int GUIx;
    int GUIy;

};
