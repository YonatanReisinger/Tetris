#include "Computer.h"
Computer::Computer(const Board& board, const Key keys[], const string name, int bestMoveScore,int score)
	: Player(board, keys, name, score)
{
	setLevel(level);
	this->bestMoveScore = bestMoveScore;
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
Key Computer::getKey() const
{
	Key key;
	Shape:: RotationDirection currDirection = currPlayingShape->getDirection();
	Shape:: RotationDirection finalDirection = currShapeFinalState.getDirection();
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

bool Computer:: setCurrShapeFinalState(const Shape& shape)
{
	bool res;
	res = currPlayingShape->getType() == shape.getType() && board.isShapeInBoard(shape);
	if (res)
		currShapeFinalState = shape;
	return res;
}
void Computer:: findBestMove()
{
	short int i, numOfRotationsPossible = 4;
	Shape tmpShape(*currPlayingShape);
	setBestMoveScore(0); // Reset the best move score because Each cuurent shape has a different best move score
	
	if (shouldMakeRandomMove())
	{
		findRandomMove();
		return;
	}

	// else, the computer should find the best move possible
	for (i = 0; i < numOfRotationsPossible; i++)
	{
		// For every rotation check all the possible lanes to fall from the sides of the current shape
		evaluatePossibleMovesFromSide(tmpShape, Shape:: ShapeMovement:: RIGHT);
		evaluatePossibleMovesFromSide(tmpShape, Shape:: ShapeMovement::LEFT);
		// check the placement in the current lane
		updateBestMoveScoreAndCurrShapeFinalState(evaluatePlacement(tmpShape), tmpShape);

		if (tmpShape.getType() == Shape:: Type::BOMB) // No need to rotate a bomb
			break;
		if (board.canShapeMove(tmpShape, Shape:: ShapeMovement::ROTATE_RIGHT))
			tmpShape.move(Shape:: ShapeMovement::ROTATE_RIGHT);
		else
			numOfRotationsPossible--;
	}
}
void Computer:: evaluatePossibleMovesFromSide(const Shape& tmpShape, Shape:: ShapeMovement direction)
{
	int moveScore = 0;
	Shape horizontalShape(tmpShape), verticalShape(tmpShape);

	while (board.canShapeMove(horizontalShape, direction))
	{
		horizontalShape.move(direction);
		verticalShape = horizontalShape;
		// Drop the point from this specific place till it reaches the ground
		while (board.canShapeMove(verticalShape, Shape:: ShapeMovement::DROP))
			verticalShape.move(Shape:: ShapeMovement::DROP);

		moveScore = evaluatePlacement(verticalShape);
		updateBestMoveScoreAndCurrShapeFinalState(moveScore, verticalShape);
	}
}
bool Computer:: updateBestMoveScoreAndCurrShapeFinalState(int newScore, const Shape& newShapeFinalState)
{
	return newScore > bestMoveScore ? setBestMoveScore(newScore) && setCurrShapeFinalState(newShapeFinalState) : false;
}
bool Computer::setBestMoveScore(int newScore)
{
	bestMoveScore = newScore;
	return true;
}
int Computer:: evaluatePlacement(Shape tmpShape)
{
	int moveScore = 0;
	// Set the shape in the board in that place and check the result
	if (board.canSetShapeInGameBoard(tmpShape))
	{
		board.setShapeInGameBoard(tmpShape, false);
		// based on the current state of the board return an int for the score of the move
		moveScore = tmpShape.getType() != Shape:: Type:: BOMB ? evaluate() : evaluate(tmpShape);
		board.clearShapeFromGameBoard(tmpShape);
	}
	return moveScore;
}
Shape Computer:: getcurrShapeFinalState()
{
	return currShapeFinalState;
}
int Computer::evaluate() const
{
	short int score = 0, maxHeight = NOT_FOUND, holesPenalty = 0, fullRows = 0, scorePerFilledRow, scorePerHeight;

	calculateEvaluationParameters(maxHeight, holesPenalty, fullRows);

	if (maxHeight <= GameConfig::THRESHOLD_FOR_DANGEROUS_HEIGHT)
	{
		scorePerFilledRow = GameConfig::SCORE_PER_FILLED_ROW;
		scorePerHeight = GameConfig::SCORE_PER_HEIGHT;
	}
	else // The shapes in the board are to high, thus clearing rows and reducing height is more important
	{
		scorePerFilledRow = GameConfig::DANGEROUS_SCORE_PER_FILLED_ROW;
		scorePerHeight = GameConfig:: DANGEROUS_SCORE_PER_HEIGHT;
	}
	// Increment score based on the number of filled rows
	score += fullRows * scorePerFilledRow;
	// Increment score based on the height of the highest occupied point
	score += (GameConfig::HEIGHT - maxHeight) * scorePerHeight;
	// Deduct score based on the number of holes
	score -= holesPenalty;

	return score;
}
void Computer::calculateEvaluationParameters(short int& maxHeight, short int& holesPenalty, short int& fullRows) const
{
	short int row, col;
	gameBoardPointer gameBoardP = board.getGameBoard();

	maxHeight = NOT_FOUND;
	holesPenalty = fullRows = 0;

	for (row = 0; row < GameConfig::HEIGHT; ++row)
	{
		// Check for full rows
		fullRows += board.isRowFull(row);
		for (col = 0; col < GameConfig::WIDTH; ++col)
		{
			// A blocked point is an empty point that cant be reached easily. each direction it is blocked more points will be deducted from the move score
			if (board.isPointFull(gameBoardP[row][col]))
			{
				if (maxHeight == NOT_FOUND) // if the maxHeight was not found yet, update it
					maxHeight = GameConfig::HEIGHT - row;
				continue;
			}
			// Calculate the penalty for holes in that point
			holesPenalty += getBlockedFromAbovePenalty(row, col);
			holesPenalty += getBlockedFromSidePenalty(row, col);
		}
	}
}
int Computer::getBlockedFromAbovePenalty(int row, int col) const
{
	int i, penalty = 0;
	gameBoardPointer gameBoardP = board.getGameBoard();

	// If a point is blocked from above. the furether away it is blocked the less the penalty is
	for (i = 1; i <= 3; i++)
		if (row - i >= 0 && board.isPointFull(gameBoardP[row - i][col]))
			penalty += GameConfig::HOLES_BLOCKED_FROM_ABOVE_PENALTY / i;

	return penalty;
}

int Computer::getBlockedFromSidePenalty(int row, int col) const
{
	int penalty = 0;
	gameBoardPointer gameBoardP = board.getGameBoard();

	// If a point is blocked from the left 
	if (col > 0 && board.isPointFull(gameBoardP[row][col - 1]))
		penalty += GameConfig::HOLES_BLOCKED_FROM_SIDE_PENALTY;
	// If a point is blocked from the right
	if (col < GameConfig::WIDTH - 1 && board.isPointFull(gameBoardP[row][col + 1]))
		penalty += GameConfig::HOLES_BLOCKED_FROM_SIDE_PENALTY;
	return penalty;
}
int Computer:: evaluate(Shape& bomb) const
{
	short int row, col, pointsInBombRange = 0;
	gameBoardPointer gameBoardP = board.getGameBoard();

	for (row = 0; row < GameConfig::HEIGHT; ++row)
		for (col = 0; col < GameConfig::WIDTH; ++col)
			if (board.isPointFull(gameBoardP[row][col]) && bomb.getPoints()[0].distance(gameBoardP[row][col]) <= GameConfig::BOMB_EXPLOSION_RANGE)
				pointsInBombRange++;

	return pointsInBombRange;
}
bool Computer::shouldMakeRandomMove() const
{
	unsigned int randomNum;
	float chanceForRandomMove;

	if (level != Level::BEST)
	{
		chanceForRandomMove = (level == Level::GOOD) ? GameConfig::CHANCE_FOR_GOOD_CPU_RANDOM_MOVE : GameConfig::CHANCE_FOR_NOVICE_CPU_RANDOM_MOVE;
		randomNum = (rand() % 100) + 1; // Generate a random number between 1 and 100
		return (randomNum <= (chanceForRandomMove * 100));
	}
	else
		return false;
}
void Computer:: findRandomMove()
{
	Shape tmpShape;
	short int i, horizontalMovement, randomNumOfRotations;
	do
	{
		tmpShape = *currPlayingShape;
		if (tmpShape.getType() != Shape::Type::BOMB)
		{
			randomNumOfRotations = rand() % 4;
			for (i = 0; i < randomNumOfRotations && board.canShapeMove(tmpShape, Shape::ShapeMovement::ROTATE_RIGHT); ++i)
				tmpShape.move(Shape::ShapeMovement::ROTATE_RIGHT);
		}
		// randomize the location across the X-axis (between 6 moves to the right and 6 moves to the left)
		horizontalMovement = (rand() % GameConfig::WIDTH) - (GameConfig::WIDTH / 2);
		for (i = 0; i < abs(horizontalMovement); ++i)
		{
			if (horizontalMovement > 0) //for right movement
				tmpShape.moveRight();
			else //for left movement
				tmpShape.moveLeft();
		}
		// Drop the point from this specific place till it reaches the ground
		while (board.canShapeMove(tmpShape, Shape:: ShapeMovement::DROP))
			tmpShape.move(Shape:: ShapeMovement::DROP);

	} while (!board.canSetShapeInGameBoard(tmpShape)); // try until you find a random move that can be set on the board
	setCurrShapeFinalState(tmpShape);
}