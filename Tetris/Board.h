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
enum Borders {TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT} ;
// <- Macros and enums

class Board{
private:
	Point borders[4];
	Point gameBoard[GameConfig::HEIGHT][GameConfig::WIDTH];
	Shape activeShapes[GameConfig::HEIGHT * GameConfig::WIDTH];
	size_t numOfActiveShapes;

	// Shape** activeShapes;
	bool setBorders(const Point& topLeft, const Point& topRight, const Point& bottomLeft, const Point& bottomRight);
	bool setGameBoard(char boardSymbol);
	inline bool isHeightValid(Point borders[4]) const;
	inline bool isWidthValid(Point borders[4]) const;
	void printFrame() const;
	void printHorizontalLine(Point& leftEnd, Point& rightEnd, char symbol = GameConfig:: BORDER_SYMBOL) const;
	void printVerticalLine(Point& topEnd, Point& bottomEnd, char symbol = GameConfig:: BORDER_SYMBOL) const;
	bool isPointInBoard(const Point& point) const;
	bool isPointFull(const Point& point) const;
	bool isRowFull(short int i) const;
	void clearShapeFromGameBoard(Shape& shape);
	void removeActiveShapeFromArr(Shape& shape, int shapeInd);
	bool canActiveShapeDrop(const Shape& shape) const;
	bool canShapeRotate(const Shape& shape, ShapeMovement movement);
	void clearPointsFromActiveShapes(short int i);
	void insertShapeToArr(const Shape& newShape);
public:
	bool setRow(short int i, char boardSymbol);
	Board(const Point& topLeft, const Point& topRight, const Point& bottomLeft, const Point& bottomRight);
	inline Point* getBorders() { return borders; };
	bool setNumOfShapes(size_t size);
	bool setPointInGameBoard(const Point& point);
	bool setShapeInGameBoard(const Shape& shape, bool isShapeNew);
	void print() const;
	void printGameBoard() const;
	void clear();
	inline bool clearRow(short int i) { return setRow(i, EMPTY); };
	int clearFullRows();
	bool canPointMove(Point point, Directions direction) const;
	inline Point getStartingPoint() const { return gameBoard[0][GameConfig::WIDTH / 2]; };
	bool isShapeInBoard(const Shape& shape) const;
	bool canShapeMove(const Shape& shape, ShapeMovement movement) const;
	void dropActiveShapes();
	bool isShapeStuck(const Shape& shape) const;
	bool canSetShapeInGameBoard(const Shape& shape) const;
};

#endif // Board.h