#include "Board.h"
#include "gameConfig.h"

Board:: Board(const Point& topLeft, const Point& topRight, const Point& bottomLeft, const Point& bottomRight)
{
	setBorders(topLeft, topRight, bottomLeft, bottomRight);
	clear(); //when board is being made it need to be empty
	setNumOfShapes(0);
}
bool Board:: setBorders(const Point& topLeft, const Point& topRight, const Point& bottomLeft, const Point& bottomRight)
{
	Point borders[4] = { topLeft , topRight , bottomLeft , bottomRight } ;
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
bool Board:: setNumOfShapes(size_t size)
{
	if (size < 0 || size >(GameConfig::HEIGHT * GameConfig::WIDTH))
		return false;
	else
	{
		numOfActiveShapes = size;
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
	// maybe add just the points that are in the game still !!!!!!!!!!!!!!!!!!!!1
	for (i = 0; i < NUM_OF_POINTS && res; i++) // if all the points could be set on the board thus all the shape can
	{
		if (shape.points[i].symbol != EMPTY) // insert just non empty points
			res = setPointInGameBoard(shape.points[i]);
	}
	if (res == true) // add the shape to the active shape array
		activeShapes[numOfActiveShapes++] = shape;
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
	setNumOfShapes(0);
}

bool Board:: clearRow(short int i)
{
	return setRow(i, EMPTY);
}
int Board:: clearFullRows()
{
	short int i, j,k,fullRowsCounter = 0,  removedPointInd;
	for (i = 0; i < GameConfig::HEIGHT; i++)
		if (isRowFull(i))
		{
			clearRow(i);
			fullRowsCounter++;
			// clear the removed points from all the shape
			for (j = 0; j < GameConfig:: WIDTH; j++)
				for (k = 0; k < numOfActiveShapes; k++)
				{
					removedPointInd = activeShapes[k].getPointInd(gameBoard[i][j]);
					if (removedPointInd != NOT_FOUND)
						activeShapes[k].points[removedPointInd].setSymbol(EMPTY);
				}

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
	// a shape can move iff all of its active points can move
	for (i = 0; i < NUM_OF_POINTS && res; i++)
		if (shape.points[i].symbol != EMPTY)
			res = canPointMove(shape.points[i], direction);
	return res;
}
Point Board:: getStartingPoint() const
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
	else if (movement == ShapeMovement::DROP)
		return canShapeChangeDirection(shape, Directions::DOWN);
	else // rotation
		return canShapeRotate(shape, movement);
}
bool Board::canActiveShapeDrop(const Shape& shape)
{
	short int i, emptyCounter = 0;
	bool res = true;
	Point tempPoint;
	// a shape can move iff all of its points that are still in the game can move
	for (i = 0; i < NUM_OF_POINTS && res; i++)
	{
		if (shape.points[i].symbol != EMPTY)
		{
			tempPoint = shape.points[i];
			tempPoint.move(Directions::DOWN);
			// a point can drop if either the place below is free or if the place below it is part of it's own shape
			res = canPointMove(shape.points[i], Directions::DOWN)
				|| (shape.getPointInd(tempPoint) != NOT_FOUND && isPointInBoard(tempPoint));
		}
		else
			emptyCounter++;
	}
	// an empty shape can't drop
	if (emptyCounter == NUM_OF_POINTS)
		return false;
	return res;
}
void Board:: dropActiveShapes()
{
	short int i;
	bool dropped = false;
	for (i = 0; i < numOfActiveShapes; i++)
	{
		Shape& shape = activeShapes[i];
		// if after the clearing of line a shape can drop down the board, drop while it can
		while (canActiveShapeDrop(shape))
		{
			// update the place of the shape
			clearShapeFromGameBoard(shape);
			// moveShapeDownTheScreen()
			shape.moveDown();
			dropped = true;
		}
		if (dropped) // set the board in it's new place on the board
			setShapeInGameBoard(shape);
	}
}
void Board:: clearShapeFromGameBoard(Shape& shape)
{
	short int i;
	for (i = 0; i < NUM_OF_POINTS; i++)
		if (shape.points[i].symbol != EMPTY) // clear just the points that are part of the game
		{
			shape.points[i].setSymbol(EMPTY);
			setPointInGameBoard(shape.points[i]);
			shape.points[i].setSymbol(GameConfig:: SHAPE_SYMBOL);
		}
}
// a shape is stuck if it can't move to any direction
bool Board::isShapeStuck(const Shape& shape)
{
	return !canShapeChangeDirection(shape, Directions::DOWN)
		&& !canShapeChangeDirection(shape, Directions::LEFT)
		&& !canShapeChangeDirection(shape, Directions::RIGHT);
}
bool Board:: canShapeRotate(const Shape& shape, ShapeMovement movement)
{
	bool res = true;
	short int i;
	Shape tempShape(shape);
	tempShape.move(movement);
	for (i = 0; i < NUM_OF_POINTS && res; i++)
		if (shape.points[i].symbol != EMPTY)
			res = !isPointFull(shape.points[i]); // shapes can always rotate unless the new place will be full
	return res;
}