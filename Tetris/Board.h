#ifndef __BOARD_H__
#define __BOARD_H__

// Imports ->
#include "Point.h"
#include "Shape.h"
#include "gameConfig.h"
#include <iostream>
using namespace std;
// <- Imports

// Macros and typedefs->
typedef const Point (*gameBoardPointer)[GameConfig::WIDTH];
// <- Macros and typedefs

class Board{
private:
	Point borders[4];
	Point gameBoard[GameConfig::HEIGHT][GameConfig::WIDTH];
	Shape activeShapes[GameConfig::HEIGHT * GameConfig::WIDTH];
	size_t numOfActiveShapes;

	bool setBorders(const Point& topLeft, const Point& topRight, const Point& bottomLeft, const Point& bottomRight);
	bool setGameBoard(char boardSymbol);
	inline bool isHeightValid(Point borders[4]) const;
	inline bool isWidthValid(Point borders[4]) const;
	void printFrame() const;
	void printHorizontalLine(Point& leftEnd, Point& rightEnd, char symbol = GameConfig:: BORDER_SYMBOL) const;
	void printVerticalLine(Point& topEnd, Point& bottomEnd, char symbol = GameConfig:: BORDER_SYMBOL) const;
	void removeActiveShapeFromArr(Shape& shape, int shapeInd);
	bool canActiveShapeDrop(const Shape& shape) const;
	void updateActiveShapes(short int clearedRowInd);
	void insertShapeToArr(const Shape& newShape);
	
public:

	// Enums ->
	enum Borders { TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT };
	// <- Enums

	bool setRow(short int i, char boardSymbol);
	Board(const Point& topLeft, const Point& topRight, const Point& bottomLeft, const Point& bottomRight);
	inline const Point* getBorders() const { return borders; };
	gameBoardPointer getGameBoard() const;
	bool setNumOfShapes(size_t size);
	bool setPointInGameBoard(const Point& point);
	bool setShapeInGameBoard(const Shape& shape, bool isShapeNew);
	void print() const;
	void printGameBoard() const;
	void clear();
	inline bool clearRow(short int i) { return setRow(i, EMPTY); };
	int clearFullRows();
	bool canPointMove(Point point, Directions direction) const;
	inline Point getStartingPoint() const { Point SP = gameBoard[0][GameConfig::WIDTH / 2]; SP.moveUp(); return  gameBoard[0][GameConfig::WIDTH / 2]; };
	bool isShapeInBoard(const Shape& shape) const;
	void dropActiveShapes();
	bool canSetShapeInGameBoard(const Shape& shape) const;
	void explodeBomb(Shape& shape);
	void clearShapeFromGameBoard(Shape& shape);
	bool canShapeMove(const Shape& shape, Shape:: ShapeMovement movement) const;
	bool isPointInBoard(const Point& point) const;
	bool isRowFull(short int i) const;
	bool isPointFull(const Point& point) const;
};

#endif // Board.h