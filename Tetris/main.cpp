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
	Game* pGame;
	unsigned int choice;
	Board board1(Point(1, 1), Point(GameConfig::WIDTH, 1), Point(1, GameConfig::HEIGHT), Point(GameConfig::WIDTH, GameConfig::HEIGHT));
	Board board2(Point(GameConfig::WIDTH + 2 + GameConfig::DISTANCE_BETWEEN_BOARDS + 1, 1)
		, Point(GameConfig::WIDTH * 2 + 2 + GameConfig::DISTANCE_BETWEEN_BOARDS, 1)
		, Point(GameConfig::WIDTH + 2 + GameConfig::DISTANCE_BETWEEN_BOARDS + 1, GameConfig::HEIGHT)
		, Point(GameConfig::WIDTH * 2 + 2 + GameConfig::DISTANCE_BETWEEN_BOARDS, GameConfig::HEIGHT));
	Player player1(board1, GameConfig:: player1Keys, "Daniel")
		, player2(board2, GameConfig::player2Keys, "Yonatan");
		
	Point p1(2, 1, '*'), p2(23, 1, '@');
	board1.setPointInGameBoardByInd(17, 1, '*');
	board1.setPointInGameBoardByInd(17, 0, '*');
	board2.setPointInGameBoardByInd(17, 3, '@');
	board2.setPointInGameBoardByInd(17, 2, '@');

	char keyPlayer1 = ' ';
	char keyPlayer2 = ' ';
	Key key = ' ';

	while (true) {
		// Check if a key is pressed for player 1
		if (_kbhit()) {
			key = _getch();
			if (player1.isInKeys(key))
				std::cout << "Player 1 pressed: " << key << std::endl;
			if (player2.isInKeys(key))
				std::cout << "Player 2 pressed: " << key << std::endl;
		}

		// Exit the loop if a specific key is pressed (for example, 'q')
		if (key == ESC)
			break;
	}
	//// print the whole board including the frame
	//board1.print();
	//board2.print();
	//bool flag1 = false, flag2 = false;
	//while (board1.canPointMove(p1, Directions::DOWN) || board2.canPointMove(p2, Directions::DOWN))
	//{
	//	if (board1.canPointMove(p1, Directions::DOWN))
	//	{
	//		Sleep(250);
	//		p1.gotoxy();
	//		cout << ' ';
	//		p1.move(Directions::DOWN);
	//		p1.print();
	//	}
	//	else if (!flag1)
	//	{
	//		//p1.move(Directions::UP);
	//		board1.setPointInGameBoard(p1);
	//		board1.printGameBoard();
	//		flag1 = true;
	//	}
	//	if (board2.canPointMove(p2, Directions::DOWN))
	//	{
	//		Sleep(250);
	//		p2.gotoxy();
	//		cout << ' ';
	//		p2.move(Directions::DOWN);
	//		p2.print();
	//	}
	//	else if (!flag2)
	//	{
	//		board2.setPointInGameBoard(p2);
	//		board2.printGameBoard();
	//		flag2 = true;
	//	}
	//}
	//board1.print();
	//board2.print();
	//pGame = nullptr;    34        
	//printMenu(); //the program just started and therefore for sure no paused game exists
	//cin >> choice;

	//while (choice != Choice::EXIT)
	//{
	//	switch (choice)
	//	{
	//	case(Choice::START):
	//		pGame->start();
	//		if (pGame->getStatus == GameStatus:: PAUSED)
	//			system("cls");
	//		break;
	//	case(Choice::CONTINUE):
	//		if (pGame != nullptr && pGame->getStatus() == GameStatus::PAUSED)
	//			pGame->resume();
	//		else
	//			cout << "No paused game to continue !" << endl;
	//		break;
	//	case(Choice::INSTRUCTIONS):
	//		printInstructionsAndKeys(GameConfig:: INSTRUCTIONS_STR, GameConfig:: KEYS_STR);
	//		break;
	//	default:
	//		printChoiceError(); 
	//		break;
	//	}
	//	printMenu(pGame->getStatus());
	//	cin >> choice;
	//}
	//cout << "Good Game! Goodbye!" << endl;
	return 0;
}