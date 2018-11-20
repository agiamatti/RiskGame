#include "Continent.h"

//int Continent::continentCounter;

//  Default Constructor
Continent::Continent() : continentValue(0), continentName("Empty"), countriesInContinent() {
	
}

// Parameterized Constructor
Continent::Continent(int value, std::string name) : continentValue(value), continentName(name), countriesInContinent() {
	
}

// Mutator Methods
void Continent::setContinentValue(int value) {
	//cout << "setcontinentValue is being called" << endl;
	continentValue = value;
}

void Continent::setContinentName(std::string cn) {
	//cout << "setContinentName is being called" << endl;
	continentName = cn;
}

void Continent::setCountriesInContinent(std::string countries) {
	//cout << "setCountriesInContinent is being called" << endl;
	countriesInContinent.push_back(countries);
}

// Accessor Methods

int Continent::getContinentValue() {
	//cout << "getContinentValue is being called" << endl;
	return continentValue;
}

std::string Continent::getContinentName() {
	//cout << "getContinentName is being called" << endl;
	return continentName;
}

std::string Continent::getCountriesInContinent(int index) {
	//cout << "getCountriesInContinent is being called" << endl;
	return countriesInContinent[index];
}

int Continent::getSizeOfCountriesInContinent()
{
	return countriesInContinent.size();
}


std::vector <std::string> Continent::getListOfCountries() {
	//cout << ":getListOfCountries is being called" << endl;
	return countriesInContinent;
}

// Destructor
Continent::~Continent(){
	//cout << "Continent Object is being deleted" << endl;
}
