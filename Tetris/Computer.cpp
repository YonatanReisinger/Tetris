#include "Computer.h"
Computer::Computer(const Board& board, const Key keys[], const string name, Level level, int bestMoveScore,int score)
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
		setBestMoveScoreAndCurrShapeFinalState(dropShapeAndEvaluatePlacement(tmpShape), tmpShape);

		if (board.canShapeMove(tmpShape, ShapeMovement::ROTATE_RIGHT))
			tmpShape.move(ShapeMovement::ROTATE_RIGHT);
		else
			numOfRotationsPossible--;
	}
}
void Computer:: evaluatePossibleMovesFromSide(ShapeMovement direction)
{
	short int i;
	Shape *pResShape, tmpShape(*currPlayingShape);
	int curMoveScore = 0;

	while (board.canShapeMove(tmpShape, direction))
	{
		tmpShape.move(direction);
		curMoveScore = dropShapeAndEvaluatePlacement(tmpShape);
		setBestMoveScoreAndCurrShapeFinalState(curMoveScore, tmpShape);
	}
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
int Computer::dropShapeAndEvaluatePlacement(Shape tmpShape)
{
	int moveScore = 0;
	// Drop the point from this specific place till it reaches the ground
	while (board.canShapeMove(tmpShape, ShapeMovement::DROP))
		tmpShape.move(ShapeMovement::DROP);
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