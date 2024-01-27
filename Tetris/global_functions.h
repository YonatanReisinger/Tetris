#ifndef __GLOBAL_FUNCTIONS_H__
#define __GLOBAL_FUNCTIONS_H__


// Imports ->
#include <iostream>
using namespace std;
#include <string>
#include "Game.h"
// <- Imports

// Macros ans enums->
#define LEFT_ARROW 75
#define RIGHT_ARROW 77
// <- Macros and enums

void printMenu(GameStatus gameStatus = GameStatus:: PLAYING) ;
void printWelcomeMessage();
void printChoiceError();
void printInstructionsAndKeys();
void clearScreen();
void printWinner(Game& game);
void clearCin();
void printInstructions();
void printKeys();
void printColorOption();
void showConsoleCursor(bool showFlag);

#endif // global_functions.h
