#include "Game.h"

Game:: Game(Player &player1, Player &player2) : player1(player1), player2(player2)
{
	setStatus(GameStatus:: PLAYING); // new game is automatically being played
}
GameStatus Game:: run()
{
	Board board1 = player1.getBoard(), board2 = player2.getBoard();
	// get the place that the shapes should start falling from
	Point startPoint1 = board1.getStartingPoint(), startPoint2 = board2.getStartingPoint();
	Shape shape1 = getRandomShape(startPoint1), shape2 = getRandomShape(startPoint2);
	Key key;
	GameStatus gameStatus = GameStatus:: PLAYING;
	bool flag1 = false, flag2 = false;

	board1.print();
	board2.print();
	shape1.print();
	shape2.print();
	while (board1.canShapeMove(shape1, Directions::DOWN) || board2.canShapeMove(shape2, Directions::DOWN))
	{
		if (board1.canShapeMove(shape1, Directions::DOWN))
		{
			Sleep(250);
			shape1.clearShape();
			shape1.print();
			shape1.moveDown();
			shape1.setSymbol(GameConfig::SHAPE_SYMBOL);
			shape1.print();
		}
		else if (!flag1)
		{
			//p1.move(Directions::UP);
			board1.setShapeInGameBoard(shape1);
			board1.printGameBoard();
			flag1 = true;
		}
		if (board2.canShapeMove(shape2, Directions::DOWN))
		{
			Sleep(250);
			shape2.clearShape();
			shape2.print();
			shape2.moveDown();
			shape2.setSymbol(GameConfig::SHAPE_SYMBOL);
			shape2.print();
		}
		else if (!flag2)
		{
			//p1.move(Directions::UP);
			board2.setShapeInGameBoard(shape2);
			board2.printGameBoard();
			flag2 = true;
		}
	}
	return gameStatus;
}
void Game::start()
{
	setStatus(GameStatus::PLAYING); // no need to check the return value because you can always start a new game
	player1.reset();
	player2.reset();
	setStatus(run()); //run the game and update the game status afterwards
}

bool Game:: pause()
{
	return setStatus(GameStatus::PAUSED);
}
bool Game::resume()
{
	// set the status to continue playing and just after the function validate that the game can resume, 
	// run the game and update to gameStatus in the end
	if (status == GameStatus::PAUSED) // cant resume a game that was not paused before
		return (setStatus(GameStatus::PLAYING) && setStatus(run()));
	else
		return false;
}

GameStatus Game:: getStatus()
{
	return status;
}
bool Game:: setStatus(GameStatus status)
{
	bool res;
	// the status has to be one of the supported types
	if (status == GameStatus::PAUSED || status == GameStatus::PLAYING || status == GameStatus::FINISHED)
	{
		// cant pause a game that was already finished 
		if (status == GameStatus::PAUSED && this->status == GameStatus::FINISHED)
			res = false;
		else
		{
			this->status = status;
			res = true;
		}
	}
	else
		res = false;
	return res;
}
Player& Game:: getPlayer(int playerNum)
{
	return playerNum == 1 ? player1 : player2; 
}
inline Shape Game:: getRandomShape(Point& startPoint)
{
	return Shape(Type(rand() % NUM_OF_SHAPES), startPoint);
}