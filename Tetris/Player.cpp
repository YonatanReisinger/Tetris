#include "Player.h"

Player::Player(const Board& board, const Key keys[], const char* name, int score): board(board)
	, keys{keys[KeyInd:: LEFT], keys[KeyInd::RIGHT], keys[KeyInd::ROTATE_CW], keys[KeyInd::ROTATE_COUNTER_CW], keys[KeyInd::DROP] }
{
	setName(name);
	setScore(score);
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
}
bool Player:: isInKeys(Key inputKey)
{
	// search if the input key is part of the players keys
	for (const Key& key : keys)
		// the input key can be either small letters or capital letters
		if (inputKey == key || inputKey + ('a' - 'A') == key)
			return true;
	return false;
}