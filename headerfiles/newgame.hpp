#ifndef newgame
#define newgame

#include <iostream>
#include <vector>
using namespace std;

string **new_game()
{
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
            game[i][j] = " ";
        }
    }
    return game;
}

#endif