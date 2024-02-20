#ifndef __COMPUTER_H__
#define __COMPUTER_H__
// Imports ->
#include "Player.h"
// <- Imports

class Computer: public Player
{
public:
	enum class Level { BEST = 'a', GOOD = 'b', NOVICE = 'c'};
	Computer(const Board& board, const Key keys[], const string name, int bestMoveScore = 0, int score = 0);

	bool setLevel(Level level);
	inline Level getLevel() const { return level; };
	static Level getLevelFromKeyboard();
	Key pressKey() const;
	bool setCurrShapeFinalState(const Shape& shape) const;
	void findBestMove();
	

private:
	Level level;
	mutable Shape currShapeFinalState;
	mutable int bestMoveScore;

	void evaluatePossibleMovesFromSide(const Shape& tmpShape, Shape:: ShapeMovement direction);
	inline bool updateBestMoveScoreAndCurrShapeFinalState(int newScore, const Shape& newShapeFinalState) const;
	int evaluatePlacement(Shape tmpShape);
	Shape getcurrShapeFinalState() const;
	inline bool setBestMoveScore(int newScore) const;
	int evaluate() const;
	int evaluate(Shape& bomb) const;
	void calculateEvaluationParameters(short int& maxHeight, short int& holesPenalty, short int& fullRows) const;
	int getBlockedFromAbovePenalty(int row, int col) const;
	int getBlockedFromSidePenalty(int row, int col) const;
	bool shouldMakeRandomMove() const;
	void findRandomMove() const;
};
#endif //Computer.h

