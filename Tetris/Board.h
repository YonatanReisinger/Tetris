#ifndef __BOARD_H__
#define __BOARD_H__

// Imports ->
#include "Point.h"
#include "gameConfig.h"
#include <iostream>
using namespace std;
// <- Imports

// Macros ans enums->
#define BORDER_SYMBOL '*'
#define EMPTY ' '
enum Borders {TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT};
// <- Macros and enums

class Board{
private:
	Point borders[4];
	// Shape** activeShapes;
	bool isHeightValid(Point borders[4]);
	bool isWidthValid(Point borders[4]);
	void printHorizontalLine(Point& leftEnd, Point& rightEnd, char symbol = '*');
	void printVerticalLine(Point& topEnd, Point& bottomEnd, char symbol = '*');

public:
	Board(const Point& topLeft, const Point& topRight, const Point& BottomLeft, const Point& BottomRight);
	Board(const Board* other);
	bool setBorders(const Point& topLeft, const Point& topRight, const Point& BottomLeft, const Point& BottomRight);
	Point* getBorders();
	void print();
	void clear();
};

#endif // Board.h