#include "Player.h"

Player::Player(const Board& board, const char* name, int score) : board(board)
{
	setName(name);
	this->score = score;
}
Board& Player:: getBoard()
{
	return board;
}
bool Player:: setName(const char* name)
{
	if (name == nullptr)
		return false;
	else
	{
		this->name = new char[strlen(name) + 1];
		return true;
	}
}
char* Player:: getName()
{
	return name;
}