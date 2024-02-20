#ifndef __GAME_H__
#define __GAME_H__

// Imports ->
#include "Board.h"
#include "Point.h"
#include "Player.h"
#include "Shape.h"
#include "gameConfig.h"
#include "Computer.h"
#include "global_functions.h"
#include <conio.h> // for _kbhit() and _getch()
#include <typeinfo>
#include <vector>
// <- Imports

// Macros ans enums->
#define NO_WINNER -1
#define TIE 0
// <- Macros and enums

class Game {

public:
	enum class GameStatus { PAUSED, PLAYING, FINISHED };

	Game(Player& player1, Player& player2, GameColorStatus colorStatus);
	void start();
	inline bool pause() { return setStatus(GameStatus::PAUSED); };
	bool resume();
	GameStatus getStatus() const { return status; };
	bool setStatus(GameStatus status);
	inline const Player& getPlayer(int playerNum) const { return playerNum == 1 ? player1 : player2; };
	void setCurrentShapeInBoard(Player& player);
	bool setWinnerNum(short int winnerNum);
	inline short int getWinnerNum() const { return winnerNum; };
	inline GameColorStatus const getColorStatus() const { return colorStatus; };
	void printWinner() const;
	static GameColorStatus getUserColorChoiceFromKeyboard();
	void moveShapeOnScreen(Shape& shape, Shape::ShapeMovement movement, GamePace pace) const;
	void setKeysPressed();
	static void printWelcomeMessage();
	static void printMenu(Game* pGame);
	static void printInstructionsAndKeys();
	static void printInstructions();
	static void printKeys();
	static void clearKeyboardInputBuffer();
	inline void clearKeysPressed();
	bool wasEscapePressed() const;
	void clearCharFromKeysPressed(char ch);

private:
	GameStatus status;
	Player &player1, &player2;
	short int winnerNum;
	GameColorStatus const colorStatus;
	vector<Key> keysPressed;

	void run(); //game logic
	bool checkAndProcessKeyboardInput();
	void processPlayerInput(Player& player);
	void printScores() const;
	void determineWinner();
};
#endif // Game.h