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
	Key getKey() const;
	bool setCurrShapeFinalState(const Shape& shape);
	void findBestMove();
	int evaluatePlacement(Shape tmpShape);
	Shape getcurrShapeFinalState() const;
	bool setBestMoveScore(int newScore);

protected:
	Level level;
	Shape currShapeFinalState;
	int bestMoveScore;

	void evaluatePossibleMovesFromSide(const Shape& tmpShape, Shape:: ShapeMovement direction);
	inline bool updateBestMoveScoreAndCurrShapeFinalState(int newScore, const Shape& newShapeFinalState);
	int evaluate() const;
	int evaluate(Shape& bomb) const;
	void calculateEvaluationParameters(short int& maxHeight, short int& holesPenalty, short int& fullRows) const;
	int getBlockedFromAbovePenalty(int row, int col) const;
	int getBlockedFromSidePenalty(int row, int col) const;
	bool shouldMakeRandomMove() const;
	void findRandomMove();
};
#endif //Computer.h

