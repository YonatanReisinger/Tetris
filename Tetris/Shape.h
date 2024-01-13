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
enum RotationDirection{FACE_UP,FACE_DOWN,FACE_LEFT,FACE_RIGHT};
#define NUM_OF_POINTS  4
#define LEFT -1
#define RIGHT 1
// <- Macros and enums

class Shape {
private:
	/*each shape will be held by an array of 4 points and an enum that represents
	the shape type*/
	Point points[NUM_OF_POINTS];
	Type shapeType;
	RotationDirection shapeDirection;
public:
	Shape(Type t, Point& start,RotationDirection shapeDirection = FACE_UP);
	//void setColor(Color color);
	void moveDown();
	void moveLeft();
	void moveRight();
	void rotateLeft(Type t);
	void rotateRight(Type t);
	void createSquare(Point* points,Point& start);
	void createStraight(Point* points, Point& start);
	void createPlus(Point* points, Point& start);
	void createSkew(Point* points, Point& start);
	void createMirrorSkew(Point* points, Point& start);
	void createL(Point* points, Point& start);
	void createMirrorL(Point* points, Point& start);
	void printShape();
	void rotatePlus(int direction);
	void rotateMirrorL(int direction);
	void rotateStraight(int direction);
	void rotateL(int direction);
	void rotateMirrorSkew(int direction);
	void rotateSkew(int direction);
	
};


#endif //Shape.h
