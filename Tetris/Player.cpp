#include "Player.h"

Player::Player(const Board& board, const Key keys[], const char* name, int score): board(board)
	, keys{keys[KeyInd:: LEFT_IND], keys[KeyInd::RIGHT_IND], keys[KeyInd::ROTATE_RIGHT_IND], keys[KeyInd::ROTATE_LEFT_IND], keys[KeyInd::DROP_IND] }
{
	setName(name);
	setScore(score);
	setCurrShape(nullptr);
}
Board& Player:: getBoard()
{
	return board;
}
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
char* Player:: getName()
{
	return name;
}
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
int Player:: getScore()
{
	return score;
}
bool Player::increaseScore(int increase)
{
	return setScore(score += increase);
}
void Player:: reset()
{
	board.clear();
	setScore(0);
	if (currPlayingShape != nullptr) {
		delete currPlayingShape;
	}
}
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

Shape* Player::getCurrShape()
{
	return currPlayingShape;
}

void Player:: setCurrShape(Shape* currShape)
{
	currPlayingShape = currShape;
}
