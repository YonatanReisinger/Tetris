#ifndef __COMPUTER_H__
#define __COMPUTER_H__
// Imports ->
#include "Player.h"
// <- Imports

class Computer: virtual protected Player
{
public:
	enum Level { BEST = 'a', GOOD = 'b', NOVICE = 'c', HUMAN = 'h' };
	Computer(const Board& board, const Key keys[], const string name, Level level, int score = 0);

	bool setLevel(Level level);
	inline Level getLevel() const { return level; };
	static Level getLevelFromKeyboard();
	virtual int getKeyInd(Key inputKey);
	Key getKey();
	bool setCurrShapeFinalState(const Shape& shape);

protected:
	Level level;
	Shape currShapeFinalState;
};
#endif //Computer.h

