// Imports -> 
#include <iostream>
#include <conio.h>
#include <windows.h>
#include "global_functions.h"
#include "Shape.h"
#include "Game.h"
#include "Point.h"
#include "gameConfig.h"
#include "Player.h"
using namespace std;
// <- Imports 

// Macros and enums ->
enum Choice{ START = 1, CONTINUE = 2, INSTRUCTIONS = 8, EXIT = 9};
// <- Macros and enums

int main()
{
	unsigned int choice;
	Board board1(Point(1, 1), Point(GameConfig::WIDTH, 1), Point(1, GameConfig::HEIGHT), Point(GameConfig::WIDTH, GameConfig::HEIGHT));
	Board board2(Point(GameConfig::WIDTH + 2 + GameConfig::DISTANCE_BETWEEN_BOARDS + 1, 1)
		, Point(GameConfig::WIDTH * 2 + 2 + GameConfig::DISTANCE_BETWEEN_BOARDS, 1)
		, Point(GameConfig::WIDTH + 2 + GameConfig::DISTANCE_BETWEEN_BOARDS + 1, GameConfig::HEIGHT)
		, Point(GameConfig::WIDTH * 2 + 2 + GameConfig::DISTANCE_BETWEEN_BOARDS, GameConfig::HEIGHT));
	Player player1(board1, GameConfig:: player1Keys, "Daniel")
		, player2(board2, GameConfig::player2Keys, "Yonatan");
	Game game(player1, player2);
	
	// print the whole board including the frame
	printMenu(); //the program just started and therefore for sure no paused game exists
	cin >> choice;

	while (choice != Choice::EXIT)
	{
		clearCin();
		clearScreen();
		switch (choice)
		{
		case(Choice::START):
			game.start();
			break;
		case(Choice::CONTINUE):
			if (game.getStatus() == GameStatus::PAUSED)
				game.resume();
			else
			{
				cout << "No paused game to continue !" << "\n\n\nPress any key to continue........";
				while (!_kbhit());
			}
			break;
		case(Choice::INSTRUCTIONS):
			printInstructionsAndKeys();
			break;
		default:
			printChoiceError(); 
			break;
		}
		clearScreen();
		printWinner(game); //entersssssss 
		printMenu(game.getStatus());
		cin >> choice;
	}
	cout << "Good Game! Goodbye!" << endl;
	return 0;
}