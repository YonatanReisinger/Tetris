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
#include "Computer.h"
using namespace std;
// <- Imports 

int main()
{
	unsigned int choice;
	Board board1(Point(1, 1), Point(GameConfig::WIDTH, 1), Point(1, GameConfig::HEIGHT), Point(GameConfig::WIDTH, GameConfig::HEIGHT));
	Board board2(Point(GameConfig::WIDTH + 2 + GameConfig::DISTANCE_BETWEEN_BOARDS + 1, 1)
		, Point(GameConfig::WIDTH * 2 + 2 + GameConfig::DISTANCE_BETWEEN_BOARDS, 1)
		, Point(GameConfig::WIDTH + 2 + GameConfig::DISTANCE_BETWEEN_BOARDS + 1, GameConfig::HEIGHT)
		, Point(GameConfig::WIDTH * 2 + 2 + GameConfig::DISTANCE_BETWEEN_BOARDS, GameConfig::HEIGHT));
	Player player1(board1, GameConfig::player1Keys, "Player 1")
		, player2(board2, GameConfig::player2Keys, "Player 2");
	Computer computerPlayer1(board1, GameConfig::player1Keys, "CPU 1")
		, computerPlayer2(board2, GameConfig::player2Keys, "CPU 2");
	GameColorStatus colorChoice;
	Game* pGame = nullptr;
	
	Player* cpu3 = new Computer(board1, GameConfig::player1Keys, "CPU 1")
		, * cpu4 = new Computer(board2, GameConfig::player2Keys, "CPU 2");
	Computer* temp3 = dynamic_cast<Computer*>(cpu3), * temp4 = dynamic_cast<Computer*>(cpu4);

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
			pGame = new Game(player1, player2, colorChoice);
			pGame->start();
			break;
		case(Choice::START_HUMAN_VS_CPU):
			colorChoice = Game::getUserColorChoiceFromKeyboard();
			computerPlayer1.setLevel(Computer::getLevelFromKeyboard());
			// pGame = Game:: getSideChoiceFromKeyboard() == RIGHT_ARROW ? new Game(computerPlayer1, player2, colorChoice) : new Game(player1, computerPlayer1, colorChoice);
			pGame->start();
			break;
		case(Choice::START_CPU_VS_CPU):
			colorChoice = Game::getUserColorChoiceFromKeyboard();
			cout << "Player1:" << endl;
			temp3->setLevel(Computer::getLevelFromKeyboard());
			clearScreen();
			cout << "Player2:" << endl;
			temp4->setLevel(Computer::getLevelFromKeyboard());
			clearScreen();

			pGame = new Game(*cpu3, *cpu4, colorChoice);
			//pGame = new Game(computerPlayer1, computerPlayer2, colorChoice);
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