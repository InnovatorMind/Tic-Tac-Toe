#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <conio.h> // For _getch()

using namespace std;

class TicTacToe
{
private:
    vector<vector<char>> board;
    char currentPlayer;
    bool gameOver;

    // ANSI escape codes for cursor manipulation and colors
    const string CLEAR_SCREEN = "\033[2J\033[1;1H";
    const string CURSOR_UP = "\033[A";

    // Color codes
    const string RED = "\033[31m";
    const string GREEN = "\033[32m";
    const string YELLOW = "\033[33m";
    const string BLUE = "\033[34m";
    const string MAGENTA = "\033[35m";
    const string CYAN = "\033[36m";
    const string WHITE = "\033[37m";
    const string RESET = "\033[0m";
    const string BOLD = "\033[1m";

public:
    TicTacToe()
    {
        // Initialize the 3x3 board with empty spaces
        board = vector<vector<char>>(3, vector<char>(3, ' '));
        currentPlayer = 'X'; // X goes first
        gameOver = false;
    }

    void clearScreen()
    {
        cout << CLEAR_SCREEN;
    }

    void drawBoard()
    {
        clearScreen();
        cout << BOLD << CYAN << "Tic-Tac-Toe\n\n"
             << RESET;

        // Display current player with color
        string playerColor = (currentPlayer == 'X') ? RED : BLUE;
        cout << "Player " << playerColor << BOLD << currentPlayer << RESET << "'s turn\n\n";

        // Display column numbers
        cout << YELLOW << "  1 2 3\n"
             << RESET;

        for (int i = 0; i < 3; i++)
        {
            // Display row numbers
            cout << YELLOW << i + 1 << " " << RESET;

            for (int j = 0; j < 3; j++)
            {
                // Display X in red and O in blue
                if (board[i][j] == 'X')
                {
                    cout << RED << BOLD << 'X' << RESET;
                }
                else if (board[i][j] == 'O')
                {
                    cout << BLUE << BOLD << 'O' << RESET;
                }
                else
                {
                    cout << ' ';
                }

                if (j < 2)
                    cout << YELLOW << "|" << RESET;
            }
            cout << endl;
            if (i < 2)
                cout << YELLOW << "  -+-+-\n"
                     << RESET;
        }

        cout << "\n"
             << GREEN << "Use numpad (1-9) to place your mark or 'q' to quit\n"
             << RESET;
    }

    bool makeMove(int position)
    {
        // Convert position (1-9) to row and column
        int row = (position - 1) / 3;
        int col = (position - 1) % 3;

        // Check if the position is valid and not already occupied
        if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ')
        {
            board[row][col] = currentPlayer;
            return true;
        }
        return false;
    }

    bool checkWin()
    {
        // Check rows
        for (int i = 0; i < 3; i++)
        {
            if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][1] == board[i][2])
            {
                return true;
            }
        }

        // Check columns
        for (int i = 0; i < 3; i++)
        {
            if (board[0][i] != ' ' && board[0][i] == board[1][i] && board[1][i] == board[2][i])
            {
                return true;
            }
        }

        // Check diagonals
        if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2])
        {
            return true;
        }
        if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0])
        {
            return true;
        }

        return false;
    }

    bool checkDraw()
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] == ' ')
                {
                    return false;
                }
            }
        }
        return true;
    }

    void switchPlayer()
    {
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    void playGame()
    {
        char input;
        int position;

        clearScreen();

        while (!gameOver)
        {
            drawBoard();

            input = _getch(); // Get character without needing Enter key

            if (input == 'q' || input == 'Q')
            {
                cout << "\n"
                     << YELLOW << "Game ended by player.\n"
                     << RESET;
                return;
            }

            if (input >= '1' && input <= '9')
            {
                position = input - '0'; // Convert char to int

                if (makeMove(position))
                {
                    if (checkWin())
                    {
                        drawBoard();
                        string winnerColor = (currentPlayer == 'X') ? RED : BLUE;
                        cout << "\n"
                             << BOLD << GREEN << "Player " << winnerColor << currentPlayer << GREEN << " wins!" << RESET << "\n";
                        gameOver = true;
                    }
                    else if (checkDraw())
                    {
                        drawBoard();
                        cout << "\n"
                             << MAGENTA << BOLD << "It's a draw!" << RESET << "\n";
                        gameOver = true;
                    }
                    else
                    {

                        switchPlayer();
                    }
                }
            }
        }

        cout << CYAN << "Press any key to exit..." << RESET;
        _getch();
    }
};

int main()
{
// Enable ANSI escape sequences for Windows console
#ifdef _WIN32
    // Enable ANSI escape sequences in Windows console
    system("color");
    system("cls");
#else
    system("clear");
#endif

    TicTacToe game;
    game.playGame();

    return 0;
}
