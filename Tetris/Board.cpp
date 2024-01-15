#include "Board.h"
#include "gameConfig.h"

Board:: Board(const Point& topLeft, const Point& topRight, const Point& bottomLeft, const Point& bottomRight)
{
	setBorders(topLeft, topRight, bottomLeft, bottomRight);
	clear(); //when board is being made it need to be empty
	setNumOfShapes(0);
}

//Board:: Board(const Board* other)
//{
//	// might not need !!!!!!!!!!!! check !!!!!!!!!!!!!
//	// default copy constructor does the same !!!!!!
//	short int i;
//	for (i = 0; i < 4; i++)
//		borders[i] = other->borders[i];
//}
bool Board:: setBorders(const Point& topLeft, const Point& topRight, const Point& bottomLeft, const Point& bottomRight)
{
	Point borders[4] = { topLeft , topRight , bottomLeft , bottomRight };
	//check that the board has valid borders
	if (isHeightValid(borders) && isWidthValid(borders))
	{
		short int i;
		for (i = 0; i < 4; i++)
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
bool Board:: setNumOfShapes(short int num)
{
	if (num < 0 || num >(GameConfig::HEIGHT * GameConfig::WIDTH))
		return false;
	else
	{
		numOfActiveShapes = num;
		return true;
	}
}
bool Board:: setGameBoard(char boardSymbol)
{
	bool res = true;
	short int i;
	if (boardSymbol == GameConfig::BORDER_SYMBOL) // not possible to fill the game board with a char exactly like the borders
		res = false;
	for (i = 0; i < GameConfig::HEIGHT && res; i++)
		setRow(i, boardSymbol); // no need to check the value returned as here we know that the row index is valid
	return res;
}
bool Board:: setRow(short int i, char boardSymbol)
{
	bool res = true;
	short int j;
	if (i < 0 && GameConfig::HEIGHT <= i) //check if the "i" value is within the board borders
		res = false;
	else // else the "i" value is valid
	{
		short int leftBorderXVal = borders[Borders::BOTTOM_LEFT].getX(), upperBorderYVal = borders[Borders::TOP_LEFT].getY();
		for (j = 0; j < GameConfig::WIDTH; j++)
		{
			//the j cell in the row is j x values to the right of the border
			gameBoard[i][j].setXY(leftBorderXVal + j, upperBorderYVal + i);
			gameBoard[i][j].setSymbol(boardSymbol);
		}
		res = true;
	}
	return res;
}
bool Board:: setPointInGameBoardByInd(short int i, short int j, char symbol)
{
	short int leftBorderXVal = borders[Borders::BOTTOM_LEFT].getX(), upperBorderYVal = borders[Borders::TOP_LEFT].getY();
	Point tempPoint(leftBorderXVal + j, upperBorderYVal + i,symbol);
	return setPointInGameBoard(tempPoint);
}
bool Board::setPointInGameBoard(const Point& point)
{
	bool res = true;
	short int i, j, leftBorderXVal = borders[Borders::BOTTOM_LEFT].getX()
		, upperBorderYVal = borders[Borders::TOP_LEFT].getY();

	if (isPointInBoard(point)) // check that the point is inside the board ranges
	{
		//get relative place of the point
		j = point.x - leftBorderXVal;
		i = point.y - upperBorderYVal;
		// can set a place in the board just if the place is empty or you want to clear it
		if (gameBoard[i][j].getSymbol() == EMPTY || (gameBoard[i][j].getSymbol() != EMPTY && point.symbol == EMPTY))
		{
			gameBoard[i][j] = point;
			res = true;
		}
		else 	// cant change a place that is already full
			res = false;
	}
	else
		res = false;
	return res;
}
bool Board:: setShapeInGameBoard(const Shape& shape)
{
	short int i;
	bool res = true;
	for (i = 0; i < NUM_OF_POINTS && res; i++)
		res = setPointInGameBoard(shape.points[i]);
	return res;
}
inline bool Board:: isHeightValid(Point borders[4])
{
	//one end - other end + 1 = length of the line between the two types (including them)
	return ((borders[BOTTOM_LEFT].getY() - borders[TOP_LEFT].getY() + 1) == GameConfig::HEIGHT) && ((borders[BOTTOM_RIGHT].getY() - borders[TOP_RIGHT].getY() + 1) == GameConfig::HEIGHT);
}
inline bool Board:: isWidthValid(Point borders[4])
{
	// one end - other end + 1 = length of the line between the two types (including them)
	return (borders[TOP_RIGHT].getX() - borders[TOP_LEFT].getX() + 1 == GameConfig::WIDTH) && (borders[BOTTOM_RIGHT].getX() - borders[BOTTOM_LEFT].getX() + 1== GameConfig::WIDTH);
}
void Board:: print()
{
	// print both parts of the board
	printGameBoard();
	printFrame();
}
void Board:: printGameBoard()
{
	short int i, j;
	//add color after !!!!!!!!
	for (i = 0; i < GameConfig::HEIGHT; i++)
		for (j = 0; j < GameConfig::WIDTH; j++)
			gameBoard[i][j].print();
}
void Board:: printFrame()
{
	//the frame should be outside the borders of the board
	Point topLeftBorderFrame(borders[TOP_LEFT].getX() - 1, borders[TOP_LEFT].getY() - 1)
		, topRightBorderFrame(borders[TOP_RIGHT].getX() + 1, borders[TOP_RIGHT].getY() - 1)
		, bottomLeftBorderFrame(borders[BOTTOM_LEFT].getX() - 1, borders[BOTTOM_LEFT].getY() + 1)
		, bottomRightBorderFrame(borders[BOTTOM_RIGHT].getX() + 1, borders[BOTTOM_RIGHT].getY() + 1);
	printHorizontalLine(topLeftBorderFrame, topRightBorderFrame);
	printHorizontalLine(bottomLeftBorderFrame, bottomRightBorderFrame);
	printVerticalLine(topLeftBorderFrame, bottomLeftBorderFrame);
	printVerticalLine(topRightBorderFrame, bottomRightBorderFrame);
}
void Board:: printHorizontalLine(Point& leftEnd, Point& rightEnd, char symbol)
{
	//can't draw a straight line between two points that are not on in same "height"
	if (leftEnd.getY() != rightEnd.getY())
		return;
	short int x, startX = leftEnd.getX(), endX = rightEnd.getX();
	Point p(leftEnd.getX(), leftEnd.getY(), symbol);  // change to copy ctor after !!!!!!!!!
	for (x = startX; x <= endX; x++)
	{
		p.setX(x);
		p.print();
	}
}
void Board:: printVerticalLine(Point& topEnd, Point& bottomEnd, char symbol)
{
	//can't draw a straight line between two points that are not on in same "width"
	if (topEnd.getX() != bottomEnd.getX())
		return;
	short int y, startY = topEnd.getY(), endY = bottomEnd.getY();
	Point p(topEnd.getX(), topEnd.getY(), symbol);  // change to copy ctor after !!!!!!!!!
	for (y = startY; y <= endY; y++)
	{
		p.setY(y);
		p.print();
	}
}
void Board:: clear()
{
	setGameBoard(EMPTY);
}

bool Board:: clearRow(short int i)
{
	return setRow(i, EMPTY);
}
int Board:: clearFullRows()
{
	short int i, fullRowsCounter = 0;
	for (i = 0; i < GameConfig::HEIGHT; i++)
		if (isRowFull(i))
		{
			clearRow(i);
			fullRowsCounter++;
		}
	return fullRowsCounter;
}
bool Board:: isRowFull(short int i)
{
	for (Point& point : gameBoard[i])
		if (!isPointFull(point)) // if one point is not full thus the whole row is not full
			return false;
	return true;
}
bool Board::isOverflowing()
{
	return false;

	//need to check what is the definition of board over flowing in tetris !!!!!!!!!!
	

	//bool res = true;
	//short int j;
	//for (j = 0; j < GameConfig::WIDTH && res; j++)
	//	// if the highest row is full it means that the whole board is full
	//	if (gameBoard[0][j] == EMPTY) // if there is one place in the highest row which is empty then the row is not full
	//		res = false;
	//return res;
}
bool Board:: isPointFull(const Point& point)
{
	short int i,j, leftBorderXVal = borders[Borders::BOTTOM_LEFT].getX()
		, upperBorderYVal = borders[Borders::TOP_LEFT].getY();
	//get relative place of the point
	j = point.x - leftBorderXVal;
	i = point.y - upperBorderYVal;
	// if the point is on the board and it is not empty
	return isPointInBoard(point) && gameBoard[i][j].getSymbol() != EMPTY;
}
bool Board:: isPointInBoard(const Point& point)
{
	short int leftBorderXVal = borders[Borders::BOTTOM_LEFT].getX()
		, rightBorderXVal = borders[Borders::BOTTOM_RIGHT].getX()
		, upperBorderYVal = borders[Borders::TOP_LEFT].getY()
		, lowerBorderYVal = borders[Borders::BOTTOM_LEFT].getY();
	return point.x >= leftBorderXVal && point.x <= rightBorderXVal
		&& point.y >= upperBorderYVal && point.y <= lowerBorderYVal;
}
bool Board:: canPointMove(Point point, Directions direction)
{
	// if the point can move to that direction and that future place is not full then the point can move 
	return point.move(direction) && isPointInBoard(point) && !isPointFull(point);
}
bool Board:: canShapeChangeDirection(const Shape& shape, Directions direction)
{
	short int i;
	bool res = true;
	// a shape can move iff all of its points can move
	for (i = 0; i < NUM_OF_POINTS && res; i++)
		res = canPointMove(shape.points[i], direction);
	return res;
}
Point Board:: getStartingPoint()
{
	// the place that the shapes should start falling from is the middle point on the first row
	return gameBoard[0][GameConfig:: WIDTH / 2];
}
bool Board:: isShapeInBoard(const Shape& shape)
{
	short int i;
	bool res = true;
	// a shape can move iff all of its points can move
	for (i = 0; i < NUM_OF_POINTS && res; i++)
		res = isPointInBoard(shape.points[i]);
	return res;
}
bool Board:: canShapeMove(const Shape& shape, ShapeMovement movement)
{
	if (movement == ShapeMovement::LEFT || movement == ShapeMovement::RIGHT)
		return canShapeChangeDirection(shape, (Directions)movement);
	else if (movement == ShapeMovement:: DROP)
		return canShapeChangeDirection(shape, Directions:: DOWN);
	return true;
}
bool Board:: canShapeDrop(Shape& shape)
{
	short int i;
	bool res = true;
	Point tempPoint;
	// a shape can move iff all of its points can move
	for (i = 0; i < NUM_OF_POINTS && res; i++)
	{
		tempPoint = shape.points[i];
		tempPoint.move(Directions::DOWN);
		// a point can drop if either the place below is free or it is a part of the current shape 
		res = canPointMove(shape.points[i], Directions::DOWN) || shape.isPointInside(tempPoint);
	}
	return res;
}
void Board:: dropActiveShapes()
{

}