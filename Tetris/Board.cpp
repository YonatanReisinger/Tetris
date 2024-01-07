#include "Board.h"

Board:: Board(const Point& topLeft, const Point& topRight, const Point& BottomLeft, const Point& BottomRight)
{
	setBorders(topLeft, topRight, BottomLeft, BottomRight);
}
Board:: Board(const Board* other)
{
	for (auto i = 0; i < 4; i++)
		borders[i] = other->borders[i];
}
bool Board:: setBorders(const Point& topLeft, const Point& topRight, const Point& BottomLeft, const Point& BottomRight)
{
	Point borders[4] = { topLeft , topRight , BottomLeft , BottomRight };
	//check that the board has valid borders
	if (isHeightValid(borders) && isWidthValid(borders))
	{
		for (auto i = 0; i < 4; i++)
			this->borders[i] = borders[i];
		return true;
	}
	else
		return false;
}
Point* Board:: getBorders()
{
	return borders;
}
bool Board:: isHeightValid(Point borders[4])
{
	// there should be HEIGHT points between the top and bottom borders
	return ((borders[BOTTOM_LEFT].getY() - borders[TOP_LEFT].getY() + 1) == HEIGHT + 2) && ((borders[BOTTOM_RIGHT].getY() - borders[TOP_RIGHT].getY() + 1) == HEIGHT + 2);
}
bool Board:: isWidthValid(Point borders[4])
{
	// there should be WIDTH points between the left and right borders
	return (borders[TOP_RIGHT].getX() - borders[TOP_LEFT].getX() + 1 == WIDTH + 2) && (borders[BOTTOM_RIGHT].getX() - borders[BOTTOM_LEFT].getX() + 1== WIDTH + 2);
}
void Board:: print()
{
	printHorizontalLine(borders[TOP_LEFT], borders[TOP_RIGHT]);
	printHorizontalLine(borders[BOTTOM_LEFT], borders[BOTTOM_RIGHT]);
	printVerticalLine(borders[TOP_LEFT], borders[BOTTOM_LEFT]);
	printVerticalLine(borders[TOP_RIGHT], borders[BOTTOM_RIGHT]);
}
void Board:: printHorizontalLine(Point& leftEnd, Point& rightEnd, char symbol)
{
	//can't draw a straight line between two points that are not on in same "height"
	if (leftEnd.getY() != rightEnd.getY())
		return;
	int startX = leftEnd.getX(), endX = rightEnd.getX();
	Point p(startX, leftEnd.getY());  // change to copy ctor after !!!!!!!!!
	for (int x = startX; x <= endX; x++)
	{
		p.setX(x);
		p.gotoxy();
		cout << symbol;
	}
}
void Board:: printVerticalLine(Point& topEnd, Point& bottomEnd, char symbol)
{
	//can't draw a straight line between two points that are not on in same "width"
	if (topEnd.getX() != bottomEnd.getX())
		return;
	int startY = topEnd.getY(), endY = bottomEnd.getY();
	Point p(topEnd.getX(), startY);  // change to copy ctor after !!!!!!!!!
	for (int y = startY; y <= endY; y++)
	{
		p.setY(y);
		p.gotoxy();
		cout << symbol;
	}
}
bool Board:: clear()
{
	return true;
}