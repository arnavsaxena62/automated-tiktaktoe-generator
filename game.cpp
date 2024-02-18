#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <time.h>

#include "headerfiles\conversions.hpp"
#include "headerfiles\extractgame.hpp"

using namespace std;



tuple<int, int> input_to_addr(string s)
{
    const char *str = s.c_str();
    return make_tuple(str[0] - '0', str[1] - '0');
}

bool startsWith(const gameturns_array &vec, const gameturns_array &sequence)
{
    if (vec.size() < sequence.size())
        return false;

    for (size_t i = 0; i < sequence.size(); ++i)
    {
        if (vec[i] != sequence[i])
            return false;
    }
    return true;
}

vector<gameturns_array> find_game(vector<gameturns_array> vga, gameturns_array currentgame)
{

    vector<gameturns_array> resultVector;
    for (const auto &innerVector : vga)
    {
        if (startsWith(innerVector, currentgame))
        {
            resultVector.push_back(innerVector);
        }
    }
    return resultVector;
}

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

int main()
{
    srand(time(NULL));
    // vector<gameturns_array> testvector = extractgames("Xwins");
    // gameturns_array input = printedline_to_gamearray("20,11,02");

    // vector<gameturns_array> resultList = find_game(testvector, input);

    gameturns_array game;
    vector<gameturns_array> resultList = extractgames("Xwins");
    while (checkGameStatus(gamearray_to_game(game)) == "running")
    {
        string input;
        cin >> input;

        tuple<int, int> inputTuple = input_to_addr(input);

        game.push_back(inputTuple);

        cout << "input recorded" << endl;
        cout << "finding game" << endl;

        resultList = find_game(resultList, game);

        if (!resultList.empty())
        {
            cout << "game found" << endl;
            int randomIndex = rand() % resultList.size();
            gameturns_array chosengame = (resultList[randomIndex]);
            cout << "game chosen" << endl;
            game.push_back(chosengame[size(game)]);
        }
        else
        {
            resultList = find_game(extractgames("draw"), game);
            int randomIndex = rand() % resultList.size();
            gameturns_array chosengame = (resultList[randomIndex]);
            game.push_back(chosengame[size(game)]);
        }
        printGame(gamearray_to_game(game));
    }
    cout << checkGameStatus(gamearray_to_game(game));

    return 0;
}