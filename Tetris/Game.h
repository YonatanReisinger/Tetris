#ifndef __GAME_H__
#define __GAME_H__

// Imports ->
#include "Board.h"
#include "Player.h"
#include "Shape.h"
#include "gameConfig.h"
#include <iostream>
#include <conio.h> // for _kbhit() and _getch()
using namespace std;
// <- Imports

// Macros ans enums->
enum class GameStatus {PAUSED, PLAYING, FINISHED} ;
#define NO_WINNER -1
#define TIE 0
// <- Macros and enums

class Game {
private:
	GameStatus status;
	Player &player1, &player2;
	short int winnerNum;
	GameColorStatus colorStatus;

	GameStatus run(); //game logic
	inline Shape* getRandomShape(Point& startPoint);
	void moveShapeOnScreen(Shape& shape, ShapeMovement movement, GamePace pace);
	bool checkAndProcessKeyboardInput();
	void processPlayerInput(Key key, Player& player);
	void printScores();
	void clearKeyboardInputBuffer();
	void determineWinner(GameStatus gameStatus);
public:
	Game(Player& player1, Player& player2);
	void start();
	bool pause();
	bool resume();
	GameStatus getStatus() const;
	bool setStatus(GameStatus status);
	const Player& getPlayer(int playerNum) const;
	void setCurrentShape(Player& player,Point& startPoint);
	bool setWinnerNum(short int winnerNum);
	short int getWinnerNum();
	bool setColorStatus(GameColorStatus choice);
	GameColorStatus getColorStatus();
};
#endif //Game.h