#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

#define gettupple(int, tuple) (get<int>(tuple))

int printGame(string **game)
{
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            cout << game[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}

tuple<int, int> strToAddr(string input)
{
    char *char_arr = &input[0];
    return make_tuple(char_arr[0] - '0', char_arr[1] - '0');
}

string checkGameStatus(const string *const *board)
{
    // Rows and columns
    for (int i = 0; i < 3; ++i)
    {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != "")
        {
            return board[i][0];
        }

        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != "")
        {
            return board[0][i];
        }
    }

    // Diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != "")
    {
        return board[0][0];
    }

    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != "")
    {
        return board[0][2];
    }

    // Check draw
    bool isDraw = true;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (board[i][j] == "")
            {
                isDraw = false;
                break;
            }
        }
        if (!isDraw)
        {
            break;
        }
    }

    if (isDraw)
    {
        return "draw";
    }

    return "running";
}

string **generateRandomGame()
{
    // Dynamically allocate memory for the game board
    string **game = new string *[3];
    for (int i = 0; i < 3; ++i)
    {
        game[i] = new string[3];
    }

    // Initialize the game board
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            game[i][j] = "";
        }
    }

    // Start the game loop
    for (int turn = 0; turn < 9; turn++)
    {
        if (checkGameStatus(game) == "running")
        {
            int adr1 = rand() % 3;
            int adr2 = rand() % 3;
            if (game[adr1][adr2] == "")
            {
                if (turn % 2 == 0)
                {
                    game[adr1][adr2] = "X";
                }
                else
                {
                    game[adr1][adr2] = "O";
                }
            }
            else
            {
                turn--; // Decrement turn if the selected cell is not empty
            }
        }
        else
        {
            break;
        }
        if (turn == 9 && checkGameStatus(game) == "draw")
        {
            for (int i = 0; i < 3; ++i)
            {
                for (int j = 0; j < 3; ++j)
                {
                    if (game[i][j] == "")
                    {
                        game[i][j] = (rand() % 2 == 0) ? "X" : "O";
                    }
                }
            }
        }
    }

    return game;
}

int main()
{
    srand(time(NULL));

    for (int i = 0; i < 10; i++)
    {

        string **game = generateRandomGame();

        printGame(game);

        cout << "-----------" << checkGameStatus(game) << endl;

        for (int i = 0; i < 3; ++i)
        {
            delete[] game[i];
        }
        delete[] game;
    }
    return 0;
}