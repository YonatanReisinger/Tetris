#ifndef __BOARD_H__
#define __BOARD_H__

// Imports ->
#include "Point.h"
#include <iostream>
using namespace std;
// <- Imports

// Macros ans enums->
#define HEIGHT 18
#define WIDTH 12
#define BORDER_SYMBOL '*'
enum Borders {TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT};
// <- Macros and enums

class Board{
private:
	Point borders[4];

	bool isHeightValid(Point borders[4]);
	bool isWidthValid(Point borders[4]);
	void printHorizontalLine(Point& leftEnd, Point& rightEnd, char symbol = '*');
	void printVerticalLine(Point& topEnd, Point& bottomEnd, char symbol = '*');
public:
	Board(const Point& topLeft = Point(0, 0),
		const Point& topRight = Point(WIDTH + 1, 0),
		const Point& BottomLeft = Point(0, HEIGHT + 1),
		const Point& BottomRight = Point(WIDTH + 1, HEIGHT + 1));
	Board(const Board* other);
	bool setBorders(const Point& topLeft = Point(0, 0),
		const Point& topRight = Point(WIDTH + 1, 0),
		const Point& BottomLeft = Point(0, HEIGHT + 1),
		const Point& BottomRight = Point(WIDTH + 1, HEIGHT + 1));
	Point* getBorders();
	void print();
	bool clear();
};

#endif // Board.h