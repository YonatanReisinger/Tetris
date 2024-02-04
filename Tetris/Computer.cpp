#include "Computer.h"
Computer::Computer(const Board& board, const Key keys[], const string name, int bestMoveScore,int score)
	: Player(board, keys, name, score)
{
	setLevel(level);
	this->bestMoveScore = bestMoveScore;
}
int Computer:: getKeyInd(Key inputKey)
{
	return NOT_FOUND;
}
Computer:: Level Computer:: getLevelFromKeyboard()
{
	Level levelChoice;
	cout << "Choose level: (a) BEST (b) GOOD and (c) NOVICE" << endl;
	do
	{
		levelChoice = (Level)_getch();
	} while (levelChoice != Level::BEST && levelChoice != Level::GOOD && levelChoice != Level::NOVICE
		&& tolower(levelChoice) != Level::BEST && tolower(levelChoice) != Level::GOOD && tolower(levelChoice) != Level::NOVICE);
	return ('a' <= levelChoice <= 'z') ? levelChoice : (Level)tolower(levelChoice);
}
bool Computer::setLevel(Level level)
{
	if (level == Level::BEST || level == Level::GOOD || level == Level::NOVICE || level == Level::HUMAN)
	{
		this->level = level;
		return true;
	}
	else
		return false;
}
void Computer:: findBestMove()
{
	short int i, numOfRotationsPossible = 4;
	Shape tmpShape(*currPlayingShape);
	// ShapeMovement currentDirection = RIGHT, currentRotation = ShapeMovement::ROTATE_RIGHT;

	for (i = 0; i < numOfRotationsPossible; i++)
	{
		// For every rotation check all the possible lanes to fall from the sides of the current shape
		evaluatePossibleMovesFromSide(ShapeMovement:: RIGHT);
		evaluatePossibleMovesFromSide(ShapeMovement::LEFT);
		// check the placement in the current lane
		setBestMoveScoreAndCurrShapeFinalState(evaluatePlacement(tmpShape), tmpShape);

		if (board.canShapeMove(tmpShape, ShapeMovement::ROTATE_RIGHT))
			tmpShape.move(ShapeMovement::ROTATE_RIGHT);
		else
			numOfRotationsPossible--;
	}
}
void Computer:: evaluatePossibleMovesFromSide(ShapeMovement direction)
{
	short int i;
	Shape tmpShape(*currPlayingShape);
	int curMoveScore = 0;
	Shape* movingPtr, horizontalShape(*currPlayingShape), verticalShape(*currPlayingShape);
	movingPtr = &horizontalShape;

	while (board.canShapeMove(horizontalShape, direction))
	{
		horizontalShape.move(direction);
		verticalShape = horizontalShape;
		// Drop the point from this specific place till it reaches the ground
		while (board.canShapeMove(verticalShape, ShapeMovement::DROP))
			verticalShape.move(ShapeMovement::DROP);

		curMoveScore = evaluatePlacement(verticalShape);
		setBestMoveScoreAndCurrShapeFinalState(curMoveScore, verticalShape);
	}

	//while (board.canShapeMove(tmpShape, direction))
	//{
	//	tmpShape.move(direction);
	//	// Drop the point from this specific place till it reaches the ground
	//	while (board.canShapeMove(tmpShape, ShapeMovement::DROP))
	//		tmpShape.move(ShapeMovement::DROP);

	//	curMoveScore = evaluatePlacement(tmpShape);
	//	setBestMoveScoreAndCurrShapeFinalState(curMoveScore, tmpShape);
	//}
}
bool Computer:: setBestMoveScoreAndCurrShapeFinalState(int newScore, const Shape& newShapeFinalState)
{
	if (newScore > bestMoveScore)
	{
		bestMoveScore = newScore;
		return setCurrShapeFinalState(newShapeFinalState);
	}
	else
		return false;
}
bool Computer::setCurrShapeFinalState(const Shape& shape)
{
	bool res;
	res = currPlayingShape->getType() == shape.getType() && board.isShapeInBoard(shape);
	if (res)
		currShapeFinalState = shape;
	return res;
}
Key Computer:: getKey()
{
	Key key;
	RotationDirection currDirection = currPlayingShape->getDirection();
	RotationDirection finalDirection = currShapeFinalState.getDirection();
	int val;
	if (currDirection != finalDirection) {
		val = (4 + finalDirection - currDirection) % 4;
		if (val == 3)
			key = keys[KeyInd::ROTATE_LEFT_IND];
		else
			key = keys[KeyInd::ROTATE_RIGHT_IND];
	}
	else if (currPlayingShape->isAbove(currShapeFinalState))
		key = keys[KeyInd::DROP_IND];
	else if (currPlayingShape->isToTheRight(currShapeFinalState))
		key = keys[KeyInd::LEFT_IND];
	else
		key = keys[KeyInd::RIGHT_IND];
	return key;
}
int Computer:: evaluatePlacement(Shape tmpShape)
{
	int moveScore = 0;
	// Set the shape in the board in that place and check the result
	if (board.canSetShapeInGameBoard(tmpShape))
	{
		board.setShapeInGameBoard(tmpShape, false);
		// based on the current state of the board return an int for the score of the move
		moveScore = board.evaluate();
		board.clearShapeFromGameBoard(tmpShape);
	}
	return moveScore;
}