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
public:
	Point(short int x = 0, short int y = 0);
	bool setX(short int x);
	short int getX();
	bool setY(short int y);
	short int getY();
	void gotoxy();
	void print(char symbol = '*');
	bool copy(const Point& other);
	bool moveUp();
	bool moveDown();
	bool moveLeft();
	bool moveRight();
};
#endif //Point.h