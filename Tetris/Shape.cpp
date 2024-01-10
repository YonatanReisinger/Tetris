#include "Shape.h"

#include "Shape.h"

/*input: gets a type that represents the tetronimo type, and a point that repreesents
the starting point of the tetronimo
Creates a new shape based on the type and point*/
Shape::Shape(Type t, Point& start) {
	shapeType = type;
	/*switch (type) {
	case STRAIGHT: {

	}
	case SQUARE: {

	}

	}*/

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




