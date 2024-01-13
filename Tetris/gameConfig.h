#ifndef __GAMECONFIG_H__
#define __GAMECONFIG_H__

#define FOREGROUND_WHITE 0xFFFFFF
enum class Color {
	RED = FOREGROUND_RED, BLUE = FOREGROUND_BLUE, GREEN = FOREGROUND_GREEN
	, WHITE = FOREGROUND_WHITE
};

enum class Directions {UP, DOWN, LEFT, RIGHT};
enum class GamePace { NORMAL = 250, FAST = 100 };
enum KeyInd { LEFT_IND, RIGHT_IND, ROTATE_RIGHT_IND, ROTATE_LEFT_IND, DROP_IND, NOT_FOUND = -1 };

#define EMPTY ' '
#define NOT_FOUND -1
#define ESC 27
#define NUM_OF_KEYS 5
#define NUM_OF_SHAPES 7
class GameConfig {
public:
	static constexpr char INSTRUCTIONS_STR[] = "instructions";
	static constexpr char KEYS_STR[] = "keys";
	static constexpr int HEIGHT = 18;
	static constexpr int WIDTH = 12;
	static constexpr int DISTANCE_BETWEEN_BOARDS = 6;
	static constexpr char BORDER_SYMBOL = 'X';
	static constexpr char SHAPE_SYMBOL = '*';
	static constexpr unsigned char player1Keys[NUM_OF_KEYS] = {'a', 'd', 's', 'w', 'x'};
	static constexpr unsigned char player2Keys[NUM_OF_KEYS] = { 'j', 'l', 'k', 'i', 'm' };

	//static constexpr Color BORDER_COLOR = Color::WHITE;
};
#endif //GameConfig.h