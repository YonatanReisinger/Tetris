#ifndef __PLAYER_H__
#define __PLAYER_H__

// Imports ->
#include "Board.h"
#include "gameConfig.h"
// <- Imports

// Macros ans enums->
enum KeyInd { LEFT_IND, RIGHT_IND, ROTATE_LEFT_IND, ROTATE_RIGHT_IND, DROP_IND};
typedef unsigned char Key;
// <- Macros and enums

class Player {
private:
	char* name;
	Board board;
	int score;
	const Key keys[NUM_OF_KEYS];
	Shape* currPlayingShape;
public:
	Player(const Board& board, const Key keys[], const char* name = "momo", int score = 0);
	Player(const Player& other);

	Board& getBoard();
	bool setName(const char* name);
	char* getName();
	bool setScore(int score);
	int getScore();
	bool increaseScore(int increase);
	void reset();
	int getKeyInd(Key inputKey);
	Shape* getCurrShape();
	void setCurrShape(Shape* currShape);
};
#endif // PLAYER.h