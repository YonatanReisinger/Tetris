#ifndef __COMPUTER_H__
#define __COMPUTER_H__
// Imports ->
#include "Player.h"
// <- Imports

class Computer: virtual public Player
{
public:
	enum Level { BEST = 'a', GOOD = 'b', NOVICE = 'c', HUMAN = 'h' };
	Computer(const Board& board, const Key keys[], const string name, int bestMoveScore = 0, int score = 0);

	bool setLevel(Level level);
	inline Level getLevel() const { return level; };
	static Level getLevelFromKeyboard();
	virtual int getKeyInd(Key inputKey);
	void findBestMove();
	int evaluatePlacement(Shape tmpShape);

protected:
	Level level;
	Shape currShapeFinalState;
	int bestMoveScore;

	void evaluatePossibleMovesFromSide(ShapeMovement direction);
	bool setBestMoveScoreAndCurrShapeFinalState(int newScore, const Shape& newShapeFinalState);
};
#endif //Computer.h

