#ifndef __SHAPE_H__
#define __SHAPE_H__
// Imports ->

// <- Imports
#include "Point.h"
#include <Windows.h>
#include <iostream>
using namespace std;
// Macros ans enums->
enum Color { RED = FOREGROUND_RED, BLUE = FOREGROUND_BLUE, GREEN = FOREGROUND_GREEN };
#define NUM_OF_POINTS  4
// <- Macros and enums

class Shape {
private:
	/*each shape will be held by an array of 4 points.
	points [0] is the most left-bottom point
	points [1] is the most left-top point
	points [2] is the most right-bottom point
	points [3] is the most right-top point*/
	Point points[NUM_OF_POINTS];
	Color shapeColor;
	char symbol;
public:
	void setColor(Color color);
	void moveDown();
	void moveLeft();
	void moveRight();
	void rotateLeft();
	void rotateRight();
};


#endif //Shape.h

