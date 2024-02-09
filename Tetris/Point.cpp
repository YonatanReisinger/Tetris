#include "Point.h"
/*************************
* Name: Point
* Input: short int x = 0, short int y = 0, char symbol = EMPTY, Color color = Color::WHITE
* Output: none
* Description: Constructs a Point with specified coordinates, symbol, and color.

*************************/
Point::Point(short int x, short int y, char symbol,Color color)
{
	setX(x);
	setY(y);
	setSymbol(symbol) ; //dasdsa
	setColor(color);
}
/*************************
* Name: setX
* Input: short int x
* Output: bool
* Description: Sets the x-coordinate of the Point and returns true on success, false otherwise.

*************************/
bool Point:: setX(short int x)
{
	bool res;
	//if the x coordiante is outside of the screen width
	if (x > GameConfig::SCREEN_WIDTH || x < 0)
		res = false;
	else
	{
		this->x = x;
		res = true;
	}
	return res;
}
/*************************
* Name: setY
* Input: short int y
* Output: bool
* Description: Sets the y-coordinate of the Point and returns true on success, false otherwise.

*************************/
bool Point:: setY(short int y)
{
	bool res;
	//if the y coordiante is larger the fixed height of the board and its frame
	if (y > GameConfig:: SCREEN_HEIGHT|| y < 0)
		res = false;
	else
	{
		this->y = y;
		res = true;
	}
	return res;
}
/*************************
* Name: setXY
* Input: short int x, short int y
* Output: bool
* Description: Sets both x and y coordinates of the Point and returns true on success, false otherwise.

*************************/
bool Point:: setXY(short int x, short int y)
{
	return setX(x) && setY(y);
}
/*************************
* Name: setSymbol
* Input: char symbol
* Output: bool
* Description: Sets the symbol of the Point and returns true on success, false otherwise.

*************************/
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
/*************************
* Name: gotoxy
* Input: none
* Output: none
* Description: Moves the console cursor to the Point's coordinates.

*************************/
void Point:: gotoxy(short int x, short int y)
{
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	cout.flush();
	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}
/*************************
* Name: print
* Input: none
* Output: none
* Description: Prints the Point's symbol at its coordinates on the console.

*************************/
void Point:: print() const
{
	gotoxy();
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (symbol == EMPTY) {
	SetConsoleTextAttribute(hStdOut, (WORD)Color::WHITE);
	}
	else {
	SetConsoleTextAttribute(hStdOut, (WORD)color);
	}
	cout << symbol;
	SetConsoleTextAttribute(hStdOut, (WORD)Color::WHITE);
}
/*************************
* Name: move
* Input: Directions direction
* Output: bool
* Description: Moves the Point in the specified direction and returns true on success, false otherwise.

*************************/
bool Point:: move(Directions direction)
{
	bool res = true;
	switch (direction)
	{
	case Directions::UP:
		res = moveUp();
		break;
	case Directions::DOWN:
		res = moveDown();
		break;
	case Directions::LEFT:
		res = moveLeft();
		break;
	case Directions::RIGHT:
		res = moveRight();
		break;
	default:
		res = false;
		break;
	}
	return res;
}
/*************************
* Name: moveUp
* Input: none
* Output: bool
* Description: Moves the Point upwards and returns true on success, false otherwise.

*************************/
bool Point:: moveUp()
{
	return setY(y - 1);
}
/*************************
* Name: moveDown
* Input: none
* Output: bool
* Description: Moves the Point downwards and returns true on success, false otherwise.

*************************/
bool Point::moveDown()
{
	return setY(y + 1);
}
/*************************
* Name: moveUp
* Input: none
* Output: bool
* Description: Moves the Point left and returns true on success, false otherwise.

*************************/
bool Point::moveLeft()
{
	return setX(x - 1);
}
/*************************
* Name: moveUp
* Input: none
* Output: bool
* Description: Moves the Point right and returns true on success, false otherwise.

*************************/
bool Point::moveRight()
{
	return setX(x + 1);
}
/*************************
* Name: setColor
* Input: Color color
* Output: bool
* Description: Sets the color of the Point and returns true on success, false otherwise.
*************************/
bool Point:: setColor(Color color)
{
	bool res = false;
	if (color == Color::WHITE || color == Color::RED || color == Color::BLUE ||
		color == Color::CYAN || color == Color::GREY || color == Color::PURPLE ||
		color == Color::BRWON || color == Color::GREEN) {
		res = true;
		this->color = color;
	}
	else {
		res = false;
	}
	return res;
}
/************************
* Name: getHorizontalDistance
* Input: const Point& other (The other point)
* Output: int (The horizontal distance between this point and the other point)
* Description: Calculates the horizontal distance between this point and another point.
************************/
int Point:: getHorizontalDistance(const Point & other)
{
	return abs(this->x - other.x);
}
/************************
* Name: getVerticalDistance
* Input: const Point& other (The other point)
* Output: int (The vertical distance between this point and the other point)
* Description: Calculates the vertical distance between this point and another point.
************************/
int Point:: getVerticalDistance(const Point& other)
{
	return abs(this->y - other.y);
}
/************************
* Name: distance
* Input: const Point& other (The other point)
* Output: double (The distance between this point and the other point)
* Description: Calculates the Euclidean distance between this point and another point in 2D space.
************************/
const double Point::distance(const Point& other) const
{
	return sqrt(pow(this->x - other.x, 2) + pow(this->y - other.y, 2));
}
/************************
* Name: blink
* Input: None
* Output: None
* Description: Makes the point blink on the screen by temporarily hiding its symbol and then restoring it after a brief delay.
************************/
void Point:: blink()
{
	char symbol = this->symbol;
	setSymbol(EMPTY);
	print();
	Sleep((DWORD)GamePace:: BLINKING_PACE);
	setSymbol(symbol);
	print();
	Sleep((DWORD)GamePace::BLINKING_PACE);
}