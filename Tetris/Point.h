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
	Point(short int x = 0, short int y = 0, char symbol = '*');
	bool setX(short int x);
	short int getX();
	bool setY(short int y);
	short int getY();
	bool setXY(short int x, short int y);
	bool setSymbol(char symbol);
	char getSymbol();
	//bool setColor(Color color);
	//Color getColor();
	void gotoxy();
	void print();
	bool moveUp();
	bool moveDown();
	bool moveLeft();
	bool moveRight();
	bool isInSameCoordinate(const Point& other);
};
#endif //Point.h