#ifndef __GAMECONFIG_H__
#define __GAMECONFIG_H__

#define FOREGROUND_WHITE 0xFFFFFF

enum Choice { START_HUMAN_VS_HUMAN = 1, START_HUMAN_VS_CPU = 2, START_CPU_VS_CPU = 3, CONTINUE = 4, INSTRUCTIONS = 8, EXIT = 9 };
enum class Directions {LEFT, RIGHT, UP, DOWN} ;
enum class GamePace { NORMAL = 700, MODERATE = 500 ,FAST = 50, BLINKING_PACE = 200};
enum GameColorStatus { COLORIZED = 1, UNCOLORIZED = 2};
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
	static constexpr int SCREEN_HEIGHT = 25;
	static constexpr int SCREEN_WIDTH = 80;
	static constexpr char BORDER_SYMBOL = 'X';
	static constexpr char SHAPE_SYMBOL = '*';
	static constexpr char BOMB_SYMBOL = '@';
	static constexpr unsigned char player1Keys[NUM_OF_KEYS] = {'a', 'd', 's', 'w', 'x'};
	static constexpr unsigned char player2Keys[NUM_OF_KEYS] = { 'j', 'l', 'k', 'i', 'm' };
	static constexpr int SCORE_FOR_FULL_LINE = 100;
	static constexpr int SCORE_FOR_PLACING_SHAPE = 25;
	static constexpr float CHANCE_FOR_BOMB = 0.05;
	static constexpr unsigned int BOMB_EXPLOSION_RANGE = 4;
	static constexpr int CLEARED_LINES_IMPORTANCE = 3;
	static constexpr int HEIGT_IMPORTANCE = 2;
	static constexpr int HOLES_IMPORTANCE = 1;
};
#endif //GameConfig.h
