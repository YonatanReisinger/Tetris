#ifndef __BOARD_H__
#define __BOARD_H__

// Imports ->
#include "Point.h"
#include "Shape.h"
#include "gameConfig.h"
#include <iostream>
using namespace std;
// <- Imports

// Macros ans enums->
enum Borders {TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT};
// <- Macros and enums

class Board{
private:
	Point borders[4];
	Point gameBoard[GameConfig:: HEIGHT][GameConfig:: WIDTH];
	//the maximum amout of shapes is that all the board is full of shapes that transformed into points
	Shape activeShapes[GameConfig::HEIGHT * GameConfig::WIDTH];
	short int numOfActiveShapes;

	// Shape** activeShapes;
	bool setBorders(const Point& topLeft, const Point& topRight, const Point& bottomLeft, const Point& bottomRight);
	bool setGameBoard(char boardSymbol);
	inline bool isHeightValid(Point borders[4]);
	inline bool isWidthValid(Point borders[4]);
	void printFrame();
	void printHorizontalLine(Point& leftEnd, Point& rightEnd, char symbol = GameConfig:: BORDER_SYMBOL);
	void printVerticalLine(Point& topEnd, Point& bottomEnd, char symbol = GameConfig:: BORDER_SYMBOL);
	bool isPointInBoard(const Point& point);
	bool isPointFull(const Point& point);
	bool isRowFull(short int i);
	void clearShapeFromGameBoard(Shape& shape);

public:
	bool setRow(short int i, char boardSymbol);
	Board(const Point& topLeft, const Point& topRight, const Point& bottomLeft, const Point& bottomRight);
	//Board(const Board* other);
	Point* getBorders();
	bool setNumOfShapes(short int num);
	bool setPointInGameBoardByInd(short int i, short int j, char symbol);
	bool setPointInGameBoard(const Point& point);
	bool setShapeInGameBoard(const Shape& shape);
	void print();
	void printGameBoard();
	void clear();
	bool clearRow(short int i);
	int clearFullRows();
	bool isOverflowing();
	bool canPointMove(Point point, Directions direction);
	bool canShapeChangeDirection(const Shape& shape, Directions direction);
	Point getStartingPoint();
	bool isShapeInBoard(const Shape& shape);
	bool canShapeMove(const Shape& shape, ShapeMovement movement);
	bool canShapeDrop(Shape& shape);
	void dropActiveShapes();
};

#endif // Board.h