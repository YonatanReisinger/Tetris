#include "Game.h"

/************************
* Name: Game::Game
* Input: Player& player1 (Reference to the first player), Player& player2 (Reference to the second player)
* Output: None
* Description: Constructor for the Game class. Initializes the game with the provided players, sets the initial game status to PLAYING, and the winner number to NO_WINNER.
************************/
Game:: Game(Player &player1, Player &player2) : player1(player1), player2(player2)
{
	setStatus(GameStatus:: PLAYING); // new game is automatically being played
	setWinnerNum(NO_WINNER);
}
/************************
* Name: Game::run
* Input: None
* Output: GameStatus representing the final status of the game
* Description: Runs the main game loop, handling player input, moving shapes, updating scores, and determining the winner.
************************/
GameStatus Game::run()
{
	GameStatus gameStatus = GameStatus::PLAYING;
	bool isGamePlaying = true;
	Board& board1 = player1.getBoard(), &board2 = player2.getBoard();
	Point startPoint1 = board1.getStartingPoint(), startPoint2 = board2.getStartingPoint();

	if (getStatus() != GameStatus::PAUSED) // random new shapes just if it is completely new game 
	{
		player1.setCurrShape(getRandomShape(startPoint1));
		player2.setCurrShape(getRandomShape(startPoint2));
	}

	board1.print();
	board2.print();
	
	// while both boards have space
	while (isGamePlaying)
	{
		player1.getCurrShape()->print();
		player2.getCurrShape()->print();
		printScores();
		isGamePlaying = checkAndProcessKeyboardInput();
		if (!isGamePlaying) // if the player typed on ESC char that represents pausing the game
		{
			gameStatus = GameStatus::PAUSED;
			break;
		}
		// the following code is repeat as it helps the reactivity of the game !!!
		isGamePlaying = checkAndProcessKeyboardInput();
		if (!isGamePlaying) // if the player typed on ESC char that represents pausing the game
		{
			gameStatus = GameStatus::PAUSED;
			break;
		}
		setCurrentShape(player1, startPoint1);
		setCurrentShape(player2, startPoint2);
		
		// if one of the current shapes can't move anymore, it means that the player has lost and the game should end
		isGamePlaying = !board1.isShapeStuck(*(player1.getCurrShape())) && !board2.isShapeStuck(*(player2.getCurrShape()));
	}
	clearKeyboardInputBuffer();
	// if the game reached here and was not paused, thus it finished
	gameStatus = (gameStatus == GameStatus::PAUSED) ? GameStatus::PAUSED : GameStatus::FINISHED;
	determineWinner(gameStatus);
	return gameStatus;
}
/************************
* Name: Game::start
* Input: None
* Output: None
* Description: Starts a new game by resetting players and running the game loop.
************************/
void Game::start()
{
	setStatus(GameStatus::PLAYING); // no need to check the return value because you can always start a new game
	player1.reset();
	player2.reset();
	setStatus(run()); //run the game and update the game status afterwards
}
/************************
* Name: Game::resume
* Input: None
* Output: bool representing whether the resume operation was successful (true) or not (false)
* Description: Resumes the game if it was previously paused, setting the game status to PLAYING.
************************/
bool Game::resume()
{
	// set the status to continue playing and just after the function validate that the game can resume, 
	// run the game and update to gameStatus in the end
	if (status == GameStatus::PAUSED) // cant resume a game that was not paused before
		return setStatus(run());
	else
		return false;
}
/************************
* Name: Game::setStatus
* Input: GameStatus status (The desired game status)
* Output: bool representing whether the status was set successfully (true) or not (false)
* Description: Sets the game status to the provided status if it's a valid status. Checks if the game can transition to the new status.
************************/
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
/************************
* Name: Game::getRandomShape
* Input: Point& startPoint (The starting point for the new shape)
* Output: Shape* representing a randomly generated shape
* Description: Generates a new shape with a random type, starting point, and color status.
************************/
inline Shape* Game:: getRandomShape(Point& startPoint) const
{
	Shape* s = new Shape(Type(rand() % NUM_OF_SHAPES), startPoint,getColorStatus()) ;
	return s;
}
/************************
* Name: Game::moveShapeOnScreen
* Input: Shape& shape (Reference to the shape to be moved), ShapeMovement movement (The direction of movement), GamePace pace (The speed of movement)
* Output: None
* Description: Moves a shape on the screen, clearing it from the old position, printing it in the new position, and applying a delay based on the game pace.
************************/
void Game:: moveShapeOnScreen(Shape& shape, ShapeMovement movement, GamePace pace) const
{
	Sleep((DWORD)pace);
	shape.clearShape(); // clear the shape from the screen to make it look like it's moving
	shape.print();
	shape.move(movement);
	shape.setSymbol(GameConfig::SHAPE_SYMBOL); // after it moved down, print it again in it's new place
	shape.print();
}
/************************
* Name: Game::checkAndProcessKeyboardInput
* Input: None
* Output: bool representing whether the game is still being played (true) or not (false)
* Description: Checks for keyboard input and processes player movements. Returns false if the ESC key is pressed, indicating a pause request.
************************/
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
/************************
* Name: Game::processPlayerInput
* Input: Key key (The key pressed by the player), Player& player (Reference to the player whose input is being processed)
* Output: None
* Description: Processes player input, interpreting the key and applying the corresponding movement to the player's current shape on the board.
************************/
void Game:: processPlayerInput(Key key, Player& player)
{
	ShapeMovement movement;
	Board& board = player.getBoard();
	Shape& currShape = *(player.getCurrShape()), tempShape;
	//// the index of the key indicates it's type of movement
	movement = (ShapeMovement)player.getKeyInd(key);
	// if a valid key was pressed
	if (movement != NOT_FOUND && board.canShapeMove(*(player.getCurrShape()), movement))
	{
		// if the player pressed the drop bottom, drop the shape down the board while it can
		if (movement == ShapeMovement::DROP)
			while (board.canShapeMove(currShape, ShapeMovement::DROP))
				moveShapeOnScreen(currShape, ShapeMovement::DROP, GamePace::FAST);
		else // else, move the shape according to the movement selected
			moveShapeOnScreen(currShape, movement, GamePace::FAST);
	}
}
/************************
* Name: Game::setCurrentShape
* Input: Player& player (Reference to the player whose current shape is being set), Point& startPoint (The starting point for the new shape)
* Output: None
* Description: Sets the current shape for the player, either generating a new shape or moving the existing one down the board. Handles clearing full rows, updating scores, and printing the new shape.
************************/
void Game:: setCurrentShape(Player& player,Point& startPoint)
{
	int clearRowsForPlayerInRound = 0;
	Board& board = player.getBoard();
	if (board.canShapeMove(*(player.getCurrShape()), ShapeMovement::DROP))
		moveShapeOnScreen(*(player.getCurrShape()), ShapeMovement::DROP, GamePace::NORMAL);
	//if you can't move anymore and can insert the shape into the board
	else
	{
		board.setShapeInGameBoard(*(player.getCurrShape()), true);
		// print the new shape on the playing board
		board.printGameBoard();
		
		// increase the score of the player according to how many rows he cleared
		clearRowsForPlayerInRound = board.clearFullRows();
		// drop all the shapes, if after the drop more rows can be cleared, continue to do so
		while (clearRowsForPlayerInRound != 0)
		{
			player.increaseScore(GameConfig::SCORE_FOR_FULL_LINE * clearRowsForPlayerInRound);
			board.dropActiveShapes();
			board.printGameBoard();
			clearRowsForPlayerInRound = board.clearFullRows();
		}
		// get a new random shape and print it
		player.setCurrShape(getRandomShape(startPoint));
	}
}
/************************
* Name: Game::printScores
* Input: None
* Output: None
* Description: Prints the scores of both players at the bottom of the game board.
************************/
void Game:: printScores() const
{
	// print the score at the middle of the board in the middle
	Point p1 = player1.getBoard().getBorders()[Borders::BOTTOM_LEFT]
		, p2 = player2.getBoard().getBorders()[Borders::BOTTOM_LEFT];
	p1.setY(GameConfig:: HEIGHT + 2);
	p1.moveLeft();
	p1.gotoxy();
	cout << "Player 1 Score: " << player1.getScore();
	p2.setY(GameConfig::HEIGHT + 2);
	p2.moveLeft();
	p2.gotoxy();
	cout << "Player 2 Score: " << player2.getScore();
}
/************************
* Name: Game::clearKeyboardInputBuffer
* Input: None
* Output: None
* Description: Clears the keyboard input buffer, ensuring no residual input is processed.
************************/
void Game:: clearKeyboardInputBuffer() const
{
	char temp;
	while (_kbhit())
		temp = _getch();
}
/************************
* Name: Game::setWinnerNum
* Input: short int winnerNum (The winner number to be set)
* Output: bool representing whether the winner number was set successfully (true) or not (false)
* Description: Sets the winner number if it is a valid value (1, 2, TIE, or NO_WINNER).
************************/
bool Game:: setWinnerNum(short int winnerNum)
{
	if (winnerNum == 1 || winnerNum == 2 || winnerNum == TIE || winnerNum == NO_WINNER)
	{
		this->winnerNum = winnerNum;
		return true;
	}
	else
		return false;
}
/************************
* Name: Game::determineWinner
* Input: GameStatus gameStatus (The final status of the game)
* Output: None
* Description: Determines the winner based on the final status of the game. Handles tie scenarios by comparing scores.
************************/
void Game:: determineWinner(GameStatus gameStatus)
{
	// if the was finished and there is a winner
	if (gameStatus == GameStatus:: FINISHED)
	{
		// if both of them finished the board at the same time, determine the winner by score
		if (player1.getBoard().isShapeStuck(*(player1.getCurrShape())) && player2.getBoard().isShapeStuck(*(player2.getCurrShape())))
		{
			if (player1.getScore() > player2.getScore())
				setWinnerNum(1);
			else if (player1.getScore() < player2.getScore())
				setWinnerNum(2);
			else //tie
				setWinnerNum(TIE);
		}
		// if only the second player finished his board
		else if(player2.getBoard().isShapeStuck(*(player2.getCurrShape())))
			setWinnerNum(1);
		else // the game was finished and thus for sure someone finished his board
			setWinnerNum(2);
	}

}
/************************
* Name: Game::setColorStatus
* Input: GameColorStatus choice (The desired color status)
* Output: bool representing whether the color status was set successfully (true) or not (false)
* Description: Sets the color status for the game if it is a valid choice (COLORIZED or UNCOLORIZED).
************************/
bool Game:: setColorStatus(GameColorStatus choice)
{
	bool res = true;
	if (choice != COLORIZED && choice != UNCOLORIZED) {
		res = false;
	}
	else {
	colorStatus = choice;
	}
	return res;
}