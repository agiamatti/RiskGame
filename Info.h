#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Continent.h"
using namespace std;

class Info {

    // Methods

public:
    Info();
    Info(string country);
    ~Info();

    //setters
    void setCountry(string country);
    void setContinent(Continent c);
    void setNumberOfTotalCountries(int x);
    void setNumberOfTotalContinents(int x);
    void setListOfCountries(string countries);
    void setGUIx(int x);
    void setGUIy(int y);

    //getters
    string getCountry();
    int getNumberOfTotalCountries();
    int getNumberOfTotalContinents();
    string getContinent();
    Continent getContinent2();
    string getCountriesFromList(int index);
    vector <string> getListOfCountries();
    int SizeOfListOfCountries();
    int getGUIx();
    int getGUIy();


    // Attributes

private:
    int numberOfTotalCountries;
    int numberOfTotalContinents;
    string m_Country;
    Continent m_Continent;
    vector <string> listOfCountries;
    int GUIx;
    int GUIy;
};



