#include "Shape.h"

/*input: gets a type that represents the tetronimo type, and a point that represents
the starting point of the tetronimo
Creates a new shape based on the type and point*/
Shape::Shape(Type t, Point& start,RotationDirection shapeDirection) {
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
	setSymbol(GameConfig::SHAPE_SYMBOL);
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
	Point p1 = start;
	points[0] = p1;//copies the starting point
	p1.moveLeft();//takes the starting point and moves it left
	points[1] = p1;//copies the "new" starting point
	p1.moveDown();
	points[2] = p1;
	p1.moveRight();
	points[3] = p1;
}
/*Creates a straight line tetronimo shape*/
void Shape::createStraight(Point* points, Point& start) {
	Point p1 = start;
	points[0] = p1;//copies the starting point
	p1.moveDown();//takes the starting point and moves it left
	points[1] = p1;//copies the "new" starting point
	p1.moveDown();
	points[2] =p1;
	p1.moveDown();
	points[3] =p1;
}
/*Creates a plus tetronimo shape*/
void Shape::createPlus(Point* points, Point& start) {
	Point p1 = start;
	points[0] = p1;
	p1.moveDown();
	points[1] = p1;
	p1.moveLeft();
	points[2] = p1;
	p1.moveRight();
	p1.moveRight();
	points[3] = p1;
}
/*Creates an 'L' shape tetronimo*/
void Shape::createL(Point* points, Point& start) {
	Point p1 = start;
	points[0] = p1;
	p1.moveDown();
	points[1] = p1;
	p1.moveDown();
	points[2] = p1;
	p1.moveRight();
	points[3] = p1;
}
/*Creates a mirrored 'L' shape tetronimo*/
void Shape::createMirrorL(Point* points, Point& start) {
	Point p1 = start;
	points[0] = p1;
	p1.moveDown();
	points[1] = p1;
	p1.moveDown();
	points[2] = p1;
	p1.moveLeft();
	points[3] = p1;
}
/*Creates a skew tetronimo shape*/
void Shape::createSkew(Point* points, Point& start) {
	Point p1 = start;
	points[0] = p1;
	p1.moveDown();
	points[1] = p1;
	p1.moveRight();
	points[2] = p1;
	p1.moveDown();
	points[3] = p1;
}
/*Creates a mirrored skew tetronimo shape*/
void Shape::createMirrorSkew(Point* points, Point& start) {
	Point p1 = start;
	points[0] = p1;
	p1.moveDown();
	points[1] = p1;
	p1.moveLeft();
	points[2] = p1;
	p1.moveDown();
	points[3] = p1;
}
/*input: an enum type that represents the type of the shape we want to rotate left
 this function rotate the given shape left */
void Shape::rotateLeft(Type t) {
	switch (t) {
		case SQUARE: {
			break;
		}
		case STRAIGHT: {
			rotateStraight(ROTATE_LEFT);
			break;
		}
		case PLUS: {
			rotatePlus(ROTATE_LEFT);
			break;
		}
		case SKEW: {
			rotateSkew(ROTATE_LEFT);
			break;
		}
		case MIRROR_SKEW: {
			rotateMirrorSkew(ROTATE_LEFT);
			break;
		}
		case L: {
			rotateL(ROTATE_LEFT);
			break;
		}
		case MIRROR_L: {
			rotateMirrorL(ROTATE_LEFT);
			break;
		}
	}
}
/*input: an enum type that represents the type of the shape we want to rotate left
 this function rotate the given shape right */
void Shape::rotateRight(Type t) {
	switch (t) {
	case SQUARE: {
		break;
	}
	case STRAIGHT: {
		rotateStraight(ROTATE_RIGHT);
		break;
	}
	case PLUS: {
		rotatePlus(ROTATE_RIGHT);
		break;
	}
	case SKEW: {
		rotateSkew(ROTATE_RIGHT);
		break;
	}
	case MIRROR_SKEW: {
		rotateMirrorSkew(ROTATE_RIGHT);
		break;
	}
	case L: {
		rotateL(ROTATE_RIGHT);
		break;
	}
	case MIRROR_L: {
		rotateMirrorL(ROTATE_RIGHT);
		break;
	}
	}
}
void Shape::rotatePlus(ShapeMovement direction) {
	if (direction == ROTATE_LEFT) {
		points[3] = points[0];
		points[0] = points[2];
		switch (shapeDirection) {
			case FACE_UP: {
				points[2].moveRight();
				points[2].moveDown();
				shapeDirection = FACE_LEFT;
				break;
			}
			case FACE_LEFT: {
				points[2].moveUp();
				points[2].moveRight();
				shapeDirection = FACE_DOWN;
				break;
			}
			case FACE_DOWN: {
				points[2].moveLeft();
				points[2].moveUp();
				shapeDirection = FACE_RIGHT;
				break;
			}
			case FACE_RIGHT: {
				points[2].moveLeft();
				points[2].moveDown();
				shapeDirection = FACE_UP;
				break;
			}
		}
	}
	else {
		points[2] = points[0];
		points[0] = points[3];
		switch (shapeDirection) {
			case FACE_UP: {
				points[3].moveLeft();
				points[3].moveDown();
				shapeDirection = FACE_RIGHT;
				break;
			}
			case FACE_RIGHT: {
				points[3].moveLeft();
				points[3].moveUp();
				shapeDirection = FACE_DOWN;
				break;
			}
			case FACE_DOWN: {
				points[3].moveRight();
				points[3].moveUp();
				shapeDirection = FACE_LEFT;
				break;
			}
			case FACE_LEFT: {
				points[3].moveRight();
				points[3].moveDown();
				shapeDirection = FACE_UP;
				break;
			}
		}
	}
}
/*input: a number that represents left/right rotation
This function rotates the mirror 'L' shape tetronimo left/right based on the given number*/
void Shape::rotateMirrorL(ShapeMovement direction) {
	if (direction == ROTATE_LEFT) 
	{
		switch (shapeDirection) {
			case FACE_UP: {
				points[0].moveDown();
				points[0].moveLeft();
				points[2].moveRight();
				points[2].moveUp();
				points[3].moveRight();
				points[3].moveRight();
				shapeDirection = FACE_LEFT;
				break;
			}
			case FACE_RIGHT: {
				points[0].moveLeft();
				points[0].moveUp();
				points[2].moveRight();
				points[2].moveDown();
				points[3].moveDown();
				points[3].moveDown();
				shapeDirection = FACE_UP;
				break;
			}
			case FACE_DOWN: {
				points[0].moveRight();
				points[0].moveUp();
				points[2].moveLeft();
				points[2].moveDown();
				points[3].moveLeft();
				points[3].moveLeft();
				shapeDirection = FACE_RIGHT;
				break;
			}
			case FACE_LEFT: {
				points[0].moveDown();
				points[0].moveRight();
				points[2].moveLeft();
				points[2].moveUp();
				points[3].moveUp();
				points[3].moveUp();
				shapeDirection = FACE_DOWN;
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
				shapeDirection = FACE_RIGHT;
				break;
			}
			case FACE_RIGHT: {
				points[0].moveLeft();
				points[0].moveDown();
				points[2].moveRight();
				points[2].moveUp();
				points[3].moveRight();
				points[3].moveRight();
				shapeDirection = FACE_DOWN;
				break;
			}
			case FACE_DOWN: {
				points[0].moveLeft();
				points[0].moveUp();
				points[2].moveRight();
				points[2].moveDown();
				points[3].moveDown();
				points[3].moveDown();
				shapeDirection = FACE_LEFT;
				break;
			}
			case FACE_LEFT: {
				points[0].moveUp();
				points[0].moveRight();
				points[2].moveLeft();
				points[2].moveDown();
				points[3].moveLeft();
				points[3].moveLeft();
				shapeDirection = FACE_UP;
				break;
			}
		}
	}
}
/*input: a number that represents left/right rotation
This function rotates the straight shape tetronimo left/right based on the given number*/
void Shape::rotateStraight(ShapeMovement direction) {
	if (direction == ROTATE_LEFT) {
		switch (shapeDirection) {
			case FACE_UP: {
				points[0].moveLeft();
				points[0].moveDown();
				points[2].moveRight();
				points[2].moveUp();
				for (int i = 0; i < 2; i++) {
					points[3].moveRight();
					points[3].moveUp();
				}
				shapeDirection = FACE_LEFT;
				break;
			}
			case FACE_LEFT: {
				points[0].moveRight();
				points[0].moveDown();
				points[2].moveLeft();
				points[2].moveUp();
				for (int i = 0; i < 2; i++) {
					points[3].moveLeft();
					points[3].moveUp();
				}
				shapeDirection = FACE_DOWN;
				break;
			}
			case FACE_DOWN: {
				points[0].moveUp();
				points[0].moveRight();
				points[2].moveLeft();
				points[2].moveDown();
				for (int i = 0; i < 2; i++) {
					points[3].moveLeft();
					points[3].moveDown();
				}
				shapeDirection = FACE_RIGHT;
				break;
			}
			case FACE_RIGHT: {
				points[0].moveLeft();
				points[0].moveUp();
				points[2].moveRight();
				points[2].moveDown();
				for (int i = 0; i < 2; i++) {
					points[3].moveRight();
					points[3].moveDown();
				}
				shapeDirection = FACE_UP;
				break;
			}
		}
	}
	else {
		switch (shapeDirection) {
			case FACE_UP: {
				points[0].moveRight();
				points[0].moveDown();
				points[2].moveLeft();
				points[2].moveUp();
				for (int i = 0; i < 2; i++) {
					points[3].moveLeft();
					points[3].moveUp();
				}
				shapeDirection = FACE_RIGHT;
				break;
			}
			case FACE_RIGHT: {
				points[0].moveLeft();
				points[0].moveDown();
				points[2].moveRight();
				points[2].moveUp();
				for (int i = 0; i < 2; i++) {
					points[3].moveRight();
					points[3].moveUp();
				}
				shapeDirection = FACE_DOWN;
				break;
			}
			case FACE_DOWN: {
				points[0].moveUp();
				points[0].moveLeft();
				points[2].moveRight();
				points[2].moveDown();
				for (int i = 0; i < 2; i++) {
					points[3].moveRight();
					points[3].moveDown();
				}
				shapeDirection = FACE_LEFT;
				break;
			}
			case FACE_LEFT: {
				points[0].moveRight();
				points[0].moveUp();
				points[2].moveLeft();
				points[2].moveDown();
				for (int i = 0; i < 2; i++) {
					points[3].moveLeft();
					points[3].moveDown();
				}
				shapeDirection = FACE_UP;
				break;
			}
		}
	}
}
/*input: a number that represents left/right rotation
This function rotates the L shape tetronimo left/right based on the given number*/
void Shape::rotateL(ShapeMovement direction) {
	if (direction == ROTATE_LEFT) {
		switch (shapeDirection) {
			case FACE_UP: {
				points[0].moveDown();
				points[0].moveLeft();
				points[2].moveRight();
				points[2].moveUp();
				points[3].moveUp();
				points[3].moveUp();
				shapeDirection = FACE_LEFT;
				break;
			}
			case FACE_LEFT: {
				points[0].moveDown();
				points[0].moveRight();
				points[2].moveLeft();
				points[2].moveUp();
				points[3].moveRight();
				points[3].moveRight();
				shapeDirection = FACE_DOWN;
				break;
			}
			case FACE_DOWN: {
				points[0].moveUp();
				points[0].moveRight();
				points[2].moveLeft();
				points[2].moveDown();
				points[3].moveDown();
				points[3].moveDown();
				shapeDirection = FACE_RIGHT;
				break;
			}
			case FACE_RIGHT: {
				points[0].moveLeft();
				points[0].moveUp();
				points[2].moveRight();
				points[2].moveDown();
				points[3].moveRight();
				points[3].moveRight();
				shapeDirection = FACE_UP;
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
				points[3].moveLeft();
				points[3].moveLeft();
				shapeDirection = FACE_RIGHT;
				break;
			}
			case FACE_RIGHT: {
				points[0].moveLeft();
				points[0].moveDown();
				points[2].moveRight();
				points[2].moveUp();
				points[3].moveUp();
				points[3].moveUp();
				shapeDirection = FACE_DOWN;
				break;
			}
			case FACE_DOWN: {
				points[0].moveLeft();
				points[0].moveUp();
				points[2].moveRight();
				points[2].moveDown();
				points[3].moveRight();
				points[3].moveRight();
				shapeDirection = FACE_LEFT;
				break;
			}
			case FACE_LEFT: {
				points[0].moveRight();
				points[0].moveUp();
				points[2].moveLeft();
				points[2].moveDown();
				points[3].moveDown();
				points[3].moveDown();
				shapeDirection = FACE_UP;
				break;
			}
		}
	}
}
/*input: a number that represents left/right rotation
This function rotates the mirror skew shape tetronimo left/right based on the given number*/
void Shape::rotateMirrorSkew(ShapeMovement direction) {
	if (direction == ROTATE_LEFT) {
		switch (shapeDirection) {
			case FACE_UP: {
				points[0] = points[2];
				points[2].moveDown();
				points[2].moveRight();
				points[3].moveRight();
				points[3].moveRight();
				shapeDirection = FACE_LEFT;
				break;
			}
			case FACE_LEFT: {
				points[0] = points[2];
				points[2].moveUp();
				points[2].moveRight();
				points[3].moveUp();
				points[3].moveUp();
				shapeDirection = FACE_DOWN;
				break;
			}
			case FACE_DOWN: {
				points[0] = points[2];
				points[2].moveLeft();
				points[2].moveUp();
				points[3].moveLeft();
				points[3].moveLeft();
				shapeDirection = FACE_RIGHT;
				break;
			}
			case FACE_RIGHT: {
				points[0] = points[2];
				points[2].moveLeft();
				points[2].moveDown();
				points[3].moveUp();
				points[3].moveUp();
				shapeDirection = FACE_UP;
				break;
			}
		}
	}
	else
	{
		switch (shapeDirection) {
			case FACE_UP: {
				points[2] = points[0];
				points[0].moveDown();
				points[0].moveRight();
				points[3].moveUp();
				points[3].moveUp();
				shapeDirection = FACE_RIGHT;
				break;
			}
			case FACE_LEFT: {
				points[2] = points[0];
				points[0].moveUp();
				points[0].moveRight();
				points[3].moveLeft();
				points[3].moveLeft();
				shapeDirection = FACE_UP;
				break;
			}
			case FACE_DOWN: {
				points[2] = points[0];
				points[0].moveLeft();
				points[0].moveUp();
				points[3].moveDown();
				points[3].moveDown();
				shapeDirection = FACE_LEFT;
				break;
			}
			case FACE_RIGHT: {
				points[2] = points[0];
				points[0].moveDown();
				points[0].moveLeft();
				points[3].moveRight();
				points[3].moveRight();
				shapeDirection = FACE_DOWN;
				break;
			}
		}
	}
}
/*input: a number that represents left/right rotation
This function rotates the skew shape tetronimo left/right based on the given number*/
void Shape::rotateSkew(ShapeMovement direction) {
	if (direction == ROTATE_LEFT) {
		switch (shapeDirection) {
			case FACE_UP: {
				points[2] = points[0];
				points[0].moveDown();
				points[0].moveLeft();
				points[3].moveUp();
				points[3].moveUp();
				shapeDirection = FACE_LEFT;
				break;
			}
			case FACE_LEFT: {
				points[2] = points[0];
				points[0].moveDown();
				points[0].moveRight();
				points[3].moveLeft();
				points[3].moveLeft();
				shapeDirection = FACE_DOWN;
				break;
			}
			case FACE_DOWN: {
				points[2] = points[0];
				points[0].moveRight();
				points[0].moveUp();
				points[3].moveDown();
				points[3].moveDown();
				shapeDirection = FACE_RIGHT;
				break;
			}
			case FACE_RIGHT: {
				points[2] = points[0];
				points[0].moveLeft();
				points[0].moveUp();
				points[3].moveRight();
				points[3].moveRight();
				shapeDirection = FACE_UP;
				break;
			}
		}
	}
	else 
	{
		switch (shapeDirection) {
			case FACE_UP: {
				points[0] = points[2];
				points[2].moveDown();
				points[2].moveLeft();
				points[3].moveLeft();
				points[3].moveLeft();
				shapeDirection = FACE_RIGHT;
				break;
			}
			case FACE_RIGHT: {
				points[0] = points[2];
				points[2].moveLeft();
				points[2].moveUp();
				points[3].moveUp();
				points[3].moveUp();
				shapeDirection = FACE_DOWN;
				break;
			}
			case FACE_DOWN: {
				points[0] = points[2];
				points[2].moveRight();
				points[2].moveUp();
				points[3].moveRight();
				points[3].moveRight();
				shapeDirection = FACE_LEFT;
				break;
			}
			case FACE_LEFT: {
				points[0] = points[2];
				points[2].moveDown();
				points[2].moveRight();
				points[3].moveDown();
				points[3].moveDown();
				shapeDirection = FACE_UP;
				break;
			}
		}
	}
}

void Shape:: clearShape() {
	setSymbol(EMPTY);
}

void Shape::setSymbol(char symbol) {
	for (int i = 0; i < 4; i++) {
		points[i].setSymbol(symbol);
	}
}

void Shape::print() {
	for (int i = 0; i < 4; i++) {
		points[i].print();
	}
}

void Shape::move(ShapeMovement movement) {
	switch (movement) {
	case ROTATE_LEFT: {
		rotateLeft(shapeType);
		break;
	}
	case ROTATE_RIGHT: {
		rotateRight(shapeType);
		break;
	}
	case LEFT: {
		moveLeft();
		break;
	}
	case RIGHT: {
		moveRight();
		break;
	}
	case DROP :
		moveDown();
		break;
	}
}



