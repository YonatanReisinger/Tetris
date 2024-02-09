#ifndef __GLOBAL_FUNCTIONS_H__
#define __GLOBAL_FUNCTIONS_H__


// Imports ->
#include <iostream>
using namespace std;
#include <string>
#include "Game.h"
class Game;
// <- Imports

// Macros ans enums->
#define LEFT_ARROW 75
#define RIGHT_ARROW 77
// <- Macros and enums

void printWelcomeMessage();
void printChoiceError();
void clearScreen();
void clearCin();
void printColorOption();
void showConsoleCursor(bool showFlag);

#endif // global_functions.h
