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
	unsigned int choice;
	Board board1(Point(1, 1 + 4), Point(GameConfig::WIDTH, 1 + 4), Point(1, GameConfig::HEIGHT + 4), Point(GameConfig::WIDTH, GameConfig::HEIGHT + 4));
	Board board2(Point(GameConfig::WIDTH + 2 + GameConfig::DISTANCE_BETWEEN_BOARDS + 1, 1 + 4)
		, Point(GameConfig::WIDTH * 2 + 2 + GameConfig::DISTANCE_BETWEEN_BOARDS, 1 + 4)
		, Point(GameConfig::WIDTH + 2 + GameConfig::DISTANCE_BETWEEN_BOARDS + 1, GameConfig::HEIGHT + 4)
		, Point(GameConfig::WIDTH * 2 + 2 + GameConfig::DISTANCE_BETWEEN_BOARDS, GameConfig::HEIGHT + 4));
	Player player1(board1, GameConfig:: player1Keys, "Player 1", true)
		, player2(board2, GameConfig::player2Keys, "Player 2", true)
		, computerPlayer1(board1, GameConfig::player1Keys, "CPU 1", false)
	    , computerPlayer2(board2, GameConfig::player2Keys, "CPU 2", false);
	GameColorStatus colorChoice;
	Level levelChoice;
	Game* pGame = nullptr;

	showConsoleCursor(false); // Get rid of the cursor
	srand(time(0)); // for getting new random shapes every time the program runs
	// print the whole board including the frame
	printMenu(nullptr); //the program just started and therefore for sure no paused game exists
	cin >> choice;

	while (choice != Choice::EXIT)
	{
		clearCin();
		clearScreen();
		switch (choice)
		{
		case(Choice::START_HUMAN_VS_HUMAN):
			colorChoice = Game:: getUserColorChoiceFromKeyboard();
			pGame = new Game(player1, player2, colorChoice, Level:: BEST);
			pGame->start();
			break;
		case(Choice::START_HUMAN_VS_CPU):
			colorChoice = Game::getUserColorChoiceFromKeyboard();
			levelChoice = Game::getLevelFromKeyboard();
			pGame = Game:: getSideChoiceFromKeyboard() == RIGHT_ARROW ? new Game(computerPlayer1, player2, colorChoice, levelChoice) : new Game(player1, computerPlayer2, colorChoice, levelChoice);
			pGame->start();
			break;
		case(Choice::START_CPU_VS_CPU):
			colorChoice = Game::getUserColorChoiceFromKeyboard();
			pGame = new Game(computerPlayer1, computerPlayer2, colorChoice, Level::BEST);
			pGame->start();
			break;
		case(Choice::CONTINUE):
			if (pGame != nullptr && pGame->getStatus() == GameStatus::PAUSED)
				pGame->resume();
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
		if (pGame != nullptr)
		{
			pGame->printWinner();
			cout << "\n\n\nPress any key to continue........";
			while (!_kbhit());
			clearScreen();
		}
		if (pGame != nullptr && pGame->getStatus() == GameStatus::FINISHED)
		{
			delete pGame;
			pGame = nullptr;
		}
		printMenu(pGame);
		cin >> choice;
	}
	cout << "Good Game! Goodbye!" << endl;
	return 0;
}