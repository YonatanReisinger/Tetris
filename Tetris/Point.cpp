#include "Point.h"

Point::Point(short int x, short int y)
{
	setX(x);
	setY(y);
}
bool Point:: setX(short int x)
{
	bool res;
	//if the x coordiante is after the end of the frame of the second board
	if ((x > ((GameConfig::WIDTH + 2) * 2 + GameConfig::DISTANCE_BETWEEN_BOARDS)) || x < 0)
		res = false;
	else
	{
		this->x = x;
		res = true;
	}
	return res;
}
bool Point:: setY(short int y)
{
	bool res;
	//if the y coordiante is larger the fixed height of the board and its frame
	if ((y > (GameConfig::HEIGHT + 1)) || y < 0)
		res = false;
	else
	{
		this->y = y;
		res = true;
	}
	return res;
}
short int Point:: getX()
{
	return x;
}
short int Point::getY()
{
	return y;
}
void Point::gotoxy()
{
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	cout.flush();
	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}
void Point:: print(char symbol)
{
	gotoxy();
	cout << symbol;
}
bool Point:: copy(const Point& other)
{
	return setX(other.x) && setY(other.y);
}
bool Point:: moveUp()
{
	return setY(y - 1);
}
bool Point::moveDown()
{
	return setY(y + 1);
}
bool Point::moveLeft()
{
	return setX(x - 1);
}
bool Point::moveRight()
{
	return setX(x + 1);
}