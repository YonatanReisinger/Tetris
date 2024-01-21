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

	inline Board& getBoard() { return board; };
	bool setName(const char* name);
	inline const char* getName() const { return name; };
	bool setScore(int score);
	inline int getScore() const { return score; };
	bool increaseScore(int increase);
	void reset();
	int getKeyInd(Key inputKey);
	inline Shape* getCurrShape() { return currPlayingShape; };
	void setCurrShape(Shape* currShape);
};
#endif // PLAYER.h