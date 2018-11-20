#pragma once
#include <iostream>
#include <time.h>

class Dice {
private:
	float face_1; //Number of times each faces of the dice are rolled, to calculate the % later.
	float face_2;
	float face_3;
	float face_4;
	float face_5;
	float face_6;

	void sortArr(int rolls[]); //Sorts the array from bigger to smaller number.
public:
	Dice(); //Default constructor.
	int* roll(int dices); //Rolls 'dices' number of dices.
	float getPerc(int face); //Returns the % of times 'face' has been rolled.
	static void showArr(int rolls[]);
};
