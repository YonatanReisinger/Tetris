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
	setCurrShape(nullptr);
	setStartpoint(board.getStartingPoint());
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
int Player:: getKeyInd(Key inputKey) const
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
/************************
* Name: isStuck
* Input: None
* Output: bool (True if the current shape is stuck, False otherwise)
* Description: Checks if the player's current shape is stuck, meaning it cannot be set on the board or moved in any direction. Also checks if the shape is at the top of the board.
************************/
bool Player:: isStuck() const
{
	bool isShapeStuck, isShapeAtTopOfBoard;
	// a player current shape is stuck if it can't be set at all on the board or if it cant move to any direction
	isShapeStuck = !board.canSetShapeInGameBoard(*currPlayingShape) ||
		(!canCurrShapeMove(Shape:: ShapeMovement::DROP)
			&& !canCurrShapeMove(Shape:: ShapeMovement::LEFT)
			&& !canCurrShapeMove(Shape:: ShapeMovement::RIGHT));
	isShapeAtTopOfBoard = currPlayingShape->getLowestY() == board.getBorders()[Board::Borders::TOP_LEFT].getY();
	// if the both of them happen then the new shape is stuck on top of the board and thus the game should finish
	return isShapeStuck && isShapeAtTopOfBoard;
}
/************************
* Name: canCurrShapeMove
* Input: Shape::ShapeMovement movement (The movement to be checked)
* Output: bool (True if the current shape can move in the specified direction, False otherwise)
* Description: Checks if the player's current shape can move in the specified direction on the board.
************************/
bool Player:: canCurrShapeMove(Shape:: ShapeMovement movement) const
{
	return board.canShapeMove(*currPlayingShape, movement);
}
/************************
* Name: findBestMove
* Input: None
* Output: None
* Description: Finds the best move for the player. Since this function is not implemented for regular players, it does nothing.
************************/
void Player:: findBestMove()
{
	// A normal player doesnt have a way to find his best move
	if (typeid(this) == typeid(Player))
		return;
}
/************************
* Name: setStartpoint
* Input: const Point& startPoint (The starting point to be set)
* Output: bool (True if the starting point was set successfully, False otherwise)
* Description: Sets the starting point for the player's shapes on the board.
************************/
bool Player::setStartpoint(const Point& startPoint)
{
	if (board.isPointInBoard(startPoint))
	{
		this->startPoint = startPoint;
		return true;
	}
	else
		return false;
}
/************************
* Name: getStartPoint
* Input: None
* Output: const Point& (Reference to the starting point of the player's shapes)
* Description: Retrieves the starting point for the player's shapes on the board.
************************/
const Point& Player:: getStartPoint() const
{
	return startPoint;
}
/************************
* Name: setRandomCurrShape
* Input: GameColorStatus color (The color status of the game)
* Output: None
* Description: Sets the player's current shape to a randomly generated shape, based on the provided color status. There's a chance for a bomb shape to be generated as well.
************************/
void Player:: setRandomCurrShape(GameColorStatus color)
{
	Shape* s;
	unsigned int randomNum;
	randomNum = (rand() % 100) + 1; // Generate a random number between 1 and 100
	if (randomNum < GameConfig::CHANCE_FOR_BOMB * 100)
		s = new Shape(Shape:: Type::BOMB, startPoint, color);
	else
		s = new Shape(Shape:: Type(rand() % NUM_OF_SHAPES), startPoint, color);
	setCurrShape(s);
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