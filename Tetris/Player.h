#ifndef __PLAYER_H__
#define __PLAYER_H__

// Imports ->
#include "Board.h"
#include "gameConfig.h"
//#include "Game.h"
#include <conio.h> // for _kbhit() and _getch()
// <- Imports

// Macros ans enums->
enum KeyInd { LEFT_IND, RIGHT_IND, ROTATE_LEFT_IND, ROTATE_RIGHT_IND, DROP_IND} ;
typedef unsigned char Key;
class Computer;
// <- Macros and enums

class Player {
protected:
	string const name;
	Board board;
	int score;
	Key const keys[NUM_OF_KEYS];
	Shape* currPlayingShape;

	int dropShapeAndRatePlacement(Shape tmpShape);

public:
	Player(const Board& board, const Key keys[], const string name, int score = 0);
	Player(const Player& other) = delete;
	Player& operator=(const Player& other) = delete;
	virtual ~Player();

	inline Board& getBoard() { return board; };
	inline const string getName() const { return name; };
	bool setScore(int score);
	inline int getScore() const { return score; };
	bool increaseScore(int increase);
	void reset();
	virtual int getKeyInd(Key inputKey);
	inline Shape* getCurrShape() { return currPlayingShape; };
	void setCurrShape(Shape* currShape);
	bool isStuck() const;
	bool canCurrShapeMove(ShapeMovement movement) const;	
	//void updateCurShapeInGame(const Game& game);
	Shape findBestMove();
};
#endif // PLAYER.h