#ifndef __POINT_H__
#define __POINT_H__

// Imports ->
#include<windows.h> //for gotoxy
#include "gameConfig.h"
#include <iostream>
using namespace std;
// <- Imports

// Macros and enums ->
enum class Color {WHITE = FOREGROUND_WHITE,RED = FOREGROUND_RED,BLUE = FOREGROUND_BLUE,GREEN = FOREGROUND_GREEN,BROWN = 0x964B00,PURPLE = 0x80080,CYAN = 0x00FFFF,ORANGE = 0xFFA500};
// <- Macros and enums

class Point {
private:
	short int x;
	short int y;
	char symbol;
	Color color;
	//Color color;
public:
	Point(short int x = 0, short int y = 0, char symbol = EMPTY,Color color = Color::WHITE);
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