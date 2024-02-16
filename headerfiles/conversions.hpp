#ifndef conversions
#define conversions

#include <iostream>
#include <vector>
#include <cstdlib>
#include <iomanip>
#include <algorithm>
#include <bits/stdc++.h>
#include <sstream>

using namespace std;

#include "checkgamestatus.hpp"
#include "newgame.hpp"

#define gettupple(int, tuple) (get<int>(tuple))

typedef vector<tuple<int, int>> gameturns_array;



string **gamearray_to_game(gameturns_array gamearray)
{
    string **game = new_game();
    for (int i = 0; i < gamearray.size(); i++)
    {
        if (i % 2 == 0)
        {
            game[gettupple(0, gamearray[i])][gettupple(1, gamearray[i])] = "X";
        }
        else if (i % 2 == 1)
        {
            game[gettupple(0, gamearray[i])][gettupple(1, gamearray[i])] = "O";
        }
    }
    return game;
}

string gamearray_to_printedline(gameturns_array ga)
{
    stringstream ss;

    bool firstTuple = true;
    for (auto &&j : ga)
    {
        if (!firstTuple)
        {
            ss << ",";
        }
        else
        {
            firstTuple = false;
        }
        ss << gettupple(0, j) << gettupple(1, j);
    }
    return ss.str();
}

gameturns_array printedline_to_gamearray(string str)
{
    vector<string> vec;
    gameturns_array game;
    stringstream ss(str);
    string word;
    while (!ss.eof())
    {
        getline(ss, word, ',');
        vec.push_back(word);
    }

    for (auto &&i : vec)
    {
        char *char_arr = &i[0];
        game.push_back(make_tuple(char_arr[0] - '0', char_arr[1] - '0'));
    }

    return game;
}

#endif