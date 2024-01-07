#include "Game.h"

Game:: Game(Player &player1, Player &player2) : player1(player1), player2(player2)
{
	setStatus(GameStatus:: PLAYING); // new game is automatically being played
}
void Game::start()
{
	status = GameStatus:: PLAYING;
	cout << "starting game" << endl;
	if (true)
		status = GameStatus:: PAUSED;
	if (false)
		status = GameStatus::FINISHED;

}

void Game:: pause()
{
	status = GameStatus:: PAUSED;
	cout << "pausing the game";
}
void Game::resume()
{
	cout << "continue the game";
}

GameStatus Game:: getStatus()
{
	return status;
}
void Game:: setStatus(GameStatus status)
{
	this->status = status;
}
Player& Game:: getPlayer(int playerNum)
{
	return playerNum == 1 ? player1 : player2; 
}