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
enum class GameStatus {PAUSED, PLAYING, FINISHED};
// <- Macros and enums

class Game {
private:
	GameStatus status;
	Player &player1, &player2;
	GameStatus run(); //game logic
	inline Shape getRandomShape(Point& startPoint);
	void moveShapeOnScreen(Shape& shape, ShapeMovement movement, GamePace pace);
	bool checkAndProcessKeyboardInput();
	void processPlayerInput(Key key, Player& player);
public:
	Game(Player& player1, Player& player2);
	void start();
	bool pause();
	bool resume();
	GameStatus getStatus();
	bool setStatus(GameStatus status);
	Player& getPlayer(int playerNum);
};
#endif //Game.h