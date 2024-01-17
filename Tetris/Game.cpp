#include "Game.h"

Game:: Game(Player &player1, Player &player2) : player1(player1), player2(player2)
{
	setStatus(GameStatus:: PLAYING); // new game is automatically being played
}
GameStatus Game::run()
{
	bool isGamePlaying = true;
	Board board1 = player1.getBoard(), board2 = player2.getBoard();
	Point startPoint1 = board1.getStartingPoint(), startPoint2 = board2.getStartingPoint();
	if (getStatus() != GameStatus::PAUSED)
	{
		player1.setCurrShape(getRandomShape(startPoint1));
		player2.setCurrShape(getRandomShape(startPoint2));
	}
	// get the place that the shapes should start falling from
	//Shape shape1 = getRandomShape(startPoint1), shape2 = getRandomShape(startPoint2);
	//shape1 = Shape(STRAIGHT, startPoint1);

	/*Point p1(6, 15), p2(6, 11), p3(6, 7), p4(6,4), p5(6,1);
	Shape s1(STRAIGHT, p1, FACE_UP), s2(STRAIGHT, p2, FACE_UP), s3(STRAIGHT, p3, FACE_UP);
	Shape L1(L, p4, FACE_UP), L2(L, p5, FACE_UP);
	board1.setShapeInGameBoard(s1);
	board1.setShapeInGameBoard(s2);
	board1.setShapeInGameBoard(s3);
	board1.setShapeInGameBoard(L1);
	board1.setShapeInGameBoard(L2);*/
	Key key;
	GameStatus gameStatus = GameStatus::PLAYING;
	bool flag1 = false, flag2 = false;
	int keyInd1, keyInd2, clearRowsForPlayer1InRound = 0, clearRowsForPlayer2InRound = 0;

	board1.print();
	board2.print();
	player1.getCurrShape()->print();
	player2.getCurrShape()->print();

	// while both boards have space
	while (!board1.isShapeStuck(*(player1.getCurrShape())) && !board2.isShapeStuck(*(player2.getCurrShape())) && isGamePlaying)
	{
		isGamePlaying = checkAndProcessKeyboardInput();
		if (!isGamePlaying)
		{
			gameStatus = GameStatus::PAUSED;
			break;
		}
		isGamePlaying = checkAndProcessKeyboardInput();
		if (!isGamePlaying)
		{
			gameStatus = GameStatus::PAUSED;
			break;
		}
		/*

		if (_kbhit()) {
			key = _getch();
			keyInd1 = player1.getKeyInd(key);
			if (keyInd1 != NOT_FOUND && board1.canShapeMove(shape1, (ShapeMovement)keyInd1)) // if a valid key was pressed
			{
				// if the player pressed the drop bottom, drop the shape down the board while it can
				if ((ShapeMovement)keyInd1 == ShapeMovement::DROP)
					while (board1.canShapeChangeDirection(shape1, Directions:: DOWN))
						moveShapeOnScreen(shape1, ShapeMovement::DROP, GamePace::FAST);
				else // else, move the shape according to the movement selected
					moveShapeOnScreen(shape1, (ShapeMovement)keyInd1, GamePace::FAST);
			}
			keyInd2 = player2.getKeyInd(key);
			if (keyInd2 != NOT_FOUND && board2.canShapeMove(shape2, (ShapeMovement)keyInd2)) // if a valid key was pressed
			{
				// if the player pressed the drop bottom, drop the shape down the board while it can
				if ((ShapeMovement)keyInd2 == ShapeMovement::DROP)
					while (board2.canShapeChangeDirection(shape2, Directions::DOWN))
						moveShapeOnScreen(shape2, ShapeMovement::DROP, GamePace::FAST);
				else // else, move the shape according to the movement selected
					//moving to the sides should be faster the moving down
					moveShapeOnScreen(shape2, (ShapeMovement)keyInd2, GamePace::MODERATE);
			}
		}
		if (_kbhit()) {
			key = _getch();
			keyInd1 = player1.getKeyInd(key);
			if (keyInd1 != NOT_FOUND && board1.canShapeMove(shape1, (ShapeMovement)keyInd1)) // if a valid key was pressed
			{
				// if the player pressed the drop bottom, drop the shape down the board while it can
				if ((ShapeMovement)keyInd1 == ShapeMovement::DROP)
					while (board1.canShapeChangeDirection(shape1, Directions::DOWN))
						moveShapeOnScreen(shape1, ShapeMovement::DROP ,GamePace::FAST);
				else // else, move the shape according to the movement selected
					//moving to the sides should be faster the moving down
					moveShapeOnScreen(shape1, (ShapeMovement)keyInd1, GamePace::MODERATE);
			}
			keyInd2 = player2.getKeyInd(key);
			if (keyInd2 != NOT_FOUND && board2.canShapeMove(shape2, (ShapeMovement)keyInd2)) // if a valid key was pressed
			{
				// if the player pressed the drop bottom, drop the shape down the board while it can
				if ((ShapeMovement)keyInd2 == ShapeMovement::DROP)
					while (board2.canShapeChangeDirection(shape2, Directions::DOWN))
						moveShapeOnScreen(shape2, ShapeMovement::DROP ,GamePace::FAST);
				else // else, move the shape according to the movement selected
					//moving to the sides should be faster the moving down
					moveShapeOnScreen(shape2, (ShapeMovement)keyInd2, GamePace::MODERATE);
			}
		}
		*/
		setCurrentShape(player1, startPoint1);
		setCurrentShape(player2, startPoint2);
		/*

		if (board1.canShapeChangeDirection(shape1, Directions::DOWN))
			moveShapeOnScreen(shape1, ShapeMovement:: DROP, GamePace::NORMAL);
		else //if you can't move anymore, insert the shape into the board
		{
			board1.setShapeInGameBoard(shape1);
			board1.printGameBoard();
			shape1 = getRandomShape(startPoint1);
			// increase the score of the player according to how many rows he cleared
			clearRowsForPlayer1InRound = board1.clearFullRows();
			if (clearRowsForPlayer1InRound != 0)
			{
				player1.increaseScore(GameConfig::SCORE_FOR_FULL_LINE * clearRowsForPlayer1InRound);
				board1.dropActiveShapes();
				board1.printGameBoard();
			}
		}

		if (board2.canShapeChangeDirection(shape2, Directions::DOWN))
			moveShapeOnScreen(shape2, ShapeMovement::DROP, GamePace::NORMAL);
		else //if you can't move anymore, insert the shape into the board
		{
			board2.setShapeInGameBoard(shape2);
			board2.printGameBoard();
			shape2 = getRandomShape(startPoint2); // get a new shape
			clearRowsForPlayer2InRound = board2.clearFullRows();
			// increase the score of the player according to how many rows he cleared
			if (clearRowsForPlayer2InRound != 0)
			{
				player2.increaseScore(GameConfig::SCORE_FOR_FULL_LINE * clearRowsForPlayer2InRound);
				board2.dropActiveShapes();
				board2.printGameBoard();
			}
		}
	}
		*/
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
inline Shape* Game:: getRandomShape(Point& startPoint)
{
	Shape* s = new Shape(Type(rand() % NUM_OF_SHAPES), startPoint);
	return s;
}
void Game:: moveShapeOnScreen(Shape& shape, ShapeMovement movement, GamePace pace)
{
	Sleep((DWORD)pace);
	shape.clearShape(); // clear the shape from the screen to make it look like it's moving
	shape.print();
	shape.move(movement);
	shape.setSymbol(GameConfig::SHAPE_SYMBOL); // after it moved down, print it again in it's new place
	shape.print();
}
bool Game:: checkAndProcessKeyboardInput()
{
	bool res = true;
	Key key;
	if (_kbhit()) {
		key = _getch();
		if (key != ESC) {
		processPlayerInput(key, player1);
		processPlayerInput(key, player2);
		res = true;
		}
		else
			res = false;

	}
	return res;
}
void Game:: processPlayerInput(Key key, Player& player)
{
	ShapeMovement movement;
	Board& board = player.getBoard();
	//// the index of the key indicates it's type of movement
	movement = (ShapeMovement)player.getKeyInd(key);
	if (movement != NOT_FOUND && board.canShapeMove(*(player.getCurrShape()), movement)) // if a valid key was pressed
	{
		// if the player pressed the drop bottom, drop the shape down the board while it can
		if (movement == ShapeMovement::DROP)
			while (board.canShapeChangeDirection(*(player.getCurrShape()), Directions::DOWN))
				moveShapeOnScreen(*(player.getCurrShape()), ShapeMovement::DROP, GamePace::FAST);
		else // else, move the shape according to the movement selected
			moveShapeOnScreen(*(player.getCurrShape()), movement, GamePace::FAST);
	}
}

void Game:: setCurrentShape(Player& player,Point& startPoint)
{
	int clearRowsForPlayerInRound = 0;
	Board& board1 = player.getBoard();
	if (board1.canShapeChangeDirection(*(player.getCurrShape()), Directions::DOWN))
		moveShapeOnScreen(*(player.getCurrShape()), ShapeMovement::DROP, GamePace::NORMAL);
	else //if you can't move anymore, insert the shape into the board
	{
		board1.setShapeInGameBoard(*(player.getCurrShape()));
		board1.printGameBoard();
		player.setCurrShape(getRandomShape(startPoint));
		// increase the score of the player according to how many rows he cleared
		clearRowsForPlayerInRound = board1.clearFullRows();
		if (clearRowsForPlayerInRound != 0)
		{
			player1.increaseScore(GameConfig::SCORE_FOR_FULL_LINE * clearRowsForPlayerInRound);
			board1.dropActiveShapes();
			board1.printGameBoard();
		}
	}
}