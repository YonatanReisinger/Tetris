#include "Board.h"
#include "gameConfig.h"

/************************
* Name: Board::Board
* Input: const Point& topLeft, const Point& topRight, const Point& bottomLeft, const Point& bottomRight
* Output: None
* Description: Constructor for the Board class. Initializes the board with the specified corners and sets it to be empty.
************************/
Board:: Board(const Point& topLeft, const Point& topRight, const Point& bottomLeft, const Point& bottomRight)
{
	setBorders(topLeft, topRight, bottomLeft, bottomRight);
	clear(); //when board is being made it need to be empty
	setNumOfShapes(0);
}
/************************
* Name: Board::setBorders
* Input: const Point& topLeft, const Point& topRight, const Point& bottomLeft, const Point& bottomRight
* Output: bool representing success (true) or failure (false)
* Description: Checks that the board has valid borders and sets them based on the provided corner points.
************************/
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
/************************
* Name: Board::setNumOfShapes
* Input: size_t size (Number of active shapes to set)
* Output: bool representing success (true) or failure (false)
* Description: Sets the number of active shapes on the board. Validates that the size is within a valid range.
************************/
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
/************************
* Name: Board::setGameBoard
* Input: char boardSymbol (Character symbol to set for the entire game board)
* Output: bool representing success (true) or failure (false)
* Description: Sets the entire game board with the specified symbol, except for the borders.
************************/
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
/************************
* Name: Board::setRow
* Input: short int i (Row index), char boardSymbol (Character symbol to set for the row)
* Output: bool representing success (true) or failure (false)
* Description: Sets a specific row in the game board with the specified symbol.
************************/
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
/************************
* Name: Board::setPointInGameBoard
* Input: const Point& point (Point to set on the game board)
* Output: bool representing success (true) or failure (false)
* Description: Sets a specific point on the game board with the provided point's symbol.
************************/
bool Board::setPointInGameBoard(const Point& point)
{
	bool res = true;
	short int i, j, leftBorderXVal = borders[Borders::BOTTOM_LEFT].getX()
		, upperBorderYVal = borders[Borders::TOP_LEFT].getY();

	if (isPointInBoard(point)) // check that the point is inside the board ranges
	{
		//get relative place of the point
		j = point.getX() - leftBorderXVal;
		i = point.getY() - upperBorderYVal;
		// can set a place in the board just if the place is empty or you want to clear it
		if (gameBoard[i][j].getSymbol() == EMPTY || (gameBoard[i][j].getSymbol() != EMPTY && point.getSymbol() == EMPTY))
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
/************************
* Name: Board::setShapeInGameBoard
* Input: const Shape& shape (Shape to set on the game board), bool isShapeNew (Flag indicating whether the shape is new)
* Output: bool representing success (true) or failure (false)
* Description: Sets all non-empty points of a shape on the game board. If the shape is new, adds it to the array of active shapes.
************************/
bool Board:: setShapeInGameBoard(const Shape& shape, bool isShapeNew)
{
	short int i;
	if (canSetShapeInGameBoard(shape))
	{
		for (i = 0; i < NUM_OF_POINTS; i++)
		{
			if (shape.points[i].getSymbol() != EMPTY) // insert just non empty points
				setPointInGameBoard(shape.points[i]);
		}
		if (isShapeNew) // add an new shape to the active shape array in its correct place
			insertShapeToArr(shape);
		return true;
	}
	else
		return false;
}
/************************
* Name: Board::insertShapeToArr
* Input: const Shape& newShape (New shape to insert into the array)
* Output: None
* Description: Inserts a new shape into the array of active shapes at the appropriate position based on its highest y-coordinate.
************************/
void Board:: insertShapeToArr(const Shape& newShape) {
	// Get the y-coordinate of the new shape
	short int newY = newShape.getHighestY(), i, insertIndex = 0;
	// Find the correct position to insert the new shape based on y-coordinate
	while (insertIndex < numOfActiveShapes && activeShapes[insertIndex].getHighestY() > newY) {
		insertIndex++;
	}
	// Shift existing shapes to make room for the new shape
	for (i = numOfActiveShapes; i > insertIndex; --i) {
		activeShapes[i] = activeShapes[i - 1];
	}
	// Insert the new shape at the correct position
	activeShapes[insertIndex] = newShape;
	// Increment the count of active shapes
	numOfActiveShapes++;
}
/************************
* Name: Board::isHeightValid
* Input: Point borders[4] (Array of four Point objects representing the borders)
* Output: bool representing validity of height
* Description: Checks if the height of the board is valid based on the given borders.
************************/
inline bool Board:: isHeightValid(Point borders[4]) const
{
	//one end - other end + 1 = length of the line between the two types (including them)
	return ((borders[BOTTOM_LEFT].getY() - borders[TOP_LEFT].getY() + 1) == GameConfig::HEIGHT) && ((borders[BOTTOM_RIGHT].getY() - borders[TOP_RIGHT].getY() + 1) == GameConfig::HEIGHT);
}
/************************
* Name: Board::isWidthValid
* Input: Point borders[4] (Array of four Point objects representing the borders)
* Output: bool representing validity of width
* Description: Checks if the width of the board is valid based on the given borders.
************************/
inline bool Board:: isWidthValid(Point borders[4]) const
{
	// one end - other end + 1 = length of the line between the two types (including them)
	return (borders[TOP_RIGHT].getX() - borders[TOP_LEFT].getX() + 1 == GameConfig::WIDTH) && (borders[BOTTOM_RIGHT].getX() - borders[BOTTOM_LEFT].getX() + 1== GameConfig::WIDTH);
}
/************************
* Name: Board::print
* Description: Prints both parts of the board - the game board and its frame.
************************/
void Board:: print() const
{
	// print both parts of the board
	printGameBoard();
	printFrame();
}
/************************
* Name: Board::printGameBoard
* Description: Prints the game board.
************************/
void Board:: printGameBoard() const
{
	short int i, j;
	for (i = 0; i < GameConfig::HEIGHT; i++)
		for (j = 0; j < GameConfig::WIDTH; j++)
			gameBoard[i][j].print();
}
/************************
* Name: Board::printFrame
* Description: Prints the frame outside the borders of the board.
************************/
void Board:: printFrame() const
{
	//the frame should be outside the borders of the board
	Point topLeftBorderFrame(borders[TOP_LEFT].getX() - 1, borders[TOP_LEFT].getY())
		, topRightBorderFrame(borders[TOP_RIGHT].getX() + 1, borders[TOP_RIGHT].getY())
		, bottomLeftBorderFrame(borders[BOTTOM_LEFT].getX() - 1, borders[BOTTOM_LEFT].getY() + 1)
		, bottomRightBorderFrame(borders[BOTTOM_RIGHT].getX() + 1, borders[BOTTOM_RIGHT].getY() + 1);
	printHorizontalLine(bottomLeftBorderFrame, bottomRightBorderFrame);
	printVerticalLine(topLeftBorderFrame, bottomLeftBorderFrame);
	printVerticalLine(topRightBorderFrame, bottomRightBorderFrame);
}
/************************
* Name: Board::printHorizontalLine
* Input: Point& leftEnd, Point& rightEnd, char symbol (Character symbol for the line)
* Output: None
* Description: Prints a horizontal line between two points.
************************/
void Board:: printHorizontalLine(Point& leftEnd, Point& rightEnd, char symbol) const
{
	//can't draw a straight line between two points that are not on in same "height"
	if (leftEnd.getY() != rightEnd.getY())
		return;
	short int x, startX = leftEnd.getX(), endX = rightEnd.getX();
	Point p(leftEnd);
	p.setSymbol(symbol);
	for (x = startX; x <= endX; x++)
	{
		p.setX(x);
		p.print();
	}
}
/************************
* Name: Board::printVerticalLine
* Input: Point& topEnd, Point& bottomEnd, char symbol (Character symbol for the line)
* Output: None
* Description: Prints a vertical line between two points.
************************/
void Board:: printVerticalLine(Point& topEnd, Point& bottomEnd, char symbol) const
{
	//can't draw a straight line between two points that are not on in same "width"
	if (topEnd.getX() != bottomEnd.getX())
		return;
	short int y, startY = topEnd.getY(), endY = bottomEnd.getY();
	Point p(topEnd);
	p.setSymbol(symbol);
	for (y = startY; y <= endY; y++)
	{
		p.setY(y);
		p.print();
	}
}
/************************
* Name: Board::clear
* Description: Clears the game board and resets the number of active shapes.
************************/
void Board:: clear()
{
	setGameBoard(EMPTY);
	setNumOfShapes(0);
}
/************************
* Name: Board::isRowFull
* Input: short int i (Row index to check)
* Output: bool representing whether the row is full (true) or not (false)
* Description: Checks if the specified row is full.
************************/
bool Board:: isRowFull(short int row) const
{
	for (const Point& point : gameBoard[row])
		if (!isPointFull(point)) // if one point is not full thus the whole row is not full
			return false;
	return true;
}
/************************
* Name: Board::isPointFull
* Input: const Point& point (Point to check)
* Output: bool representing whether the point is full (true) or not (false)
* Description: Checks if the specified point is full.
************************/
bool Board:: isPointFull(const Point& point) const
{
	short int i,j, leftBorderXVal = borders[Borders::BOTTOM_LEFT].getX()
		, upperBorderYVal = borders[Borders::TOP_LEFT].getY();
	//get relative place of the point
	j = point.getX() - leftBorderXVal;
	i = point.getY() - upperBorderYVal;
	// if the point is on the board and it is not empty
	return isPointInBoard(point) && gameBoard[i][j].getSymbol() != EMPTY;
}
/************************
* Name: Board::isPointInBoard
* Input: const Point& point (Point to check)
* Output: bool representing whether the point is in the board (true) or not (false)
* Description: Checks if the specified point is within the board boundaries.
************************/
bool Board:: isPointInBoard(const Point& point) const
{
	short int leftBorderXVal = borders[Borders::BOTTOM_LEFT].getX()
		, rightBorderXVal = borders[Borders::BOTTOM_RIGHT].getX()
		, upperBorderYVal = borders[Borders::TOP_LEFT].getY()
		, lowerBorderYVal = borders[Borders::BOTTOM_LEFT].getY();
	return point.getX() >= leftBorderXVal && point.getX() <= rightBorderXVal
		&& point.getY() >= upperBorderYVal && point.getY() <= lowerBorderYVal;
}
/************************
* Name: Board::canPointMove
* Input: Point point (Point to check), Directions direction (Direction to move)
* Output: bool representing whether the point can move (true) or not (false)
* Description: Checks if the specified point can move in the given direction.
************************/
bool Board:: canPointMove(Point point, Directions direction) const
{
	// if the point can move to that direction and that future place is not full then the point can move 
	return point.move(direction) && isPointInBoard(point) && !isPointFull(point);
}
/************************
* Name: Board::isShapeInBoard
* Input: const Shape& shape (Shape to check)
* Output: bool representing whether the entire shape is within the board (true) or not (false)
* Description: Checks if the entire shape is within the board boundaries.
************************/
bool Board:: isShapeInBoard(const Shape& shape) const
{
	short int i;
	bool res = true;
	// a shape can move iff all of its active points can move
	for (i = 0; i < NUM_OF_POINTS && shape.points[i].getSymbol() != EMPTY && res; i++)
		res = isPointInBoard(shape.points[i]);
	return res;
}
/************************
* Name: Board::clearFullRows
* Input: None
* Output: int representing the number of cleared rows
* Description: Clears any full rows on the game board and returns the count of cleared rows.
************************/
int Board::clearFullRows()
{
	short int i, j, k, fullRowsCounter = 0, removedPointInd;
	for (i = GameConfig::HEIGHT - 1; i >= 0; i--)
	{
		if (isRowFull(i))
		{
			//clearRow(i);
			// clear the removed points from all the shapes and move down the points that are above the line of clearence
			updateActiveShapes(i);
			fullRowsCounter++;
		}
	}
	return fullRowsCounter;
}
/************************
* Name: Board::updateActiveShapes
* Input: short int clearedRowInd (The index of the row that has been cleared)
* Output: None
* Description: Updates the positions of points in all active shapes after a row has been cleared.
  Points above the cleared row are dropped, points in the cleared row are cleared, and the rest are reset to their original symbol.
  If clearing rows results in a whole shape becoming empty, it is removed from the array of active shapes.
************************/
void Board:: updateActiveShapes(short int clearedRowInd)
{
	short int i, j;
	for (i = 0; i < numOfActiveShapes; i++)
	{
		// temporarly remove the active shape from the board
		clearShapeFromGameBoard(activeShapes[i]);
		for (j = 0; j < NUM_OF_POINTS; j++)
		{
			// adjust the places of points of the shape according to the line cleared
			if (activeShapes[i].points[j].getSymbol() != EMPTY)
			{
				// if above the line, drop it's points
				if (activeShapes[i].points[j].getY() <= clearedRowInd)
					activeShapes[i].points[j].moveDown();
				//if the point is in the row of clearence, clear it
				else if (activeShapes[i].points[j].getY() == (clearedRowInd + 1)) ///////////////////////
					activeShapes[i].points[j].setSymbol(EMPTY);
				// if it is a point that didnt change, get it back to its original point on the board
				else
					activeShapes[i].points[j].setSymbol(GameConfig:: SHAPE_SYMBOL);
			}
		}
		if (activeShapes[i].isShapeClear()) // if by clearinf the full rows a whole shape is empty 
		{
			removeActiveShapeFromArr(activeShapes[i], i);
			i--;
		}
	}
	// return all the active shapes to the board in their new place
	for (i = 0; i < numOfActiveShapes; i++)
		setShapeInGameBoard(activeShapes[i], false);
}
/************************
* Name: Board::dropActiveShapes
* Description: Drops the active shapes on the board as far down as possible.
************************/
void Board:: dropActiveShapes()
{
	short int i;
	bool dropped = false;
	for (i = 0 ; i < numOfActiveShapes; i++)
	{
		Shape& shape = activeShapes[i];
		// if after the clearing of line a shape can drop down the board, drop while it can
		while (canActiveShapeDrop(shape))
		{
			// update the place of the shape
			clearShapeFromGameBoard(shape);
			shape.moveDown();
			dropped = true;
		}
		if (dropped) // set the board in it's new place on the board
			setShapeInGameBoard(shape, false);
	}
}
/************************
* Name: Board::canActiveShapeDrop
* Input: const Shape& shape (Active shape to check)
* Output: bool representing whether the active shape can drop down (true) or not (false)
* Description: Checks if the active shape can drop down on the board.
************************/
bool Board::canActiveShapeDrop(const Shape& shape) const
{
	short int i, emptyCounter = 0,tempPointInd;
	bool res = true;
	Point tempPoint;
	// a shape can move iff all of its points that are still in the game can move
	for (i = 0; i < NUM_OF_POINTS && res; i++)
	{
		// check just the non empry points that can drop which are above the line of clearance
		if (shape.points[i].getSymbol() != EMPTY)
		{
			tempPoint = shape.points[i];
			tempPoint.move(Directions::DOWN);
			tempPointInd = shape.getPointInd(tempPoint);
			// a point can drop if either the place below is free or if the place below it is part of it's own shape active points
			res = canPointMove(shape.points[i], Directions::DOWN)
				|| (tempPointInd != NOT_FOUND && shape.points[tempPointInd].getSymbol() != EMPTY && isPointInBoard(tempPoint));
		}
		else if (shape.points[i].getSymbol() == EMPTY)
			emptyCounter++;
	}
	// an empty shape can't drop and also a shape that does not have one point that can drop 
	if (emptyCounter == NUM_OF_POINTS)
		return false;
	return res;
}
/************************
* Name: Board::clearShapeFromGameBoard
* Input: Shape& shape (Shape to clear from the game board)
* Output: None
* Description: Clears all points of the specified shape from the game board.
************************/
void Board:: clearShapeFromGameBoard(Shape& shape)
{
	short int i;
	for (i = 0; i < NUM_OF_POINTS; i++)
	{
		if (shape.points[i].getSymbol() != EMPTY) // clear just the points that are part of the game
		{
			shape.points[i].setSymbol(EMPTY);
			setPointInGameBoard(shape.points[i]);
			shape.points[i].setSymbol(GameConfig::SHAPE_SYMBOL);
		}
	}
}
/************************
* Name: Board::removeActiveShapeFromArr
* Input: Shape& shape (Shape to remove), int shapeInd (Index of the shape in the array)
* Output: None
* Description: Removes the specified shape from the array of active shapes.
************************/
void Board:: removeActiveShapeFromArr(Shape& shape, int shapeInd)
{
	int i;
	// Shift elements in the array to remove the shape at shapeInd
	for (i = shapeInd; i < numOfActiveShapes - 1; i++)
	{
		activeShapes[i] = activeShapes[i + 1];
	}
	// Decrement the number of active shapes
	numOfActiveShapes--;
}
/************************
* Name: Board::canSetShapeInGameBoard
* Input: const Shape& shape (Shape to check)
* Output: bool representing whether the entire shape can be set on the game board (true) or not (false)
* Description: Checks if the entire shape can be set on the game board without any conflicts
* ************************/
bool Board:: canSetShapeInGameBoard(const Shape& shape) const
{
	short int i;
	bool res = true;
	// if all the points could be set on the board thus all the shape can
	for (i = 0; i < NUM_OF_POINTS && (shape.points[i].getSymbol() != EMPTY) && res; i++)
		res = !isPointFull(shape.points[i]) && isPointInBoard(shape.points[i]);
	return res;
}
/************************
* Name: Board::explodeBomb
* Input: Shape& bomb (The bomb shape to explode)
* Output: None
* Description: Simulates the explosion of a bomb shape on the game board, clearing points within its explosion range.
************************/
void Board::explodeBomb(Shape& bomb)
{
	short int i, j;
	Point& bombPoint = bomb.points[0];
	for (i = 0; i < 3; i++) // Make the bomb "explode" by making it blink 3 times 
		bombPoint.blink();
	// update all the active shapes in the board according to the exploding of the bomb
	for (i = 0; i < numOfActiveShapes; i++)
	{
		// temporarly remove the active shape from the board
		clearShapeFromGameBoard(activeShapes[i]);
		// adjust the places of points of the shape according to the line cleared
		for (j = 0; j < NUM_OF_POINTS && activeShapes[i].points[j].getSymbol() != EMPTY; j++)
		{
			if (activeShapes[i].points[j].distance(bombPoint) <= GameConfig::BOMB_EXPLOSION_RANGE)
				activeShapes[i].points[j].setSymbol(EMPTY);
			else
				activeShapes[i].points[j].setSymbol(GameConfig:: SHAPE_SYMBOL);
		}
		if (activeShapes[i].isShapeClear()) // if by bombing a whole shape is empty 
		{
			removeActiveShapeFromArr(activeShapes[i], i);
			i--;
		}
	}
	// return all the active shapes to the board in their new place
	for (i = 0; i < numOfActiveShapes; i++)
		setShapeInGameBoard(activeShapes[i], false);
}
/************************
* Name: Board::canShapeMove
* Input: const Shape& shape (The shape to check), Shape::ShapeMovement movement (The movement to check)
* Output: bool representing whether the shape can move in the specified direction
* Description: Checks if the specified shape can move in the given direction without colliding with other shapes or going out of bounds.
************************/
bool Board::canShapeMove(const Shape& shape, Shape:: ShapeMovement movement) const
{
	Shape tempShape = shape;
	tempShape.move(movement);
	return canSetShapeInGameBoard(tempShape);
}
/************************
* Name: Board::getGameBoard
* Output: gameBoardPointer
* Description: Returns a pointer to the game board.
************************/
gameBoardPointer Board:: getGameBoard() const
{
	return gameBoard;
}
