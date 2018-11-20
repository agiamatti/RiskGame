#include "Info.h"

using namespace std;


//  Default Constructor

Info::Info() {
    //cout << "Using Info Default Constructor" << endl;
    m_Country;
    m_Continent;
    listOfCountries;

}

// Parameterized Constructor

Info::Info(string country) {
    //cout << "Using Info Parameterized Constructor" <<  m_Country << endl;
    m_Country = country;
    m_Continent;
    listOfCountries;
}

// Mutator Methods

void Info::setCountry(string country) {
    //cout << "setCountry is being called" << endl;
    m_Country = country;
}

void Info::setContinent(Continent c) {
    //cout << "setCountry is being called" << endl;
    m_Continent = c;
}

void Info::setNumberOfTotalCountries(int x)
{
}

void Info::setNumberOfTotalContinents(int x)
{
}


void Info::setListOfCountries(string countries) {
    //cout << "setListOfCountries is being called" << endl;
    listOfCountries.push_back(countries);
}


void Info::setGUIy(int y){
    GUIy = y;
}


void Info::setGUIx(int x){
    GUIx = x;
}


// Accessor Methods

string Info::getCountry() {
    //cout << "getCountry is being called" << endl;
    return m_Country;
}

int Info::getNumberOfTotalCountries()
{
    return 0;
}

int Info::getNumberOfTotalContinents()
{
    return 0;
}

string Info::getContinent() {
    //cout << "getCountry is being called" << endl;
    return m_Continent.getContinentName();
}

Continent Info::getContinent2() {
    //cout << "getCountry is being called" << endl;
    return m_Continent;
}


string Info::getCountriesFromList(int index) {
    //cout << "getCountries is being called" << endl;
    return listOfCountries[index];
}

vector <string> Info::getListOfCountries() {
    //cout << ":getListOfCountries is being called" << endl;
    return listOfCountries;
}

// Other Useful Methods

int Info::SizeOfListOfCountries() {
    //cout << "SizeOfListOfCountries is being called" << endl;
    return listOfCountries.size();
}

int Info::getGUIx(){
    return GUIx;
}

int Info::getGUIy(){
    return GUIy;
}

// Destructor
Info::~Info() {
    //cout << "Info Object is being deleted" << endl;
}
