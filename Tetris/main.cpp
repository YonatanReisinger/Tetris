// Imports -> 
#include <iostream>
#include <conio.h>
#include <windows.h>
#include "global_functions.h"
#include "Shape.h"
#include "Game.h"
#include "Point.h"
using namespace std;
// <- Imports 

// Macros and enums ->
enum Choice{ START = 1, CONTINUE = 2, INSTRUCTIONS = 8, EXIT = 9};
#define INSTRUCTIONS_STR "blabla"
#define KEYS_STR "bloblo"

// <- Macros and enums

int main()
{
	Game* pGame;
	unsigned int choice;
	Board board1, board2(Point(18,0), Point(31, 0), Point(18, HEIGHT + 1), Point(31, HEIGHT + 1));
	Player player1(board1, "Daniel"), player2(board2, "Yonatan");
	
	board1.print();
	board2.print();
	cout << "gitHub test" << endl;
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
	//		printInstructionsAndKeys(INSTRUCTIONS_STR, KEYS_STR);
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