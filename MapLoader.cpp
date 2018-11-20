#include "MapLoader.h"

using namespace std;

int numberOfCountries;
int numberOfContinents;

ifstream openFile(string input, vector <Continent> &continents) {

	// Opening the stream to read a file.
	ifstream readMap;

	// Checking if the file exist or not.
	readMap.open(input);
	if (!readMap) {
		cout << "Unable to open file" << endl;
        exit(1);
	}
	// Returning the file stream
	return readMap;
}

ifstream verify(ifstream readMap, string file, vector <Continent> &continents) {

    int condition = 3, counter = 0;
    string check[3] = { "[Map]","[Continents]","[Territories]" };

    while (condition > 0 && !readMap.eof()) {
        getline(readMap, file, '\n');
        if (check[counter].compare(file.substr(0, file.find("]") + 1)) == 0) {
            // This loop is for creating continent objects
            while (check[counter].compare(check[1]) == 0) {
                getline(readMap, file, '\n');
                string oneLine = file;

                //finds the line with '=' at index 1 or greater, otherwise it marks the end of the continent
                char charLine[oneLine.length()];
                strcpy(charLine, oneLine.c_str());
                char find = '=';

                const char *ptr = strchr(charLine, find);
                long index;
                if(ptr) {
                    index = ptr - charLine;
                }
                else{
                    index = -1;
                }


                if (index<1){
                    break;
                }
                else {
                    string continentName = oneLine.substr(0, index);
                    int value = stoi(oneLine.substr(index + 1));
                    continents.push_back(Continent(value, continentName));
                    numberOfContinents++;
                }
            }
            condition--; // For the while loop
            counter++;   // For the check array
        }
    }

    if (condition != 0) {
        cout << "Invalid Map file format. GoodBye" << endl;
        //system("Pause");
        exit(1);
    }

    return readMap;
}

vector <Info> MapLoader(string fileName, vector <Continent> &continents) {

	// Creating variables:

	string file;
	string head;
	string tail;
	string oneLine;


	/* Will open file check whether its a vaild file and if its a vaild map at the same time.
	   ifstream readMap = verify(openFile(input), file);
	   Will do 3 things:
	   1) Open up the reader stream
	   2) Check if the file is exist.
	   3) Check if the file is a vaild map file
	*/

	ifstream readMap = verify(openFile(fileName, continents), file, continents);


	// Creating more variables:
	int cUpdate = 0;
	int flag = 1;
	int index = 0;
	int counter = 0;
	vector <Info> map;

    bool prevSpace = false; //just a marker in case the previous line was a space; so several empty lines do not crash the program
    
	// Start reading the file that is important 
	while (!readMap.eof()) {
		getline(readMap, file, '\n'); // Reads one line from the file at a time
		oneLine = file; // Temporary variable called oneLine
		head = "Start"; // Initialized for the next while  
		tail = "End";   // Initialized for the next while

        if (oneLine.length()<8) { //at the very least 8 chars
            if(!prevSpace)
                cUpdate++;
            prevSpace = true; // now if there is a space right after, cUpdate will not be increased
            
            continue;
            
        }
        else{
            prevSpace = false;
        }
        
        while (head.compare(tail) != 0) { // This while loop splits the string.

			head = oneLine.substr(0, oneLine.find(","));
			tail = oneLine.substr(oneLine.find(",") + 1);

			// This flag is to create the Info class. 
			// The if condition is true once pure loop

			if (flag) {
				map.push_back(Info(head));
				numberOfCountries++;
				flag = 0;

			}
            if (counter == 1){
                int result = stoi(head);
                map[index].setGUIx(result);
            }
            
            if (counter == 2){
                int result = stoi(head);
                map[index].setGUIy(result);
            }
            
			if (counter == 3) {
				for (int i = 0; i < numberOfContinents; i++) {
					if (head.compare(continents.at(i).getContinentName()) == 0) {
						map[index].setContinent(continents.at(i));
						map[index].getContinent2().setCountriesInContinent(map[index].getCountry());
						continents.at(cUpdate).setCountriesInContinent(map[index].getCountry());
					}
				}
			}
			if (counter > 3)
				map[index].setListOfCountries(head);

			oneLine = tail;
			counter++;
		}

		index++;
		flag = 1;
		counter = 0;

	}
	readMap.close();

	if (duplicates(map) == 0) {
		cout << "Invalid Map" << endl;
		exit(1);
	}


	return map;
}

bool duplicates(vector <Info> any) {
	for (int i = 0; i < any.size(); i++) {
		for (int j = i + 1; j < any.size(); j++) {
			if (any[i].getCountry() == any[j].getCountry()) {
				if (any[i].getContinent() != any[j].getContinent())
					return 0;
			}
		}
	}
	return 1;
}
