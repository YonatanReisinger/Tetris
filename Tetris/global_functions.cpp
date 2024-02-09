#include "global_functions.h"

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