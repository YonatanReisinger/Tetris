#include "Player.h"
/*************************
* Name: Player
* Input: const Board& board, const Key keys[], const char* name, int score = 0
* Output: none
* Description: Constructs a player with a game board, keys, name, and an optional score.

*************************/
Player::Player(const Board& board, const Key keys[], const string name, int score) : board(board), name(name)
	, keys{keys[KeyInd:: LEFT_IND], keys[KeyInd::RIGHT_IND], keys[KeyInd::ROTATE_RIGHT_IND], keys[KeyInd::ROTATE_LEFT_IND], keys[KeyInd::DROP_IND] }
{
	this->board.clear();
	setScore(score);
	setCurrShape(nullptr) ;
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
	bool res = !board.canSetShapeInGameBoard(*currPlayingShape) ||
		(!canCurrShapeMove(ShapeMovement::DROP)
			&& !canCurrShapeMove(ShapeMovement::LEFT)
			&& !canCurrShapeMove(ShapeMovement::RIGHT));
	if (res == true)
		res = res;
	return res;
}
bool Player:: canCurrShapeMove(ShapeMovement movement) const
{
	return board.canShapeMove(*currPlayingShape, movement);
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