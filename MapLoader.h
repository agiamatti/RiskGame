#pragma once

#include <string>
#include <vector> 
#include <fstream>
#include <iostream>

#include "Info.h"

using namespace std;

// Helper Functions 

ifstream openFile(string input, vector <Continent> &continents);
vector <Info> MapLoader(string fileName, vector <Continent> &continents);
ifstream verify(ifstream readMap, string file, vector <Continent> &continents);
bool duplicates(vector <Info> any);
