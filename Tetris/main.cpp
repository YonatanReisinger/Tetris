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
	Player* cpu1 = new Computer(board1, GameConfig::player1Keys, "CPU 1")
		, * cpu2 = new Computer(board2, GameConfig::player2Keys, "CPU 2");
	Computer* tempCpu1 = dynamic_cast<Computer*>(cpu1), * tempCpu2 = dynamic_cast<Computer*>(cpu2);
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
			pGame = new Game(player1, player2, Game::getUserColorChoiceFromKeyboard());
			pGame->start();
			break;
		case(Choice::START_HUMAN_VS_CPU):
			tempCpu2->setLevel(Computer::getLevelFromKeyboard());
			pGame = new Game(player1, *cpu2, Game::getUserColorChoiceFromKeyboard());
			pGame->start();
			break;
		case(Choice::START_CPU_VS_CPU):
			cout << "Player1:" << endl;
			tempCpu1->setLevel(Computer::getLevelFromKeyboard());
			clearScreen();
			cout << "Player2:" << endl;
			tempCpu2->setLevel(Computer::getLevelFromKeyboard());
			clearScreen();
			pGame = new Game(*cpu1, *cpu2, Game::getUserColorChoiceFromKeyboard());
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