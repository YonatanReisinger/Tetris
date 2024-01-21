#include "Player.h"
/*************************
* Name: Player
* Input: const Board& board, const Key keys[], const char* name, int score = 0
* Output: none
* Description: Constructs a player with a game board, keys, name, and an optional score.

*************************/
Player::Player(const Board& board, const Key keys[], const char* name, int score): board(board)
	, keys{keys[KeyInd:: LEFT_IND], keys[KeyInd::RIGHT_IND], keys[KeyInd::ROTATE_RIGHT_IND], keys[KeyInd::ROTATE_LEFT_IND], keys[KeyInd::DROP_IND] }
{
	setName(name);
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
* Name: setName
* Input: const char* name
* Output: bool
* Description: Sets the player's name and returns true on success, false otherwise.

*************************/
bool Player:: setName(const char* name)
{
	bool res;
	if (name == nullptr)
		res = false;
	else
	{
		this->name = new char[strlen(name) + 1];
		strcpy(this->name, name);
		res = true;
	}
	return res;
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
