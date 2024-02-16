#ifndef generaterandomgame
#define generaterandomgame


#include <iostream>
#include <vector>

#include "checkgamestatus.hpp"
#include "newgame.hpp"

using namespace std;

typedef vector<tuple<int, int>> gameturns_array;

gameturns_array generateRandomGame()
{
    gameturns_array gameturns;

    string **game = new_game();
    // Start the game loop
    for (int turn = 0; turn < 9; turn++)
    {
        if (checkGameStatus(game) == "running")
        {
            int adr1 = rand() % 3;
            int adr2 = rand() % 3;
            if (game[adr1][adr2] == " ")
            {
                if (turn % 2 == 0)
                {
                    game[adr1][adr2] = "X";
                }
                else
                {
                    game[adr1][adr2] = "O";
                }
                gameturns.push_back(tuple<int, int>(adr1, adr2));
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
    }

    return gameturns;
}

#endif
