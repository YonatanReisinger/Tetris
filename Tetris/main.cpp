// Imports -> 
#include <conio.h>
#include <windows.h>
#include "global_functions.h"
#include "Shape.h"
#include "Game.h"
#include "Point.h"
#include "gameConfig.h"
#include "Player.h"
#include "Computer.h"
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
	Player* cpu1 = nullptr, *cpu2 = nullptr;
	Game* pGame = nullptr;
	

	showConsoleCursor(false); // Get rid of the cursor
	srand(time(0)); // for getting new random shapes every time the program runs
	// print the whole board including the frame
	Game:: printMenu(nullptr); //the program just started and therefore for sure no paused game exists
	cin >> choice;

	while ((Choice)choice != Choice::EXIT)
	{
		clearCin();
		clearScreen();
		switch (choice)
		{
		case((int)Choice::START_HUMAN_VS_HUMAN):
			pGame = new Game(player1, player2, Game::getUserColorChoiceFromKeyboard());
			pGame->start();
			break;
		case((int)Choice::START_HUMAN_VS_CPU):
			prepareHumanVsCpu(cpu2, board2);
			pGame = new Game(player1, *cpu2, Game::getUserColorChoiceFromKeyboard());
			pGame->start();
			break;
		case((int)Choice::START_CPU_VS_CPU):
			prepareCpuVsCpu(cpu1, cpu2, board1, board2);
			pGame = new Game(*cpu1, *cpu2, Game::getUserColorChoiceFromKeyboard());
			pGame->start();
			break;
		case((int)Choice::CONTINUE):
			if (pGame != nullptr && pGame->getStatus() == Game:: GameStatus::PAUSED)
				pGame->resume();
			else
			{
				cout << "No paused game to continue !" << "\n\n\nPress any key to continue........";
				while (!_kbhit());
			}
			break;
		case((int)Choice::INSTRUCTIONS):
			Game:: printInstructionsAndKeys();
			break;
		default:
			printChoiceError(); 
			break;
		}
		clearScreen();
		if (pGame != nullptr && pGame->getWinnerNum() != NO_WINNER)
		{
			pGame->printWinner();
			cout << "\n\n\nPress any key to continue........";
			Game::clearKeyboardInputBuffer();
			while (!_kbhit());
			clearScreen();
		}
		if (pGame != nullptr && pGame->getStatus() == Game:: GameStatus::FINISHED)
		{
			delete pGame;
			pGame = nullptr;
		}
		Game:: printMenu(pGame);
		cin >> choice;
	}
	delete pGame;
	delete cpu1;
	delete cpu2;
	cout << "Good Game! Goodbye!" << endl;
	return 0;
}