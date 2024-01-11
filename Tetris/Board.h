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
	Point gameBoard[GameConfig:: HEIGHT][GameConfig:: WIDTH];

	// Shape** activeShapes;
	bool setBorders(const Point& topLeft, const Point& topRight, const Point& bottomLeft, const Point& bottomRight);
	bool setGameBoard(char boardSymbol);
	inline bool isHeightValid(Point borders[4]);
	inline bool isWidthValid(Point borders[4]);
	void printFrame();
	void printHorizontalLine(Point& leftEnd, Point& rightEnd, char symbol = GameConfig:: BORDER_SYMBOL);
	void printVerticalLine(Point& topEnd, Point& bottomEnd, char symbol = GameConfig:: BORDER_SYMBOL);
	bool isPointInBoard(Point& point);

public:
	bool setRow(short int i, char boardSymbol);
	Board(const Point& topLeft, const Point& topRight, const Point& bottomLeft, const Point& bottomRight);
	//Board(const Board* other);
	Point* getBorders();
	bool setPointInGameBoardByInd(short int i, short int j, char symbol);
	bool setPointInGameBoard(Point& point);
	void print();
	void printGameBoard();
	void clear();
	bool clearRow(short int i);
	bool isOverflowing();
	bool isPointFull(Point& point);
};

#endif // Board.h