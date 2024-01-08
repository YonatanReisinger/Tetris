#ifndef __GAMECONFIG_H__
#define __GAMECONFIG_H__
class GameConfig {
public:
	static constexpr char INSTRUCTIONS_STR[] = "instructions";
	static constexpr char KEYS_STR[] = "keys";
	static constexpr int HEIGHT = 18;
	static constexpr int WIDTH = 12;
	static constexpr int DISTANCE_BETWEEN_BOARDS = 6;
	static constexpr char BORDER_SYMBOL = 'X';
	static constexpr char SHAPE_SYMBOL = '*';

};
#endif //GameConfig.h