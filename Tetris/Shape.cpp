#include "Shape.h"

/*input: gets a type that represents the tetronimo type, and a point that represents
the starting point of the tetronimo
Creates a new shape based on the type and point*/
Shape::Shape(Type t, Point& start,Direction shapeDirection = UP) {
	shapeType = t;
	this->shapeDirection = shapeDirection;
	switch (t) {
		case SQUARE: {
			createSquare(points, start);
			break;
		}
		case STRAIGHT: {
			createStraight(points, start);
			break;
		}
		case PLUS: {
			createPlus(points, start);
			break;
		}
		case SKEW: {
			createSkew(points, start);
			break;
		}
		case MIRROR_SKEW: {
			createMirrorSkew(points, start);
			break;
		}
		case L: {
			createL(points, start);
			break;
		}
		case MIRROR_L: {
			createMirrorL(points, start);
			break;
		}
	}

}
/*this function make the shape move down on the board*/
void Shape::moveDown() {
	for (int i = 0; i < NUM_OF_POINTS; i++) {
		points[i].moveDown();
	}
}
/*this function make the shape move left on the board*/
void Shape::moveLeft() {
	for (int i = 0; i < NUM_OF_POINTS; i++) {
		points[i].moveLeft();
	}
}
/*this function make the shape move right on the board*/
void Shape::moveRight() {
	for (int i = 0; i < NUM_OF_POINTS; i++) {
		points[i].moveRight();
	}
}
/*Creates a square shape tetronimo*/
void Shape::createSquare(Point* points, Point& start) {
	points[0] = start;//copies the starting point
	start.moveLeft();//takes the starting point and moves it left
	points[1] = start;//copies the "new" starting point
	start.moveDown();
	points[2] = start;
	start.moveRight();
	points[3] = start;
}
/*Creates a straight line tetronimo shape*/
void Shape::createStraight(Point* points, Point& start) {
	points[0] = start;//copies the starting point
	start.moveLeft();//takes the starting point and moves it left
	points[1] = start;//copies the "new" starting point
	start.moveLeft();
	points[2] =start;
	start.moveLeft();
	points[3] =start;
}
/*Creates a plus tetronimo shape*/
void Shape::createPlus(Point* points, Point& start) {
	points[0] = start;
	start.moveDown();
	points[1] = start;
	start.moveLeft();
	points[2] = start;
	start.moveRight();
	start.moveRight();
	points[3] = start;
}
/*Creates an 'L' shape tetronimo*/
void Shape::createL(Point* points, Point& start) {
	points[0] = start;
	start.moveDown();
	points[1] = start;
	start.moveDown();
	points[2] = start;
	start.moveRight();
	points[3] = start;
}
/*Creates a mirrored 'L' shape tetronimo*/
void Shape::createMirrorL(Point* points, Point& start) {
	points[0] = start;
	start.moveDown();
	points[1] = start;
	start.moveDown();
	points[2] = start;
	start.moveLeft();
	points[3] = start;
}
/*Creates a skew tetronimo shape*/
void Shape::createSkew(Point* points, Point& start) {
	points[0] = start;
	start.moveLeft();
	points[1] = start;
	start.moveDown();
	points[2] = start;
	start.moveLeft();
	points[3] = start;
}
/*Creates a mirrored skew tetronimo shape*/
void Shape::createMirrorSkew(Point* points, Point& start) {
	points[0] = start;
	start.moveRight();
	points[1] = start;
	start.moveDown();
	points[2] = start;
	start.moveRight();
	points[3] = start;
}
/*input: an enum type that represents the type of the shape we want to rotate left
 this function rotate the given shape left */
void Shape::rotateLeft(Type t) {
	switch (t) {
		case SQUARE: {
			break;
		}
		case STRAIGHT: {
			rotateStraight(LEFT);
			break;
		}
		case PLUS: {
			rotatePlus(LEFT);
			break;
		}
		case SKEW: {
			rotateSkew(LEFT);
			break;
		}
		case MIRROR_SKEW: {
			rotateMirrorSkew(LEFT);
			break;
		}
		case L: {
			rotateL(LEFT);
			break;
		}
		case MIRROR_L: {
			rotateMirrorL(LEFT);
			break;
		}
	}
}
/*input: a number that represents left/right rotation
This function rotates the plus shape tetronimo left/right based on the given number*/
void Shape::rotatePlus(int direction) {
	if (direction == LEFT) {
		points[3] = points[0];
		points[0] = points[2];
		switch (shapeDirection) {
			case FACE_UP: {
				points[2].setX(points[1].getX());
				points[2].setY(points[1].getY() - 1);
				break;
			}
			case FACE_LEFT: {
				points[2].setX(points[1].getX() + 1);
				points[2].setY(points[1].getY());
				break;
			}
			case FACE_DOWN: {
				points[2].setX(points[1].getX());
				points[2].setY(points[1].getY() + 1);
				break;
			}
			case FACE_RIGHT: {
				points[2].setX(points[1].getX() - 1);
				points[2].setY(points[1].getY());
				break;
			}
		}
	}
	else {
		points[2] = points[0];
		points[0] = points[3];
		switch (shapeDirection) {
			case FACE_UP: {
				points[3].setX(points[1].getX());
				points[3].setY(points[1].getY() - 1);
				break;
			}
			case FACE_LEFT: {
				points[3].setX(points[1].getX() + 1);
				points[3].setY(points[1].getY());
				break;
			}
			case FACE_DOWN: {
				points[3].setX(points[1].getX());
				points[3].setY(points[1].getY() + 1);
				break;
			}
			case FACE_RIGHT: {
				points[2].setX(points[1].getX() - 1);
				points[2].setY(points[1].getY());
				break;
			}
		}
	}
}
/*input: a number that represents left/right rotation
This function rotates the mirror 'L' shape tetronimo left/right based on the given number*/
void Shape::rotateMirrorL(int direction) {
	if (direction == LEFT) 
	{
		switch (shapeDirection) {
			case FACE_UP: {
				points[0].moveDown();
				points[0].moveLeft();
				points[2].moveRight();
				points[2].moveUp();
				points[3].moveRight();
				points[3].moveRight();
				break;
			}
			case FACE_RIGHT: {
				points[0].moveRight();
				points[0].moveDown();
				points[2].moveLeft();
				points[2].moveUp();
				points[3].moveDown();
				points[3].moveDown();
				break;
			}
			case FACE_DOWN: {
				points[0].moveRight();
				points[0].moveUp();
				points[2].moveLeft();
				points[2].moveDown();
				points[3].moveLeft();
				points[3].moveLeft();
				break;
			}
			case FACE_LEFT: {
				points[0].moveDown();
				points[0].moveRight();
				points[2].moveLeft();
				points[2].moveUp();
				points[3].moveUp();
				points[3].moveUp();
				break;
			}
		}
	}
	else
	{
		switch (shapeDirection) {
			case FACE_UP: {
				points[0].moveDown();
				points[0].moveRight();
				points[2].moveLeft();
				points[2].moveUp();
				points[3].moveUp();
				points[3].moveUp();
				break;
			}
			case FACE_RIGHT: {
				points[0].moveLeft();
				points[0].moveDown();
				points[2].moveRight();
				points[2].moveUp();
				points[3].moveRight();
				points[3].moveRight();
				break;
			}
			case FACE_DOWN: {
				points[0].moveLeft();
				points[0].moveUp();
				points[2].moveRight();
				points[2].moveDown();
				points[3].moveDown();
				points[3].moveDown();
				break;
			}
			case FACE_LEFT: {
				points[0].moveUp();
				points[0].moveRight();
				points[2].moveLeft();
				points[2].moveDown();
				points[3].moveLeft();
				points[3].moveLeft();
				break;
			}
		}
	}
}

void Shape::rotateStraight(int direction) {

}
void Shape::rotateL(int direction) {

}
void Shape::rotateMirrorSkew(int direction) {

}
void Shape::rotateSkew(int direction) {

}


