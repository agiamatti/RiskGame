#include "Dice.h"

using std::cout;
using std::cin;

Dice::Dice() {
	face_1 = 0;
	face_2 = 0;
	face_3 = 0;
	face_4 = 0;
	face_5 = 0;
	face_6 = 0;
	srand(time(NULL)); //Sets a random seed.
}

int* Dice::roll(int dice) {
	while (!(dice >= 1 && dice <= 3)) { //If the number of dice is invalid, asks again until the number is valid.
		cout << "Invalid number of dice, try again. ";
		cin >> dice;
	}

	int* rolls = new int[3]; //Creates a new array for the rolls.

	for (int i = 0; i < dice; i++) { //Loop for each dice rolled.
		switch (rand() % 6 + 1) { //Selects a random number between 1 and 6 and add it to the array, then increment by one the number of times that face has been rolled.
		case 1:
			rolls[i] = 1;
			face_1++;
			break;
		case 2:
			rolls[i] = 2;
			face_2++;
			break;
		case 3:
			rolls[i] = 3;
			face_3++;
			break;
		case 4:
			rolls[i] = 4;
			face_4++;
			break;
		case 5:
			rolls[i] = 5;
			face_5++;
			break;
		case 6:
			rolls[i] = 6;
			face_6++;
			break;
		default: //This should never happen, but if something goes wrong this message will be printed.
			cout << "Error, a value outside of the range (1-6) has been rolled.\n";
			break;
		}
	}
	if (dice < 3) {
		for (int i = dice; i < 3; i++) { //If there was less than 3 dice rolled, make the remaining "dice" roll a 0.
			rolls[i] = 0;
		}
	}

	sortArr(rolls); //Sorts the array before returning it.
	return rolls;

}

void Dice::sortArr(int rolls[]) {
	int temp;
	for (int i = 0; i < 3 - 1; i++) { //2 nested for loops in which we go through ever element of the array and compare it the the next one(s). If it's bigger they switch, if not they stay, resulting in a sorted array.
		for (int j = i + 1; j < 3; j++) {
			if (rolls[i] < rolls[j]) {
				temp = rolls[i];
				rolls[i] = rolls[j];
				rolls[j] = temp;
			}
		}
	}
}

float Dice::getPerc(int face) { //Returns the % of times the specific face has been rolled.
	int total = face_1 + face_2 + face_3 + face_4 + face_5 + face_6; //Calculate the total of rolls made.
	switch (face) { //Depending on the face chosen, calculates the %.
	case 1:
		return ((face_1 / total) * 100);
		break;
	case 2:
		return ((face_2 / total) * 100);
		break;
	case 3:
		return ((face_3 / total) * 100);
		break;
	case 4:
		return ((face_4 / total) * 100);
		break;
	case 5:
		return ((face_5 / total) * 100);
		break;
	case 6:
		return ((face_6 / total) * 100);
		break;
	default: //If the user entered a value that is not between 1 and 6 this message is printed.
		cout << "Invalid value.";
		return -1;
		break;
	}
	
}

 void Dice::showArr(int rolls[]) { //Method to show all the rolls. Loops through the array and shows the number.
	for (int i = 0; i < 3; i++) {
		if (rolls[i] != 0) {
			cout << rolls[i];
			cout << " ";
		}
	}
	cout << " ";
}
