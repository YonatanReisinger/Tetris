#include "Shape.h"



/*************************
* Name: Shape
* Input: none
* Output: none
* Description: Default constructor for the Shape class.

*************************/
Shape::Shape() {
	shapeDirection = RotationDirection:: FACE_UP ;
	shapeType = Type:: SQUARE;
}
/*************************
* Name: Shape
* Input: Type t, Point& start, GameColorStatus colorStatus, RotationDirection shapeDirection = FACE_UP
* Output: none
* Description: Parametrized constructor for the Shape class, creating a shape of the specified type, starting from the provided point,
   with the specified color status and rotation direction.

*************************/
Shape::Shape(Type t, Point& start,GameColorStatus colorStatus,RotationDirection shapeDirection) {
	shapeType = t;
	this->shapeDirection = shapeDirection;
	switch (t) {
		case Type:: SQUARE: {
			createSquare(start,colorStatus);
			break;
		}
		case Type:: STRAIGHT: {
			createStraight(start,colorStatus);
			break;
		}
		case Type:: PLUS: {
			createPlus(start, colorStatus);
			break;
		}
		case Type:: SKEW: {
			createSkew(start, colorStatus);
			break;
		}
		case Type:: MIRROR_SKEW: {
			createMirrorSkew(start, colorStatus);
			break;
		}
		case Type:: L: {
			createL(start, colorStatus);
			break;
		}
		case Type:: MIRROR_L: {
			createMirrorL(start, colorStatus);
			break;
		}
		case Type:: BOMB: {
			createBomb(start, colorStatus);
			return;
		}
	}
	setSymbol(GameConfig::SHAPE_SYMBOL);
}
/*************************
* Name: moveDown, moveLeft, moveRight
* Input: none
* Output: none
* Description: Moves the shape down, left, or right, respectively.

*************************/
void Shape::moveDown() {
	for (int i = 0; i < NUM_OF_POINTS; i++) {
		points[i].moveDown();
	}
}
void Shape::moveLeft() {
	for (int i = 0; i < NUM_OF_POINTS; i++) {
		points[i].moveLeft();
	}
}
void Shape::moveRight() {
	for (int i = 0; i < NUM_OF_POINTS; i++) {
		points[i].moveRight();
	}
}
/*************************
* Name: createSquare
* Input: Point* points, Point& start, GameColorStatus colorStatus
* Output: none
* Description: Creates a square shape using the specified points, starting from the provided starting point,
  with the specified color status.

*************************/
void Shape::createSquare(Point& start,GameColorStatus colorStatus) {
	Point p1 = start;
	points[0] = p1;//copies the starting point
	p1.moveLeft();//takes the starting point and moves it left
	points[1] = p1;//copies the "new" starting point
	p1.moveDown();
	points[2] = p1;
	p1.moveRight();
	points[3] = p1;
	if (colorStatus == GameColorStatus:: COLORIZED) {
		setShapeColor(Point:: Color::BLUE);
	}
}
/*************************
* Name: createStraight
* Input: Point* points, Point& start, GameColorStatus colorStatus
* Output: none
* Description: Creates a straight shape using the specified points, starting from the provided starting point,
   with the specified color status.

*************************/
void Shape::createStraight(Point& start,GameColorStatus colorStatus) {
	Point p1 = start;
	points[0] = p1;//copies the starting point
	p1.moveDown();//takes the starting point and moves it left
	points[1] = p1;//copies the "new" starting point
	p1.moveDown();
	points[2] =p1;
	p1.moveDown();
	points[3] =p1;
	if (colorStatus == GameColorStatus:: COLORIZED) {
		setShapeColor(Point:: Color::BRWON);
	}
}
/*************************
* Name: createPlus
* Input: Point* points, Point& start, GameColorStatus colorStatus
* Output: none
* Description: Creates a plus shape using the specified points, starting from the provided starting point, with the specified color status.

*************************/
void Shape::createPlus(Point& start,GameColorStatus colorStatus) {
	Point p1 = start;
	points[0] = p1;
	p1.moveDown();
	points[1] = p1;
	p1.moveLeft();
	points[2] = p1;
	p1.moveRight();
	p1.moveRight();
	points[3] = p1;
	if (colorStatus == GameColorStatus:: COLORIZED) {
		setShapeColor(Point:: Color::GREY);
	}
}
/*************************
* Name: createL
* Input: Point* points, Point& start, GameColorStatus colorStatus
* Output: none
* Description: Creates an L-shaped figure using the specified points, starting from the provided starting point, with the specified color status.

*************************/
void Shape::createL(Point& start,GameColorStatus colorStatus) {
	Point p1 = start;
	points[0] = p1;
	p1.moveDown();
	points[1] = p1;
	p1.moveDown();
	points[2] = p1;
	p1.moveRight();
	points[3] = p1;
	if (colorStatus == GameColorStatus:: COLORIZED) {
		setShapeColor(Point:: Color::GREEN);
	}
}
/*************************
* Name: createMirrorL
* Input: Point* points, Point& start, GameColorStatus colorStatus
* Output: none
* Description: Creates a mirror L-shaped figure using the specified points, starting from the provided starting point, with the specified color status.

*************************/
void Shape::createMirrorL(Point& start,GameColorStatus colorStatus) {
	Point p1 = start;
	points[0] = p1;
	p1.moveDown();
	points[1] = p1;
	p1.moveDown();
	points[2] = p1;
	p1.moveLeft();
	points[3] = p1;
	if (colorStatus == GameColorStatus:: COLORIZED) {
		setShapeColor(Point:: Color::CYAN);
	}
}
void Shape::createBomb(Point& start, GameColorStatus colorStatus)
{
	points[0] = start;
	points[0].setSymbol(GameConfig::BOMB_SYMBOL);
	points[1] = EMPTY;
	points[2] = EMPTY;
	points[3] = EMPTY;
	if (colorStatus == GameColorStatus:: COLORIZED) {
		setShapeColor(Point:: Color::WHITE);
	}
}
/*************************
* Name: createSkew
* Input: Point* points, Point& start, GameColorStatus colorStatus
* Output: none
* Description: Creates a skew shape using the specified points, starting from the provided starting point, with the specified color status.

*************************/
void Shape::createSkew(Point& start,GameColorStatus colorStatus) {
	Point p1 = start;
	points[0] = p1;
	p1.moveDown();
	points[1] = p1;
	p1.moveRight();
	points[2] = p1;
	p1.moveDown();
	points[3] = p1;
	if (colorStatus == GameColorStatus:: COLORIZED) {
		setShapeColor(Point:: Color::PURPLE);
	}
}
/*************************
* Name: createMirrorSkew
* Input: Point* points, Point& start, GameColorStatus colorStatus
* Output: none
* Description: Creates a mirror skew shape using the specified points, starting from the provided starting point,
  with the specified color status.

*************************/
void Shape::createMirrorSkew(Point& start,GameColorStatus colorStatus) {
	Point p1 = start;
	points[0] = p1;
	p1.moveDown();
	points[1] = p1;
	p1.moveLeft();
	points[2] = p1;
	p1.moveDown();
	points[3] = p1;
	if (colorStatus == GameColorStatus:: COLORIZED) {
		setShapeColor(Point:: Color::RED);
	}
}
/*************************
* Name: rotateLeft
* Input: Type t
* Output: none
* Description: Rotates the shape left or right, respectively.

*************************/
void Shape::rotateLeft(Type t) {
	switch (t) {
		case Type:: SQUARE: {
			break;
		}
		case Type:: STRAIGHT: {
			rotateStraight(ShapeMovement:: ROTATE_LEFT);
			break;
		}
		case Type:: PLUS: {
			rotatePlus(ShapeMovement:: ROTATE_LEFT);
			break;
		}
		case Type:: SKEW: {
			rotateSkew(ShapeMovement::ROTATE_LEFT);
			break;
		}
		case Type:: MIRROR_SKEW: {
			rotateMirrorSkew(ShapeMovement::ROTATE_LEFT);
			break;
		}
		case Type:: L: {
			rotateL(ShapeMovement::ROTATE_LEFT);
			break;
		}
		case Type:: MIRROR_L: {
			rotateMirrorL(ShapeMovement:: ROTATE_LEFT);
			break;
		}
	}
}
/*************************
* Name: rotateRight
* Input: Type t
* Output: none
* Description: Rotates the shape right or right, respectively.

*************************/
void Shape::rotateRight(Type t) {
	switch (t) {
	case Type:: SQUARE: {
		break;
	}
	case Type:: STRAIGHT: {
		rotateStraight(ShapeMovement::ROTATE_RIGHT);
		break;
	}
	case Type:: PLUS: {
		rotatePlus(ShapeMovement:: ROTATE_RIGHT);
		break;
	}
	case Type:: SKEW: {
		rotateSkew(ShapeMovement:: ROTATE_RIGHT);
		break;
	}
	case Type:: MIRROR_SKEW: {
		rotateMirrorSkew(ShapeMovement:: ROTATE_RIGHT);
		break;
	}
	case Type:: L: {
		rotateL(ShapeMovement:: ROTATE_RIGHT);
		break;
	}
	case Type:: MIRROR_L: {
		rotateMirrorL(ShapeMovement:: ROTATE_RIGHT);
		break;
	}
	}
}
/*************************
* Name: rotatePlus, rotateMirrorL, rotateStraight, rotateL, rotateMirrorSkew, rotateSkew
* Input: ShapeMovement direction
* Output: none
* Description: Rotates the shape in the specified direction.

*************************/
void Shape::rotatePlus(ShapeMovement direction) {
	if (direction == ShapeMovement:: ROTATE_LEFT) {
		points[3] = points[0];
		points[0] = points[2];
		switch (shapeDirection) {
		case RotationDirection:: FACE_UP: {
				points[2].moveRight();
				points[2].moveDown();
				shapeDirection = RotationDirection:: FACE_LEFT;
				break;
			}
			case RotationDirection:: FACE_LEFT: {
				points[2].moveUp();
				points[2].moveRight();
				shapeDirection = RotationDirection:: FACE_DOWN;
				break;
			}
			case RotationDirection:: FACE_DOWN: {
				points[2].moveLeft();
				points[2].moveUp();
				shapeDirection = RotationDirection:: FACE_RIGHT;
				break;
			}
			case RotationDirection:: FACE_RIGHT: {
				points[2].moveLeft();
				points[2].moveDown();
				shapeDirection = RotationDirection:: FACE_UP;
				break;
			}
		}
	}
	else {
		points[2] = points[0];
		points[0] = points[3];
		switch (shapeDirection) {
			case RotationDirection:: FACE_UP: {
				points[3].moveLeft();
				points[3].moveDown();
				shapeDirection = RotationDirection:: FACE_RIGHT;
				break;
			}
			case RotationDirection:: FACE_RIGHT: {
				points[3].moveLeft();
				points[3].moveUp();
				shapeDirection = RotationDirection:: FACE_DOWN;
				break;
			}
			case RotationDirection:: FACE_DOWN: {
				points[3].moveRight();
				points[3].moveUp();
				shapeDirection = RotationDirection:: FACE_LEFT;
				break;
			}
			case RotationDirection:: FACE_LEFT: {
				points[3].moveRight();
				points[3].moveDown();
				shapeDirection = RotationDirection:: FACE_UP;
				break;
			}
		}
	}
}
void Shape::rotateMirrorL(ShapeMovement direction) {
	if (direction == ShapeMovement:: ROTATE_LEFT)
	{
		switch (shapeDirection) {
			case RotationDirection:: FACE_UP: {
				points[0].moveDown();
				points[0].moveLeft();
				points[2].moveRight();
				points[2].moveUp();
				points[3].moveRight();
				points[3].moveRight();
				shapeDirection = RotationDirection:: FACE_LEFT;
				break;
			}
			case RotationDirection:: FACE_RIGHT: {
				points[0].moveLeft();
				points[0].moveUp();
				points[2].moveRight();
				points[2].moveDown();
				points[3].moveDown();
				points[3].moveDown();
				shapeDirection = RotationDirection:: FACE_UP;
				break;
			}
			case RotationDirection:: FACE_DOWN: {
				points[0].moveRight();
				points[0].moveUp();
				points[2].moveLeft();
				points[2].moveDown();
				points[3].moveLeft();
				points[3].moveLeft();
				shapeDirection = RotationDirection:: FACE_RIGHT;
				break;
			}
			case RotationDirection:: FACE_LEFT: {
				points[0].moveDown();
				points[0].moveRight();
				points[2].moveLeft();
				points[2].moveUp();
				points[3].moveUp();
				points[3].moveUp();
				shapeDirection = RotationDirection:: FACE_DOWN;
				break;
			}
		}
	}
	else
	{
		switch (shapeDirection) {
			case RotationDirection:: FACE_UP: {
				points[0].moveDown();
				points[0].moveRight();
				points[2].moveLeft();
				points[2].moveUp();
				points[3].moveUp();
				points[3].moveUp();
				shapeDirection = RotationDirection:: FACE_RIGHT;
				break;
			}
			case RotationDirection:: FACE_RIGHT: {
				points[0].moveLeft();
				points[0].moveDown();
				points[2].moveRight();
				points[2].moveUp();
				points[3].moveRight();
				points[3].moveRight();
				shapeDirection = RotationDirection:: FACE_DOWN;
				break;
			}
			case RotationDirection:: FACE_DOWN: {
				points[0].moveLeft();
				points[0].moveUp();
				points[2].moveRight();
				points[2].moveDown();
				points[3].moveDown();
				points[3].moveDown();
				shapeDirection = RotationDirection:: FACE_LEFT;
				break;
			}
			case RotationDirection:: FACE_LEFT: {
				points[0].moveUp();
				points[0].moveRight();
				points[2].moveLeft();
				points[2].moveDown();
				points[3].moveLeft();
				points[3].moveLeft();
				shapeDirection = RotationDirection:: FACE_UP;
				break;
			}
		}
	}
}
void Shape::rotateStraight(ShapeMovement direction) {
	if (direction == ShapeMovement:: ROTATE_LEFT) {
		switch (shapeDirection) {
			case RotationDirection:: FACE_UP: {
				points[0].moveLeft();
				points[0].moveDown();
				points[2].moveRight();
				points[2].moveUp();
				for (int i = 0; i < 2; i++) {
					points[3].moveRight();
					points[3].moveUp();
				}
				shapeDirection = RotationDirection:: FACE_LEFT;
				break;
			}
			case RotationDirection:: FACE_LEFT: {
				points[0].moveRight();
				points[0].moveDown();
				points[2].moveLeft();
				points[2].moveUp();
				for (int i = 0; i < 2; i++) {
					points[3].moveLeft();
					points[3].moveUp();
				}
				shapeDirection = RotationDirection:: FACE_DOWN;
				break;
			}
			case RotationDirection:: FACE_DOWN: {
				points[0].moveUp();
				points[0].moveRight();
				points[2].moveLeft();
				points[2].moveDown();
				for (int i = 0; i < 2; i++) {
					points[3].moveLeft();
					points[3].moveDown();
				}
				shapeDirection = RotationDirection:: FACE_RIGHT;
				break;
			}
			case RotationDirection:: FACE_RIGHT: {
				points[0].moveLeft();
				points[0].moveUp();
				points[2].moveRight();
				points[2].moveDown();
				for (int i = 0; i < 2; i++) {
					points[3].moveRight();
					points[3].moveDown();
				}
				shapeDirection = RotationDirection:: FACE_UP;
				break;
			}
		}
	}
	else {
		switch (shapeDirection) {
			case RotationDirection:: FACE_UP: {
				points[0].moveRight();
				points[0].moveDown();
				points[2].moveLeft();
				points[2].moveUp();
				for (int i = 0; i < 2; i++) {
					points[3].moveLeft();
					points[3].moveUp();
				}
				shapeDirection = RotationDirection:: FACE_RIGHT;
				break;
			}
			case RotationDirection:: FACE_RIGHT: {
				points[0].moveLeft();
				points[0].moveDown();
				points[2].moveRight();
				points[2].moveUp();
				for (int i = 0; i < 2; i++) {
					points[3].moveRight();
					points[3].moveUp();
				}
				shapeDirection = RotationDirection:: FACE_DOWN;
				break;
			}
			case RotationDirection:: FACE_DOWN: {
				points[0].moveUp();
				points[0].moveLeft();
				points[2].moveRight();
				points[2].moveDown();
				for (int i = 0; i < 2; i++) {
					points[3].moveRight();
					points[3].moveDown();
				}
				shapeDirection = RotationDirection:: FACE_LEFT;
				break;
			}
			case RotationDirection:: FACE_LEFT: {
				points[0].moveRight();
				points[0].moveUp();
				points[2].moveLeft();
				points[2].moveDown();
				for (int i = 0; i < 2; i++) {
					points[3].moveLeft();
					points[3].moveDown();
				}
				shapeDirection = RotationDirection:: FACE_UP;
				break;
			}
		}
	}
}
void Shape::rotateL(ShapeMovement direction) {
	if (direction == ShapeMovement:: ROTATE_LEFT) {
		switch (shapeDirection) {
		case RotationDirection:: FACE_UP: {
				points[0].moveDown();
				points[0].moveLeft();
				points[2].moveRight();
				points[2].moveUp();
				points[3].moveUp();
				points[3].moveUp();
				shapeDirection = RotationDirection:: FACE_LEFT;
				break;
			}
		case RotationDirection:: FACE_LEFT: {
				points[0].moveDown();
				points[0].moveRight();
				points[2].moveLeft();
				points[2].moveUp();
				points[3].moveLeft();
				points[3].moveLeft();
				shapeDirection = RotationDirection:: FACE_DOWN;
				break;
			}
		case RotationDirection:: FACE_DOWN: {
				points[0].moveUp();
				points[0].moveRight();
				points[2].moveLeft();
				points[2].moveDown();
				points[3].moveDown();
				points[3].moveDown();
				shapeDirection = RotationDirection:: FACE_RIGHT;
				break;
			}
			case RotationDirection:: FACE_RIGHT: {
				points[0].moveLeft();
				points[0].moveUp();
				points[2].moveRight();
				points[2].moveDown();
				points[3].moveRight();
				points[3].moveRight();
				shapeDirection = RotationDirection:: FACE_UP;
				break;
			}
		}
	}
	else
	{
		switch (shapeDirection) {
			case RotationDirection:: FACE_UP: {
				points[0].moveDown();
				points[0].moveRight();
				points[2].moveLeft();
				points[2].moveUp();
				points[3].moveLeft();
				points[3].moveLeft();
				shapeDirection = RotationDirection:: FACE_RIGHT;
				break;
			}
			case RotationDirection:: FACE_RIGHT: {
				points[0].moveLeft();
				points[0].moveDown();
				points[2].moveRight();
				points[2].moveUp();
				points[3].moveUp();
				points[3].moveUp();
				shapeDirection = RotationDirection:: FACE_DOWN;
				break;
			}
			case RotationDirection:: FACE_DOWN: {
				points[0].moveLeft();
				points[0].moveUp();
				points[2].moveRight();
				points[2].moveDown();
				points[3].moveRight();
				points[3].moveRight();
				shapeDirection = RotationDirection:: FACE_LEFT;
				break;
			}
			case RotationDirection:: FACE_LEFT: {
				points[0].moveRight();
				points[0].moveUp();
				points[2].moveLeft();
				points[2].moveDown();
				points[3].moveDown();
				points[3].moveDown();
				shapeDirection = RotationDirection:: FACE_UP;
				break;
			}
		}
	}
}
void Shape::rotateMirrorSkew(ShapeMovement direction) {
	if (direction == ShapeMovement:: ROTATE_LEFT) {
		switch (shapeDirection) {
			case RotationDirection:: FACE_UP: {
				points[0] = points[2];
				points[2].moveDown();
				points[2].moveRight();
				points[3].moveRight();
				points[3].moveRight();
				shapeDirection = RotationDirection:: FACE_LEFT;
				break;
			}
			case RotationDirection:: FACE_LEFT: {
				points[0] = points[2];
				points[2].moveUp();
				points[2].moveRight();
				points[3].moveUp();
				points[3].moveUp();
				shapeDirection = RotationDirection:: FACE_DOWN;
				break;
			}
			case RotationDirection:: FACE_DOWN: {
				points[0] = points[2];
				points[2].moveLeft();
				points[2].moveUp();
				points[3].moveLeft();
				points[3].moveLeft();
				shapeDirection = RotationDirection:: FACE_RIGHT;
				break;
			}
			case RotationDirection:: FACE_RIGHT: {
				points[0] = points[2];
				points[2].moveLeft();
				points[2].moveDown();
				points[3].moveDown();
				points[3].moveDown();
				shapeDirection = RotationDirection:: FACE_UP;
				break;
			}
		}
	}
	else
	{
		switch (shapeDirection) {
			case RotationDirection:: FACE_UP: {
				points[2] = points[0];
				points[0].moveDown();
				points[0].moveRight();
				points[3].moveUp();
				points[3].moveUp();
				shapeDirection = RotationDirection:: FACE_RIGHT;
				break;
			}
			case RotationDirection:: FACE_LEFT: {
				points[2] = points[0];
				points[0].moveUp();
				points[0].moveRight();
				points[3].moveLeft();
				points[3].moveLeft();
				shapeDirection = RotationDirection:: FACE_UP;
				break;
			}
			case RotationDirection:: FACE_DOWN: {
				points[2] = points[0];
				points[0].moveLeft();
				points[0].moveUp();
				points[3].moveDown();
				points[3].moveDown();
				shapeDirection = RotationDirection:: FACE_LEFT;
				break;
			}
			case RotationDirection:: FACE_RIGHT: {
				points[2] = points[0];
				points[0].moveDown();
				points[0].moveLeft();
				points[3].moveRight();
				points[3].moveRight();
				shapeDirection = RotationDirection:: FACE_DOWN;
				break;
			}
		}
	}
}
void Shape::rotateSkew(ShapeMovement direction) {
	if (direction == ShapeMovement:: ROTATE_LEFT) {
		switch (shapeDirection) {
			case RotationDirection:: FACE_UP: {
				points[2] = points[0];
				points[0].moveDown();
				points[0].moveLeft();
				points[3].moveUp();
				points[3].moveUp();
				shapeDirection = RotationDirection:: FACE_LEFT;
				break;
			}
			case RotationDirection:: FACE_LEFT: {
				points[2] = points[0];
				points[0].moveDown();
				points[0].moveRight();
				points[3].moveLeft();
				points[3].moveLeft();
				shapeDirection = RotationDirection:: FACE_DOWN;
				break;
			}
			case RotationDirection:: FACE_DOWN: {
				points[2] = points[0];
				points[0].moveRight();
				points[0].moveUp();
				points[3].moveDown();
				points[3].moveDown();
				shapeDirection = RotationDirection:: FACE_RIGHT;
				break;
			}
			case RotationDirection:: FACE_RIGHT: {
				points[2] = points[0];
				points[0].moveLeft();
				points[0].moveUp();
				points[3].moveRight();
				points[3].moveRight();
				shapeDirection = RotationDirection:: FACE_UP;
				break;
			}
		}
	}
	else 
	{
		switch (shapeDirection) {
			case RotationDirection:: FACE_UP: {
				points[0] = points[2];
				points[2].moveDown();
				points[2].moveLeft();
				points[3].moveLeft();
				points[3].moveLeft();
				shapeDirection = RotationDirection:: FACE_RIGHT;
				break;
			}
			case RotationDirection:: FACE_RIGHT: {
				points[0] = points[2];
				points[2].moveLeft();
				points[2].moveUp();
				points[3].moveUp();
				points[3].moveUp();
				shapeDirection = RotationDirection::FACE_DOWN;
				break;
			}
			case RotationDirection:: FACE_DOWN: {
				points[0] = points[2];
				points[2].moveRight();
				points[2].moveUp();
				points[3].moveRight();
				points[3].moveRight();
				shapeDirection = RotationDirection:: FACE_LEFT;
				break;
			}
			case RotationDirection:: FACE_LEFT: {
				points[0] = points[2];
				points[2].moveDown();
				points[2].moveRight();
				points[3].moveDown();
				points[3].moveDown();
				shapeDirection = RotationDirection:: FACE_UP;
				break;
			}
		}
	}
}
/*************************
* Name: clearShape
* Input: none
* Output: none
* Description: Clears the shape from the console by making hre symbol a " ".

*************************/
void Shape:: clearShape() {
	setSymbol(EMPTY);
}
/*************************
* Name: setSymbol
* Input: char symbol
* Output: none
* Description: Sets the symbol of the shape.

*************************/
void Shape::setSymbol(char symbol) {
	for (int i = 0; i < 4; i++) {
		points[i].setSymbol(symbol);
	}
}
/*************************
* Name: print
* Input: none
* Output: none
* Description: Prints the shape on the console.

*************************/
void Shape::print() const {
	for (int i = 0; i < 4; i++) {
		points[i].print();
	}
}
/*************************
* Name: move
* Input: ShapeMovement movement
* Output: none
* Description: Moves the shape in the specified direction.

*************************/
void Shape::move(ShapeMovement movement) {
	switch (movement) {
	case ShapeMovement:: ROTATE_LEFT: {
		rotateLeft(shapeType);
		break;
	}
	case ShapeMovement:: ROTATE_RIGHT: {
		rotateRight(shapeType);
		break;
	}
	case ShapeMovement:: LEFT: {
		moveLeft();
		break;
	}
	case ShapeMovement:: RIGHT: {
		moveRight();
		break;
	}
	case ShapeMovement:: DROP :
		moveDown();
		break;
	}
}
/*************************
* Name: getPointInd
* Input: const Point& p1
* Output: int
* Description: Returns the index of a specified point in the shape, if the point isnt in the shape returns -1.

*************************/
int Shape::getPointInd(const Point& p1) const{
	int index = NOT_FOUND;
	for (int i = 0; i < NUM_OF_POINTS; i++) {
		if (points[i].areCoordinatesEqual(p1)) {
			index = i;
		}
	}
	return index;
}
/*************************
* Name: isShapeClear
* Input: none
* Output: bool
* Description: Checks if the shape is clear on the game board.

*************************/
bool Shape:: isShapeClear() const
{
	bool res = true;
	for (int i = 0; i < NUM_OF_POINTS && res; i++) {
		if (points[i].getSymbol() != EMPTY) {
			res = false;
		}
	}
	return res;
}
/*************************
* Name: getHighestY
* Input: none
* Output: short int
* Description: Returns the highest y-coordinate of the shape.

*************************/
short int Shape:: getHighestY() const
{

	short int highestY = points[0].getY();

	for (int i = 1; i < NUM_OF_POINTS && points[i].getSymbol() != EMPTY; ++i) {
		short int currentY = points[i].getY();
		if (currentY > highestY) {
			highestY = currentY;
		}
	}
	return highestY;
}
/*************************
* Name: setShapeColor
* Input: Color color
* Output: bool
* Description: Sets the color of the shape and returns true on success, false otherwise.
*************************/
bool Shape::setShapeColor(Point:: Color color)
{
	bool res = true;
	for (int i = 0; i < NUM_OF_POINTS&&res; i++) {
		res = points[i].setColor(color);
	}
	return res;
}
/************************
* Name: getType
* Input: None
* Output: Shape::Type (The type of the shape)
* Description: Gets the type of the shape.
************************/
Shape:: Type Shape:: getType() const
{
	return shapeType;
}
/************************
* Name: getPoints
* Input: None
* Output: Point* const (A constant pointer to the points of the shape)
* Description: Gets the array of points representing the shape.
************************/
Point* const Shape:: getPoints()
{
	return points;
}
const Point* const Shape:: getPoints() const
{
	return points;
}
/************************
* Name: isAbove
* Input: const Shape& shape (The other shape to compare against)
* Output: bool (True if this shape is above the other shape, otherwise false)
* Description: Checks if this shape is positioned above the provided shape.
************************/
bool Shape::isAbove(const Shape& shape) const
{
	bool res = true;
	for (int i = 0; i < NUM_OF_POINTS&&res; i++)
	{
		if (points[i].getX() != shape.points[i].getX())
			res = false;
	}
	return res;
}
/************************
* Name: isToTheRight
* Input: const Shape& shape (The other shape to compare against)
* Output: bool (True if this shape is to the right of the other shape, otherwise false)
* Description: Checks if this shape is positioned to the right of the provided shape.
************************/
bool Shape::isToTheRight(const Shape& shape) const
{
	return (points[0].getX() > shape.points[0].getX());
}
/************************
* Name: isToTheLeft
* Input: const Shape& shape (The other shape to compare against)
* Output: bool (True if this shape is to the left of the other shape, otherwise false)
* Description: Checks if this shape is positioned to the left of the provided shape.
************************/
bool Shape::isToTheLeft(const Shape& shape) const
{
	return (points[0].getX() < shape.points[0].getX());
}
/************************
* Name: setShapeRotationDirection
* Input: RotationDirection shapeDirection (The direction to set the shape's rotation)
* Output: bool (True if the rotation direction was set successfully, otherwise false)
* Description: Sets the rotation direction of the shape.
************************/
bool Shape:: setShapeRotationDirection(RotationDirection shapeDirection)
{
	if (shapeDirection == RotationDirection:: FACE_UP || shapeDirection == RotationDirection:: FACE_RIGHT
		|| shapeDirection == RotationDirection:: FACE_DOWN || shapeDirection == RotationDirection:: FACE_LEFT)
	{
		this->shapeDirection = shapeDirection;
		return true;
	}
	else
		return false;
}
/************************
* Name: getLowestY
* Input: None
* Output: short int (The Y coordinate of the lowest point of the shape)
* Description: Gets the Y coordinate of the lowest point of the shape.
************************/
short int Shape::getLowestY() const
{
	short int lowestY = points[0].getY(), currentY;

	for (int i = 1; i < NUM_OF_POINTS && points[i].getSymbol() != EMPTY; ++i) {
		currentY = points[i].getY();
		if (currentY < lowestY) {
			lowestY = currentY;
		}
	}
	return lowestY;
}


