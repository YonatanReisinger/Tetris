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

int main()
{
	unsigned int choice,colorChoice;
	Board board1(Point(1, 1), Point(GameConfig::WIDTH, 1), Point(1, GameConfig::HEIGHT), Point(GameConfig::WIDTH, GameConfig::HEIGHT));
	Board board2(Point(GameConfig::WIDTH + 2 + GameConfig::DISTANCE_BETWEEN_BOARDS + 1, 1)
		, Point(GameConfig::WIDTH * 2 + 2 + GameConfig::DISTANCE_BETWEEN_BOARDS, 1)
		, Point(GameConfig::WIDTH + 2 + GameConfig::DISTANCE_BETWEEN_BOARDS + 1, GameConfig::HEIGHT)
		, Point(GameConfig::WIDTH * 2 + 2 + GameConfig::DISTANCE_BETWEEN_BOARDS, GameConfig::HEIGHT));
	Player player1(board1, GameConfig:: player1Keys, "Player 1")
		, player2(board2, GameConfig::player2Keys, "Player 2");
	Game game(player1, player2);
	Game* pGame;

	showConsoleCursor(false); // Get rid of the cursor
	//srand(time(0)); // for getting new random shapes every time the program runs
	// print the whole board including the frame
	printMenu(); //the program just started and therefore for sure no paused game exists
	cin >> choice;

	while (choice != Choice::EXIT)
	{
		clearCin();
		clearScreen();
		switch (choice)
		{
		case(Choice::START_HUMAN_VS_HUMAN):
			printColorOption();
			cin >> colorChoice;
			clearCin();
			clearScreen();
			if (colorChoice != GameColorStatus::COLORIZED && colorChoice != GameColorStatus::UNCOLORIZED)
			{
				printChoiceError();
				break;
			}
			game.setColorStatus((GameColorStatus)colorChoice);
			game.start();
			break;
		case(Choice::START_HUMAN_VS_CPU):
			break;
		case(Choice::START_CPU_VS_CPU):
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
		printWinner(game);
		printMenu(game.getStatus());
		cin >> choice;
	}
	cout << "Good Game! Goodbye!" << endl;
	return 0;
}