#ifndef __GLOBAL_FUNCTIONS_H__
#define __GLOBAL_FUNCTIONS_H__


// Imports ->
#include <iostream>
using namespace std;
#include "Game.h"
// <- Imports

// Macros ans enums->

// <- Macros and enums

void printMenu(GameStatus gameStatus = GameStatus:: PLAYING);
void printChoiceError();
void printInstructionsAndKeys(const char* instructions, const char* keys);

#endif // global_functions.h
