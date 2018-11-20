#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <time.h>
#include "Country.h"

class Map
{

public:

	// Methods 
    int getTotalNumberOfCountries();
	void setCountriesMap(const vector<Country *> &countriesMap);
	const vector<Country *> &getCountriesMap();
	void addCountry(Country *country);
	void addAdjacentCountry(Country *c1, Country *c2);
	void printAdjacencyListofCountries();
	bool isValid();
	void dfs(int u, vector<bool> &visited);

	// Attributes

private:
	vector<Country*> countriesMap;
};
