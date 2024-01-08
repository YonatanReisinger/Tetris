// Imports -> 
#include <iostream>
#include <conio.h>
#include <windows.h>
#include "global_functions.h"
#include "Shape.h"
#include "Game.h"
#include "Point.h"
#include "gameConfig.h"
using namespace std;
// <- Imports 

// Macros and enums ->
enum Choice{ START = 1, CONTINUE = 2, INSTRUCTIONS = 8, EXIT = 9};
// <- Macros and enums

int main()
{
	Game* pGame;
	unsigned int choice;
	Board board1(Point(0, 0), Point(GameConfig::WIDTH + 1, 0), Point(0, GameConfig::HEIGHT + 1), Point(GameConfig::WIDTH + 1, GameConfig::HEIGHT + 1));
	Board board2(Point(GameConfig::WIDTH + 1 + GameConfig::DISTANCE_BETWEEN_BOARDS + 1, 0)
		, Point((GameConfig::WIDTH + 1) * 2 + GameConfig::DISTANCE_BETWEEN_BOARDS + 1, 0)
		, Point(GameConfig::WIDTH + 1 + GameConfig::DISTANCE_BETWEEN_BOARDS + 1, GameConfig::HEIGHT + 1)
		, Point((GameConfig::WIDTH + 1) * 2 + GameConfig::DISTANCE_BETWEEN_BOARDS + 1, GameConfig::HEIGHT + 1));
	Player player1(board1, "Daniel"), player2(board2, "Yonatan");
	
	//board1.print();
	//board2.print();
	
	Point p1(10, 12), p2(14,19);
	p1.print();
	p1.moveRight();
	Sleep(1000);
	p1.print();
	p1.copy(&p2);
	p1.gotoxy();
	//pGame = nullptr;
	//printMenu(); //the program just started and therefore for sure no paused game exists
	//cin >> choice;

	//while (choice != Choice::EXIT)
	//{
	//	switch (choice)
	//	{
	//	case(Choice::START):
	//		if (pGame != nullptr && (pGame->getStatus() == GameStatus::FINISHED || pGame->getStatus() == GameStatus::PAUSED))
	//			delete pGame;
	//		//pGame = new Game;
	//		pGame->start();
	//			break;
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