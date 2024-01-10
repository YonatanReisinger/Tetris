#ifndef __SHAPE_H__
#define __SHAPE_H__
// Imports ->

// <- Imports
#include "Point.h"
#include <Windows.h>
#include <iostream>
using namespace std;
// Macros ans enums->
enum Type{PLUS,SQUARE,STRAIGHT,SKEW,MIRROR_SKEW,L,MIRROR_L};
#define NUM_OF_POINTS  4
// <- Macros and enums

class Shape {
private:
	/*each shape will be held by an array of 4 points and an enum that represents
	the shape type*/
	Point points[NUM_OF_POINTS];
	Type shapeType;
public:
	Shape(Type t, Point& start);
	//void setColor(Color color);
	void moveDown();
	void moveLeft();
	void moveRight();
	void rotateLeft(Type t);
	void rotateRight(Type t);
};


#endif //Shape.h

