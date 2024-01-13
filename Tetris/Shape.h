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
enum ShapeMovement{LEFT,RIGHT,ROTATE_LEFT,ROTATE_RIGHT,DROP};
#define NUM_OF_POINTS  4
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
	void print();
	void rotatePlus(ShapeMovement direction);
	void rotateMirrorL(ShapeMovement direction);
	void rotateStraight(ShapeMovement direction);
	void rotateL(ShapeMovement direction);
	void rotateMirrorSkew(ShapeMovement direction);
	void rotateSkew(ShapeMovement direction);
	void clearShape();
	void setSymbol(char symbol);
	void move(ShapeMovement movement);
	friend class Board;
};


#endif //Shape.h
