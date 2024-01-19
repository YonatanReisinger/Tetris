#ifndef __POINT_H__
#define __POINT_H__

// Imports ->
#include<windows.h> //for gotoxy
#include "gameConfig.h"
#include <iostream>
using namespace std;
// <- Imports

// Macros and enums ->
// <- Macros and enums

class Point {
private:
	short int x;
	short int y;
	char symbol;
	//Color color;
public:
	Point(short int x = 0, short int y = 0, char symbol = EMPTY);
	bool setX(short int x);
	short int getX() const;
	bool setY(short int y);
	short int getY() const;
	bool setXY(short int x, short int y);
	bool setSymbol(char symbol);
	char getSymbol() const;
	//bool setColor(Color color);
	//Color getColor();
	void gotoxy();
	void print();
	bool moveUp();
	bool moveDown();
	bool moveLeft();
	bool moveRight();
	bool move(Directions direction);
	bool areCoordinatesEqual(const Point& other) const;

	friend class Board;
};
#endif //Point.h