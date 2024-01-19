#ifndef __PLAYER_H__
#define __PLAYER_H__

// Imports ->
#include "Board.h"
#include "gameConfig.h"
// <- Imports

// Macros ans enums->
enum KeyInd { LEFT_IND, RIGHT_IND, ROTATE_LEFT_IND, ROTATE_RIGHT_IND, DROP_IND} ;
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
	Player(const Board& board, const Key keys[], const char* name, int score = 0);
	Player(const Player& other) = delete;
	Player& operator=(const Player& other) = delete;
	~Player();

	Board& getBoard();
	bool setName(const char* name);
	const char* getName() const;
	bool setScore(int score);
	int getScore() const;
	bool increaseScore(int increase);
	void reset();
	int getKeyInd(Key inputKey);
	Shape* getCurrShape();
	void setCurrShape(Shape* currShape);
};
#endif // PLAYER.h