#include "Point.h"

Point::Point(int x, int y)
{
	setX(x);
	setY(y);
}
void Point::gotoxy()
{
	COORD c = {x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void Point:: setX(int x)
{
	this->x = x;
}
void Point:: setY(int y)
{
	this->y = y;
}
int Point:: getX()
{
	return x;
}
int Point::getY()
{
	return y;
}