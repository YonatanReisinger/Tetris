#include "Player.h"
/*************************
* Name: Player
* Input: const Board& board, const Key keys[], const char* name, int score = 0
* Output: none
* Description: Constructs a player with a game board, keys, name, and an optional score.

*************************/
Player::Player(const Board& board, const Key keys[], const string name, bool isHuman, Level level , int score) : board(board), name(name), isHuman(isHuman)
	, keys{keys[KeyInd:: LEFT_IND], keys[KeyInd::RIGHT_IND], keys[KeyInd::ROTATE_RIGHT_IND], keys[KeyInd::ROTATE_LEFT_IND], keys[KeyInd::DROP_IND] }
{
	this->board.clear();
	setScore(score);
	setCurrShape(nullptr) ;
	setLevel(level);
}
/*Player destructor*/
Player:: ~Player()
{
	if (currPlayingShape != nullptr)
		delete currPlayingShape;
}
/*************************
* Name: setScore
* Input: int score
* Output: bool
* Description: Sets the player's score and returns true on success, false otherwise.

*************************/
bool Player:: setScore(int score)
{
	bool res;
	if (score < 0)
		res = false;
	else
	{
		this->score = score;
		res = true;
	}
	return res;
}
/*************************
* Name: increaseScore
* Input: int increase
* Output: bool
* Description: Increases the player's score by a specified amount and returns true on success, false otherwise.

*************************/
bool Player::increaseScore(int increase)
{
	return setScore(score += increase);
}
/*************************
* Name: reset
* Input: none
* Output: none
* Description: Resets the player's state, including the score.

*************************/
void Player:: reset()
{
	board.clear();
	setScore(0);
	if (currPlayingShape != nullptr) {
		delete currPlayingShape;
		currPlayingShape = nullptr;
	}
}
/*************************
* Name: getKeyInd
* Input: Key inputKey
* Output: int
* Description: Returns the index of the provided key in the player's key array.

************************
*/
int Player:: getKeyInd(Key inputKey)
{
	short int i;
	int resInd = NOT_FOUND;
	if (!isHuman) // CPU player dont have keys
		return NOT_FOUND;
	// search if the input key is part of the players keys
	for (i = 0; i < NUM_OF_KEYS && resInd == NOT_FOUND; i++)
		// the input key can be either small letters or capital letters
		if (inputKey == keys[i] || inputKey + ('a' - 'A') == keys[i])
			resInd = i;
	return resInd;
}
/*************************
* Name: setCurrShape
* Input: Shape* currShape
* Output: none
* Description: Sets the player's current playing shape to the provided shape.
************************ */
void Player:: setCurrShape(Shape* currShape)
{
	currPlayingShape = currShape;
}
bool Player:: isStuck() const
{
	// a player current shape is stuck if it can't be set at all on the board or if it cant move to any direction
	return !board.canSetShapeInGameBoard(*currPlayingShape) ||
		(!canCurrShapeMove(ShapeMovement::DROP)
			&& !canCurrShapeMove(ShapeMovement::LEFT)
			&& !canCurrShapeMove(ShapeMovement::RIGHT));
}
bool Player:: canCurrShapeMove(ShapeMovement movement) const
{
	Shape tempShape(*currPlayingShape);
	tempShape.move(movement);
	return board.canSetShapeInGameBoard(tempShape);
}
Level Player:: getLevelFromKeyboard()
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
bool Player:: setLevel(Level level)
{
	if (level == Level::BEST || level == Level::GOOD || level == Level::NOVICE || level == Level::HUMAN)
	{
		this->level = level;
		return true;
	}
	else
		return false;
}
const Shape& Player:: optimizeMove()
{
	short int i, numOfRotationsPossible = 4;
	Shape tmpShape(*currPlayingShape), resShape, originalShape(*currPlayingShape);
	ShapeMovement direction = RIGHT, rotation = ShapeMovement::ROTATE_RIGHT;
	// Go through all the possible lanes on the board the shape can drop from
	while (canCurrShapeMove(direction))
	{
		currPlayingShape->move(direction);
		// Check all rotations possibilites
		for (i = 0; i < numOfRotationsPossible; i++)
		{
			// Drop the point from this specific place till it reaches the ground
			while (canCurrShapeMove(ShapeMovement::DROP))
				currPlayingShape->move(ShapeMovement::DROP);
			// Set the shape in the board in that place and check the result
			if (board.canSetShapeInGameBoard(*currPlayingShape))
			{
				board.setShapeInGameBoard(*currPlayingShape, false);
				board.clearShapeFromGameBoard(*currPlayingShape);
			}
			// CHECK THAT IT CHECKS ALL ROTATION POSSIBILITES !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			if (canCurrShapeMove(rotation))
				currPlayingShape->move(direction);
			else
				numOfRotationsPossible--;
		}
	}



	*currPlayingShape = originalShape;
	return resShape;
}
//void Player:: updateCurShapeInGame(const Game& game)
//{
//	int clearRowsForPlayerInRound = 0;
//	if (canCurrShapeMove(ShapeMovement::DROP))
//		game.moveShapeOnScreen(*currPlayingShape, ShapeMovement::DROP, GamePace::NORMAL);
//	//if the shape can't move anymore
//	else
//	{
//		// if the shape that can't move anymore is a bomb
//		if (currPlayingShape->getType() == Type::BOMB)
//		{
//			board.explodeBomb(*currPlayingShape);
//			board.dropActiveShapes();
//			board.printGameBoard();
//		}
//		// If it is a normal shape that can be set to the board
//		else if (board.canSetShapeInGameBoard(*currPlayingShape))
//		{
//			board.setShapeInGameBoard(*currPlayingShape, true);
//			increaseScore(GameConfig::SCORE_FOR_PLACING_SHAPE);
//			// print the new shape on the playing board
//			board.printGameBoard();
//		}
//		// increase the score of the player according to how many rows he cleared
//		clearRowsForPlayerInRound = board.clearFullRows();
//		// drop all the shapes, if after the drop more rows can be cleared, continue to do so
//		while (clearRowsForPlayerInRound != 0)
//		{
//			if (clearRowsForPlayerInRound == 4) // If the player scored a tetris
//				increaseScore(800);
//			else
//				increaseScore(GameConfig::SCORE_FOR_FULL_LINE * clearRowsForPlayerInRound);
//			board.dropActiveShapes();
//			board.printGameBoard();
//			clearRowsForPlayerInRound = board.clearFullRows();
//		}
//		// get a new random shape
//		setCurrShape(game.getRandomShape(board.getStartingPoint()));
//	}
//}