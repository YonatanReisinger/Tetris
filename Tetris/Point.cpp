#include "Point.h"

Point::Point(short int x, short int y, char symbol)
{
	setX(x);
	setY(y);
	setSymbol(symbol); //dasdsa
	print();
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
short int Point:: getY()
{
	return y;
}
bool Point:: setSymbol(char symbol)
{
	// we allow symbols that are chars in the ascii table
	char asciiTableStart = ' ', asciiTableEnd = '~';
	if (asciiTableStart <= symbol && symbol <= asciiTableEnd)
	{
		this->symbol = symbol;
		return true;
	}
	else
		return false;
}
char Point:: getSymbol()
{
	return symbol;
}
//bool Point:: setColor(Color color)
//{
//	// check that the input color is one of the supported colors
//	if (color == Color::RED || color == Color::BLUE || color == Color::GREEN || color == Color::WHITE)
//	{
//		this->color = color;
//		return true;
//	}
//	else
//		return false;
//}
//Color Point:: getColor()
//{
//	return color;
//}
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
void Point:: print()
{
	gotoxy();
	/*HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, WORD(color));*/
	cout << symbol;
}
bool Point:: copy(const Point& other)
{
	return setX(other.x) && setY(other.y) && setSymbol(other.symbol);
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
bool Point:: isEqual(Point other)
{
	return x == other.getX() && y == other.getY();
}