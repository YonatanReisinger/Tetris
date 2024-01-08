#include "Point.h"

Point::Point(int x, int y)
{
	setX(x);
	setY(y);
}
bool Point:: setX(int x)
{
	//if the x coordiante is after the end of the second board
	if (x > ((GameConfig::WIDTH + 1) * 2 + GameConfig::DISTANCE_BETWEEN_BOARDS + 1))
		return false;
	else
	{
		this->x = x;
		return true;
	}
}
bool Point:: setY(int y)
{
	//if the y coordiante is larger the fixed height of the board and its frame
	if (y > (GameConfig::HEIGHT + 1))
		return false;
	else
	{
		this->y = y;
		return true;
	}
}
int Point:: getX()
{
	return x;
}
int Point::getY()
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
void Point:: print(char ch)
{
	gotoxy();
	cout << ch;
}
bool Point:: copy(const Point* other)
{
	return setX(other->x) && setY(other->y);
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