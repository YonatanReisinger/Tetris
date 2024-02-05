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
	Key getKey();
	bool setCurrShapeFinalState(const Shape& shape);
	void findBestMove();
	int evaluatePlacement(Shape tmpShape);
	Shape getcurrShapeFinalState();
	bool setBestMoveScore(int newScore);

protected:
	Level level;
	Shape currShapeFinalState;
	int bestMoveScore;

	void evaluatePossibleMovesFromSide(ShapeMovement direction);
	bool updateBestMoveScoreAndCurrShapeFinalState(int newScore, const Shape& newShapeFinalState);
};
#endif //Computer.h

