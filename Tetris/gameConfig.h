#ifndef __GAMECONFIG_H__
#define __GAMECONFIG_H__

#define FOREGROUND_WHITE 0xFFFFFF

enum class Directions {LEFT, RIGHT, UP, DOWN};
enum class GamePace { NORMAL = 700, MODERATE = 500 ,FAST = 50 };

#define EMPTY ' '
#define NOT_FOUND -1
#define ESC 27
#define NUM_OF_KEYS 5
#define NUM_OF_SHAPES 7

class GameConfig {
public:
	static constexpr int HEIGHT = 18;
	static constexpr int WIDTH = 12;
	static constexpr int DISTANCE_BETWEEN_BOARDS = 40;
	static constexpr char BORDER_SYMBOL = 'X';
	static constexpr char SHAPE_SYMBOL = '*';
	static constexpr unsigned char player1Keys[NUM_OF_KEYS] = {'a', 'd', 's', 'w', 'x'};
	static constexpr unsigned char player2Keys[NUM_OF_KEYS] = { 'j', 'l', 'k', 'i', 'm' };
	static constexpr int SCORE_FOR_FULL_LINE = 100;
	//static constexpr Color BORDER_COLOR = Color::WHITE;
};
#endif //GameConfig.h
