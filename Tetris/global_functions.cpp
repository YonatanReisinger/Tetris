#include "global_functions.h"

void printMenu(GameStatus gameStatus)
{
	cout << "Please enter your choice:\n" << "(1) Start a new game\n";
	if (gameStatus == GameStatus:: PAUSED)
	{
		cout << "(2) Continue a paused game\n";
	}
	cout << "(8) Present instructions and keys\n" << "(9) EXIT\n";
}

void printChoiceError()
{
	cout << "Wrong choice! Please Try again" << endl;
}

void printInstructionsAndKeys(const char* instructions, const char* keys)
{
	cout << "the instructions are: " << instructions << endl << "the keyss are: " << keys << endl;
}