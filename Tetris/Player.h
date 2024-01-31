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
enum Level { BEST = 'a', GOOD = 'b', NOVICE = 'c', HUMAN = 'h' };
typedef unsigned char Key;
// <- Macros and enums

class Player {
private:
	string const name;
	Board board;
	int score;
	Key const keys[NUM_OF_KEYS];
	Shape* currPlayingShape;
	bool const isHuman;
	Level level;

public:
	Player(const Board& board, const Key keys[], const string name, bool isHuman , Level level, int score = 0);
	Player(const Player& other) = delete;
	Player& operator=(const Player& other) = delete;
	~Player();

	inline Board& getBoard() { return board; };
	inline const string getName() const { return name; };
	bool setScore(int score);
	inline int getScore() const { return score; };
	bool increaseScore(int increase);
	void reset();
	int getKeyInd(Key inputKey);
	inline Shape* getCurrShape() { return currPlayingShape; };
	void setCurrShape(Shape* currShape);
	bool isStuck() const;
	bool canCurrShapeMove(ShapeMovement movement) const;
	static Level getLevelFromKeyboard();
	bool setLevel(Level level);
	inline Level getLevel() const { return level; };
	//void updateCurShapeInGame(const Game& game);
	const Shape& optimizeMove();
};
#endif // PLAYER.h