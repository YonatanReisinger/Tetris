#ifndef __GAME_H__
#define __GAME_H__

// Imports ->
#include "Board.h"
#include "Player.h"
#include <iostream>
using namespace std;
// <- Imports

// Macros ans enums->
enum class GameStatus {PAUSED, PLAYING, FINISHED};

// <- Macros and enums

class Game {
private:
	GameStatus status;
	Player &player1, &player2;
public:
	Game(Player& player1, Player& player2);
	void start();
	void pause();
	void resume();
	GameStatus getStatus();
	void setStatus(GameStatus status);
	Player& getPlayer(int playerNum);
};
#endif //Game.h