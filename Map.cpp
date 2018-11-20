#include "Map.h"

	// Mutator Methods	

void Map::setCountriesMap(const vector<Country *> &countriesMap) {
	Map::countriesMap = countriesMap;
}

// Accessor Methods

const vector<Country *> & Map::getCountriesMap() {
	return countriesMap;
}

int Map::getTotalNumberOfCountries(){
    int numberOfCountries = 0;

    for(int i=0; i<countriesMap.size(); i++){
        numberOfCountries++;
    }

    return numberOfCountries;
}

// Other Methods

// Add one country to the map
void Map::addCountry(Country *country) {
	for (Country *c : countriesMap) {
		if (c->getCountryName() == country->getCountryName())
			return;
	}
	countriesMap.push_back(country);
}

// Creates connections between two countries and checks if the country already exists
// Duplicate country names get discarded
void Map::addAdjacentCountry(Country *c1, Country *c2) {
	vector<Country*> adjCountries = c1->getAdjCountries();
	bool flag = false;
	for (int i = 0; i < adjCountries.size(); i++) {
		if (adjCountries[i]->getCountryName() == c2->getCountryName()) {
			flag = true;
			break;
		}
	}
	if (!flag) {
		c1->getAdjCountries().push_back(c2);
	}
	adjCountries = c2->getAdjCountries();
	flag = false;
	for (int i = 0; i < adjCountries.size(); i++) {
		if (adjCountries[i]->getCountryName() == c1->getCountryName()) {
			flag = true;
			break;
		}
	}
	if (!flag) {
		c2->getAdjCountries().push_back(c1);
	}
}

// Print Methods

void Map::printAdjacencyListofCountries() {
	cout << "Adjacency list of Countries:" << endl;
	for (Country *c : countriesMap) {
		cout << c->getCountryName() << " : ";
		for (Country *c1 : c->getAdjCountries()) {
			cout << c1->getCountryName() << " ";
		}
		cout << endl;
	}
	cout << endl;
}

// DFS Methods (Graph Traversal)

// Uses DFS algorithm to check if COUNTRIES are fully connected
// will have to implement this same algo for continents -> TO DO.
bool Map::isValid() {
    vector<bool> visited(countriesMap.size(), false); // set entire vector to false
    dfs(0, visited);
    
    for (int i = 0; i < countriesMap.size(); i++) {
        cout << countriesMap.at(i)->getCountryName() << " is ";
        if (!visited[i]) {

        cout << "not visited" <<endl;
        cout << "The graph is not fully connected, It is an invalid map!" << endl;
        return false;
        }
        
        else{
        cout << "visited" << endl;
        }
    }
    
    cout << "The graph is fully connected, It is a valid map!" << endl;
    return true;
}


// DFS Algorithm to check for fully connected graph (Only checks countries as of now)
void Map::dfs(int u, vector<bool> &visited) {
    visited[u] = true;
    for (Country *c : countriesMap[u]->getAdjCountries()) {
        for (int j = 0; j < countriesMap.size(); j++) {
            if (countriesMap[j]->getCountryName() == c->getCountryName()) {
                if (!visited[j]) {
                    dfs(j, visited);
                }
                break;
            }
        }
    }
}




