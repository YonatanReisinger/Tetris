#ifndef __GLOBAL_FUNCTIONS_H__
#define __GLOBAL_FUNCTIONS_H__


// Imports ->
#include <string>
#include "Game.h"
class Game;
// <- Imports

// Macros ans enums->
#define LEFT_ARROW 75
#define RIGHT_ARROW 77
// <- Macros and enums

void printChoiceError();
void clearScreen();
void clearCin();
void printColorOption();
void showConsoleCursor(bool showFlag);
ostream& operator<<(std::ostream& os, Choice choice);
void prepareCpuVsCpu(Player*& cpu1, Player*& cpu2, const Board& board1, const Board& board2);
void prepareHumanVsCpu(Player*& cpu2, const Board& board2);

#endif // global_functions.h
