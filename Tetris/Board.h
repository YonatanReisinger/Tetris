#ifndef __BOARD_H__
#define __BOARD_H__

// Imports ->
#include "Point.h"
#include "gameConfig.h"
#include <iostream>
using namespace std;
// <- Imports

// Macros ans enums->
#define EMPTY ' '
enum Borders {TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT};
// <- Macros and enums

class Board{
private:
	Point borders[4]; // maybe change to dynamic after ??????????
	char gameBoard[GameConfig:: HEIGHT][GameConfig:: WIDTH];

	// Shape** activeShapes;
	inline bool isHeightValid(Point borders[4]);
	inline bool isWidthValid(Point borders[4]);
	void printFrame();
	void printHorizontalLine(Point& leftEnd, Point& rightEnd, char symbol = GameConfig:: BORDER_SYMBOL);
	void printVerticalLine(Point& topEnd, Point& bottomEnd, char symbol = GameConfig:: BORDER_SYMBOL);
	bool setRow(short int i,char boardSymbol);

public:
	Board(const Point& topLeft, const Point& topRight, const Point& bottomLeft, const Point& bottomRight);
	Board(const Board* other);
	bool setBorders(const Point& topLeft, const Point& topRight, const Point& bottomLeft, const Point& bottomRight);
	Point* getBorders();
	bool setGameBoard(char boardSymbol);
	char(*getGameBoard())[GameConfig::WIDTH]; 
	void print();
	void printGameBoard();
	void clear();
	bool clearRow(short int i);
	bool isOverflowing();
};

#endif // Board.h