#ifndef __POINT_H__
#define __POINT_H__

// Imports ->
#include<windows.h> //for gotoxy
#include "gameConfig.h"
#include <iostream>
using namespace std;
// <- Imports

class Point {

public:
	// enums ->
	enum class Color { WHITE = (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE), RED = BACKGROUND_RED, BLUE = BACKGROUND_BLUE, GREEN = BACKGROUND_GREEN, BRWON = RED | GREEN, PURPLE = 80, GREY = 143, CYAN = 183 };
	// <- enums

	Point(short int x = 0, short int y = 0, char symbol = EMPTY, Color color = Color::WHITE);
	bool setX(short int x);
	inline short int getX() const { return x; };
	bool setY(short int y);
	inline short int getY() const { return y; };
	bool setXY(short int x, short int y);
	bool setSymbol(char symbol);
	inline char getSymbol() const { return symbol; };
	static void gotoxy(short int x, short int y); // Going to xy using coordinates
	inline void gotoxy() const { gotoxy(x, y); }; // Going to xy using a Point instance
	void print() const;
	bool moveUp();
	bool moveDown();
	bool moveLeft();
	bool moveRight();
	bool move(Directions direction);
	inline bool areCoordinatesEqual(const Point& other) const { return x == other.x && y == other.y; };
	inline Color getColor() const { return color; };
	bool setColor(Color color);
	int getHorizontalDistance(const Point& other);
	int getVerticalDistance(const Point& other);
	const double distance(const Point& other) const;
	void blink();

private:
	short int x;
	short int y;
	char symbol;
	Color color;
};
#endif //Point.h