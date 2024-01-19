#include "global_functions.h"

void printMenu(GameStatus gameStatus)
{
    printWelcomeMessage();
	cout << "Please enter your choice:\n" << "(1) Start a new game\n" ;
	if (gameStatus == GameStatus:: PAUSED)
	{
		cout << "(2) Continue a paused game\n";
	}
	cout << "(8) Present instructions and keys\n" << "(9) exit\n";
}

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
void printChoiceError()
{
	cout << "Wrong choice! Please Try again" << endl;
    Sleep(2000);
}

void printInstructionsAndKeys()
{
    Key key;
    bool showKeys = false;
    do {
        clearScreen();
        if (!showKeys) {
            printInstructions();
            cout << "\nPress Right arrow to see the game keys\nPress escape to return to the menu";
        }
        else {
            printKeys();
            cout << "\nPress Left arrow to go back to instructions\nPress escape to return to the menu";
        }
        key = _getch(); // Wait for user input
        if (key == RIGHT_ARROW && !showKeys) {  // Right arrow key
            showKeys = true;
        }
        else if (key == LEFT_ARROW && showKeys) {  // Left arrow key
            showKeys = false;
        }

    } while (key != ESC);  // Continue the loop until the user presses Esc
}
void clearScreen()
{
    system("cls");
}
void printWinner(Game& game)
{
    short int winnerNum = game.getWinnerNum();
    if (game.getStatus() == GameStatus::FINISHED && winnerNum != NO_WINNER)
    {
        if (winnerNum == TIE)
            cout << "The game ended in a tie!";
        else // there is a winnner
            cout << "The Winner is: " << game.getPlayer(winnerNum).getName();
        cout << "\n\n\nPress any key to continue........";
        // the game was finished and the winner was used, no more need for him after that
        game.setWinnerNum(NO_WINNER);
        while (!_kbhit());
        clearScreen();
    }
}

void clearCin()
{
    cin.clear();
    while (cin.get() != '\n');
}

void printInstructions()
{
    // Display Tetris game instructions
    cout << "Tetris Game Instructions:" << endl;
    // Provide instructions for playing Tetris
    cout << "1. Use arrow keys to move and rotate the falling blocks." << endl;
    cout << "2. Fill complete rows to clear them and score points." << endl;
    cout << "3. The game ends when the blocks reach the top of the screen." << endl;
}
void printKeys()
{
    // Display keys for Player 1
    cout << "Player 1 Keys:" << endl << endl;
    cout << " - Rotate Left = W    S Rotate Right -" << endl;
    cout << " |                +---+              |" << endl;
    cout << "\\/                | W |              \\/" << endl;
    cout << "              +---+---+---+" << endl;
    cout << " <- Move Left | A | S | D | Move Right ->" << endl;
    cout << "              +---+---+---+" << endl;
    cout << "                  | X |" << endl;
    cout << "                  +---+" << endl;
    cout << "                  Drop" << endl;
    cout << "                    |" << endl;
    cout << "                   \\/" << endl;

    // Display keys for Player 2
    cout << "Player 2 Keys:" << endl << endl;
    cout << " - Rotate Left = I    K Rotate Right -" << endl;
    cout << " |                +---+              |" << endl;
    cout << "\\/                | I |             \\/" << endl;
    cout << "              +---+---+---+" << endl;
    cout << " <- Move Left | J | K | L | Move Right ->" << endl;
    cout << "              +---+---+---+" << endl;
    cout << "                  | M |" << endl;
    cout << "                  +---+" << endl;
    cout << "                  Drop" << endl;
    cout << "                    |" << endl;
    cout << "                   \\/" << endl;
}
void printColorOption() {
    cout << "You have decided to start a new game!\n";
    cout << "Please select coloring option for the game :\n";
    cout << "(1) for colorized game\n(2) for uncolorized game\n";
}