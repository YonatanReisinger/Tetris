#ifndef __GAME_H__
#define __GAME_H__

// Imports ->
#include "Board.h"
#include "Point.h"
#include "Player.h"
#include "Shape.h"
#include "gameConfig.h"
#include "global_functions.h"
#include <iostream>
#include <conio.h> // for _kbhit() and _getch()
using namespace std;
// <- Imports

// Macros ans enums->
enum class GameStatus {PAUSED, PLAYING, FINISHED} ;
enum Level { BEST = 'a', GOOD = 'b', NOVICE = 'c' };
#define NO_WINNER -1
#define TIE 0
// <- Macros and enums

class Game {
private:
	GameStatus status;
	Player &player1, &player2;
	short int winnerNum;
	GameColorStatus const colorStatus;
	Level const level;

	void run(); //game logic
	inline Shape* getRandomShape(Point& startPoint) const;
	void moveShapeOnScreen(Shape& shape, ShapeMovement movement, GamePace pace) const;
	bool checkAndProcessKeyboardInput();
	void processPlayerInput(Key key, Player& player);
	void printScores() const;
	void clearKeyboardInputBuffer() const;
	void determineWinner();
public:
	Game(Player& player1, Player& player2, GameColorStatus colorStatus, Level level);
	void start();
	inline bool pause() { return setStatus(GameStatus::PAUSED); };
	bool resume();
	GameStatus getStatus() const { return status; };
	bool setStatus(GameStatus status);
	inline const Player& getPlayer(int playerNum) const { return playerNum == 1 ? player1 : player2; };
	void setCurrentShape(Player& player, Point& startPoint);
	bool setWinnerNum(short int winnerNum);
	inline short int getWinnerNum() const { return winnerNum; };
	inline GameColorStatus const getColorStatus() const { return colorStatus; };
	void printWinner() const;
	static GameColorStatus getUserColorChoiceFromKeyboard();
	static Key getSideChoiceFromKeyboard();
	static Level getLevelFromKeyboard();
};
#endif //Game.h