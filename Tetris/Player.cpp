#include "Player.h"

Player::Player(Board& board, const char* name) : board(board)
{
	setName(name);
	score = 0;
}
bool Player:: setBoard(Board& board)
{
	this->board = board;
	return true;
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
		this->name = new char[strlen(name)];
		return true;
	}
}
char* Player:: getName()
{
	return name;
}