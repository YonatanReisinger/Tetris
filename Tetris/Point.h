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
	int x;
	int y;
public:
	Point(int x, int y);
	bool setX(int x);
	int getX();
	bool setY(int y);
	int getY();
	void gotoxy();
	void print(char ch = '*');
	bool copy(const Point* other);
	bool moveUp();
	bool moveDown();
	bool moveLeft();
	bool moveRight();
};
#endif //Point.h