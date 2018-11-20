#pragma once
#include <string>
#include <vector>

class Continent {
	
// Methods
public:
	Continent();
	Continent(int value, std::string name);
	void setContinentValue(int value);
	void setContinentName(std::string cn);
	void setCountriesInContinent(std::string countries);
	int getContinentValue();
	std::string getContinentName();
	std::string getCountriesInContinent(int index);
	int getSizeOfCountriesInContinent();
	std::vector <std::string> getListOfCountries();
	~Continent();

// Attributes

private:
	int continentValue;
	std::string continentName;
	std::vector <std::string> countriesInContinent;
	
};

