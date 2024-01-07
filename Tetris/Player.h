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
	Board& board;
public:
	Player(Board& board, const char* name = "momo");
	Player(const Player* other);

	bool setBoard(Board& board);
	Board& getBoard();
	bool setName(const char* name);
	char* getName();
};
#endif // PLAYER.h