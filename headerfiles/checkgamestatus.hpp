#ifndef checkgamestatus
#define checkgamestatus

#include <iostream>
#include <vector>
#include <string>

using namespace std;



string checkGameStatus(const string *const *board)
{
    string winner;
    // Rows and columns
    for (int i = 0; i < 3; ++i)
    {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != " ")
        {
            return board[i][0];
        }

        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != " ")
        {
            return board[0][i];
        }
    }

    // Diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != " ")
    {
        winner = board[0][0];
        for (int i = 0; i < 3; ++i)
        {
            delete[] board[i];
        }
        delete[] board;
        return winner;
    }

    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != " ")
    {
        winner = board[0][2];
        for (int i = 0; i < 3; ++i)
        {
            delete[] board[i];
        }
        delete[] board;
        return winner;
    }

    // Check draw
    bool isDraw = true;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (board[i][j] == " ")
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
        for (int i = 0; i < 3; ++i)
        {
            delete[] board[i];
        }
        delete[] board;
        return "draw";
    }

    return "running";
}
#endif