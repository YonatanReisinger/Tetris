#ifndef __SHAPE_H__
#define __SHAPE_H__
// Imports ->

// <- Imports
#include "Point.h"
#include <Windows.h>
#include <iostream>
using namespace std;
// Macros ans enums->
enum Type{PLUS,SQUARE,STRAIGHT,SKEW,MIRROR_SKEW,L,MIRROR_L, BOMB} ;
enum RotationDirection{FACE_UP,FACE_RIGHT,FACE_DOWN,FACE_LEFT};
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
	void createSquare(Point* points,Point& start,GameColorStatus colorStatus);
	void createStraight(Point* points, Point& start,GameColorStatus colorStatus);
	void createPlus(Point* points, Point& start,GameColorStatus colorStatus);
	void createSkew(Point* points, Point& start,GameColorStatus colorStatus);
	void createMirrorSkew(Point* points, Point& start,GameColorStatus colorStatus);
	void createL(Point* points, Point& start,GameColorStatus colorStatus);
	void createMirrorL(Point* points, Point& start,GameColorStatus colorStatus);
	void createBomb(Point& start, GameColorStatus colorStatus);
	void rotatePlus(ShapeMovement direction);
	void rotateMirrorL(ShapeMovement direction);
	void rotateStraight(ShapeMovement direction);
	void rotateL(ShapeMovement direction);
	void rotateMirrorSkew(ShapeMovement direction);
	void rotateSkew(ShapeMovement direction);
public:
	Shape();
	Shape(Type t, Point& start, GameColorStatus colorStatus, RotationDirection shapeDirection = FACE_UP);
	//void setColor(Color color);
	void moveDown();
	void moveLeft();
	void moveRight();
	void rotateLeft(Type t);
	void rotateRight(Type t);
	void print() const;
	void clearShape();
	void setSymbol(char symbol);
	bool setShapeRotationDirection(RotationDirection shapeDirection);
	void move(ShapeMovement movement);
	int getPointInd(const Point& p1) const;
	bool isShapeClear() const;
	short int getHighestY() const;
	bool setShapeColor(Color color);
	Type getType() const;
	Point* const getPoints();
	bool isAbove(const Shape& shape);
	inline RotationDirection getDirection() const { return shapeDirection; };
	bool isToTheRight(const Shape& shape) const;
	bool isToTheLeft(const Shape& shape) const;

	friend class Board;
};


#endif //Shape.h
