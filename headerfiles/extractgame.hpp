#ifndef extractgame
#define extractgame

#include <iostream>
#include <fstream>
#include <vector>

#include "conversions.hpp"

typedef vector<tuple<int, int>> gameturns_array;

using namespace std;

vector<gameturns_array> extractgames(string filename)
{
    vector<string> games_strings;
    vector<gameturns_array> game_arrays;
    string myText;

    ifstream MyReadFile(filename + ".txt");

    if (MyReadFile.is_open())
    {
        while (getline(MyReadFile, myText))
        {
            games_strings.push_back(myText);
        }
    }
    else
    {
        cout << "Error" << endl;
    }
    MyReadFile.close();

    for (auto &&i : games_strings)
    {
        game_arrays.push_back(printedline_to_gamearray(i));
    }
    return game_arrays;
}



#endif 