#ifndef __PLAYER_H__
#define __PLAYER_H__

// Imports ->
#include "Board.h"
#include "gameConfig.h"
//#include "Game.h"
#include <conio.h> // for _kbhit() and _getch()
// <- Imports

// Macros ans enums->
typedef unsigned char Key;
class Computer;
// <- Macros and enums

class Player {
private:
	string const name;
	Board board;
	int score;
	Key const keys[NUM_OF_KEYS];
	Shape* currPlayingShape;
	Point startPoint;

public:
	enum KeyInd { LEFT_IND, RIGHT_IND, ROTATE_LEFT_IND, ROTATE_RIGHT_IND, DROP_IND };

	Player(const Board& board, const Key keys[], const string name, int score = 0);
	Player(const Player& other) = delete;
	Player& operator=(const Player& other) = delete;
	virtual ~Player();

	inline Board& getBoard() { return board; };
	inline const Board& getBoard() const { return board; };
	inline const string getName() const { return name; };
	bool setScore(int score);
	inline int getScore() const { return score; };
	bool increaseScore(int increase);
	void reset();
	int getKeyInd(Key inputKey) const;
	inline Shape* getCurrShape() const { return currPlayingShape; };
	void setCurrShape(Shape* currShape);
	bool isStuck() const;
	bool canCurrShapeMove(Shape:: ShapeMovement movement) const;
	virtual void findBestMove();
	bool setStartpoint(const Point& startPoint);
	const Point& getStartPoint() const;
	void setRandomCurrShape(GameColorStatus color);
	const Key* const getKeys() const;
};
#endif // PLAYER.h