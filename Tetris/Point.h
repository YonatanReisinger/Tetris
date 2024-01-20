#ifndef __POINT_H__
#define __POINT_H__

// Imports ->
#include<windows.h> //for gotoxy
#include "gameConfig.h"
#include <iostream>
using namespace std;
// <- Imports

// Macros and enums ->
enum class Color { WHITE = (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE), RED = BACKGROUND_RED, BLUE = BACKGROUND_BLUE, GREEN = BACKGROUND_GREEN, BRWON = RED | GREEN, PURPLE = 80, GREY = 143, CYAN = 183 };
// <- Macros and enums

class Point {
private:
	short int x;
	short int y;
	char symbol;
	Color color;
	//Color color;
public:
	Point(short int x = 0, short int y = 0, char symbol = EMPTY, Color color = Color::WHITE);
	bool setX(short int x);
	short int getX();
	bool setY(short int y);
	short int getY();
	bool setXY(short int x, short int y);
	bool setSymbol(char symbol);
	char getSymbol();
	//bool setColor(Color color);
	//Color getColor();
	void gotoxy();
	void print();
	bool moveUp();
	bool moveDown();
	bool moveLeft();
	bool moveRight();
	bool move(Directions direction);
	bool areCoordinatesEqual(const Point& other) const;
	inline Color getColor();
	bool setColor(Color color);
	friend class Board;
};
#endif //Point.h