#ifndef __PLAYER_H__
#define __PLAYER_H__

// Imports ->
#include "Board.h"
// <- Imports

// Macros ans enums->
// <- Macros and enums

class Player {
private:
	char* name;
	Board board;
	int score;
public:
	Player(const Board& board, const char* name = "momo", int score = 0);
	Player(const Player& other);

	Board& getBoard();
	bool setName(const char* name);
	char* getName();
};
#endif // PLAYER.h