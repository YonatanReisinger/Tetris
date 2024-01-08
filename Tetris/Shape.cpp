#include "Shape.h"


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


