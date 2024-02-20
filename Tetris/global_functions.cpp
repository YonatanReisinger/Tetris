#include "global_functions.h"

/************************
* Name: printChoiceError
* Input: None
* Output: None
* Description: Prints an error message for an incorrect menu choice.
************************/
void printChoiceError()
{
	cout << "Wrong choice! Please Try again" << "\n\n\nPress any key to continue........";
    while (!_kbhit());
}
/************************
* Name: clearScreen
* Input: None
* Output: None
* Description: Clears the console screen.
************************/
void clearScreen()
{
    system("cls");
}
/************************
* Name: clearCin
* Description: Clears the cin function buffer.
************************/
void clearCin()
{
    cin.clear();
    while (cin.get() != '\n');
}
/************************
* Name: printColorOption
* Input: None
* Output: None
* Description: Prompts the player to select a coloring option for the game (colorized or uncolorized).
************************/
void printColorOption()
{
    cout << "You have decided to start a new game!\n";
    cout << "Please select coloring option for the game :\n";
    cout << "(1) for colorized game\n(2) for uncolorized game\n";
}
/************************
* Name: showConsoleCursor
* Input: bool showFlag (Flag to indicate whether to show or hide the console cursor)
* Output: None
* Description: Controls the visibility of the console cursor based on the provided flag. Uses the Windows API functions to retrieve and modify the cursor information.
************************/
void showConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO     cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}
ostream& operator<<(std::ostream& os, Choice choice)
{
    return cout << (unsigned int)choice;
}
void prepareCpuVsCpu(Player* &cpu1, Player* &cpu2, const Board& board1, const Board& board2)
{
    Computer* tempCpu1, * tempCpu2;

    cpu1 = new Computer(board1, GameConfig::player1Keys, "CPU 1");
    cpu2 = new Computer(board2, GameConfig::player2Keys, "CPU 2");

    tempCpu1 = dynamic_cast<Computer*>(cpu1);
    tempCpu2 = dynamic_cast<Computer*>(cpu2);

    cout << "Player1:" << endl;
    tempCpu1->setLevel(Computer::getLevelFromKeyboard());
    clearScreen();
    cout << "Player2:" << endl;
    tempCpu2->setLevel(Computer::getLevelFromKeyboard());
    clearScreen();
}
void prepareHumanVsCpu(Player*& cpu2, const Board& board2)
{
    Computer* tempCpu2;

    cpu2 = new Computer(board2, GameConfig::player2Keys, "CPU 2");
    tempCpu2 = dynamic_cast<Computer*>(cpu2);
    cout << "Player2:" << endl;
    tempCpu2->setLevel(Computer::getLevelFromKeyboard());
    clearScreen();
}