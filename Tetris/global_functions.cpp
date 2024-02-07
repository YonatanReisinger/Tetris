#include "global_functions.h"

/************************
* Name: printMenu
* Input: GameStatus gameStatus (The current status of the game)
* Output: None
* Description: Prints the game menu based on the provided game status.
  Displays options for starting a new game, continuing a paused game, presenting instructions, and exiting.
************************/
void printMenu(Game* pGame)
{
    printWelcomeMessage();
	cout << "Please enter your choice:" << endl
        << "(" << Choice::START_HUMAN_VS_HUMAN << ") Start a new game - Human vs Human" << endl
        << "(" << Choice::START_HUMAN_VS_CPU << ") Start a new game - Human vs Computer" << endl
        << "(" << Choice::START_CPU_VS_CPU << ") Start a new game - Computer vs Computer" << endl;
    // if there is a game and it is paused
	if (pGame != nullptr && pGame->getStatus() == GameStatus::PAUSED)
	{
		cout << "(" << Choice:: CONTINUE <<") Continue a paused game" << endl;
	}
    cout << "(" << Choice::INSTRUCTIONS << ") Present instructions and keys" << endl
        << "(" << Choice:: EXIT << ") exit" << endl;
}
/************************
* Name: printWelcomeMessage
* Input: None
* Output: None
* Description: Prints a welcome message for the Tetris game.
************************/

void printWelcomeMessage()
{
    string message = "Welcome to Tetris! Have fun playing!";
    int width = message.length() + 6;
    // Print the top frame
    for (int i = 0; i < width; ++i) {
        cout << '*';
    }
    cout << endl;
    // Print the message frame
    cout << "* " << message << " *" << endl;
    // Print the bottom frame
    for (int i = 0; i < width; ++i) {
        cout << '*';
    }
    cout << endl << endl;
}
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
void showConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO     cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}