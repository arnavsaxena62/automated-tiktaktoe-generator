#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <time.h>
#include <iomanip>
#include <algorithm>
#include <bits/stdc++.h>
#include <sstream>
#include <fstream>

#include "headerfiles\generaterandomgame.hpp"
#include "headerfiles\conversions.hpp"
#include "headerfiles\extractgame.hpp"

using namespace std;

typedef vector<tuple<int, int>> gameturns_array;

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
    clock_t start, end;
    start = clock();
    srand(time(NULL));

    // string input = "12,21,22,00,02";
    // gameturns_array testarray = printedline_to_gamearray(input);
    // string** game = gamearray_to_game(testarray);
    // cout << checkGameStatus(game) <<endl;
    // printGame(game);

    // gameturns_array gamearray = generateRandomGame();
    // cout<<gamearray_to_printedline(gamearray)<<endl;
    // printGame(gamearray_to_game(gamearray));

    vector<gameturns_array> Xwins = extractgames("result/Xwins");
    ofstream Xwinsfile("result/Xwins.txt");
    vector<gameturns_array> Owins = extractgames("result/Owins");
    ofstream Owinsfile("result/Owins.txt");
    vector<gameturns_array> draw = extractgames("result/draw");
    ofstream drawfile("result/draw.txt");
    int total = 255168;

    for (int i = (size(Xwins) + size(Owins) + size(draw)); i < total; i++)
    {
        gameturns_array game = generateRandomGame();
        string win = checkGameStatus(gamearray_to_game(game));

        auto existsInVector = [](const gameturns_array &game, const std::vector<gameturns_array> &vec)
        {
            return find(vec.begin(), vec.end(), game) != vec.end();
        };
        bool firstTuple = true;
        if (win == "X" && !existsInVector(game, Xwins))
        {

            Xwins.push_back(game);
            for (auto &&tuples : game)
            {

                if (!firstTuple)
                {
                    Xwinsfile << ",";
                }
                else
                {
                    firstTuple = false; // Set flag to false after printing the first tuple
                }
                Xwinsfile << gettupple(0, tuples) << gettupple(1, tuples);
            }
            Xwinsfile << endl;
        }
        else if (win == "O" && !existsInVector(game, Owins))
        {
            Owins.push_back(game);
            for (auto &&tuples : game)
            {

                if (!firstTuple)
                {
                    Owinsfile << ",";
                }
                else
                {
                    firstTuple = false; // Set flag to false after printing the first tuple
                }
                Owinsfile << gettupple(0, tuples) << gettupple(1, tuples);
            }
            Owinsfile << endl;
        }
        else if (win == "draw" && !existsInVector(game, draw))
        {
            draw.push_back(game);
                       for (auto &&tuples : game)
            {

                if (!firstTuple)
                {
                    drawfile << ",";
                }
                else
                {
                    firstTuple = false; // Set flag to false after printing the first tuple
                }
                drawfile << gettupple(0, tuples) << gettupple(1, tuples);
            }
            drawfile << endl;
        }
        else
        {
            i--;
        }
        cout << '\r' << std::setprecision(2) << std::fixed << ((static_cast<double>(i) / total) * 100) << " %";
        cout.flush();
    }
    /*
    for (int i = 0; i < size(Xwins); i++)
    {
        bool firstTuple = true;
        for (auto &&j : Xwins[i])
        {
            if (!firstTuple)
            {
                Xwinsfile << ",";
            }
            else
            {
                firstTuple = false; // Set flag to false after printing the first tuple
            }
            Xwinsfile << gettupple(0, j) << gettupple(1, j);
        }
        Xwinsfile << endl;
    }
    for (int i = 0; i < size(Owins); i++)
    {
        bool firstTuple = true;
        for (auto &&j : Owins[i])
        {
            if (!firstTuple)
            {
                Owinsfile << ",";
            }
            else
            {
                firstTuple = false; // Set flag to false after printing the first tuple
            }
            Owinsfile << gettupple(0, j) << gettupple(1, j);
        }
        Owinsfile << endl;
    }
    for (int i = 0; i < size(draw); i++)
    {
        bool firstTuple = true;
        for (auto &&j : draw[i])
        {
            if (!firstTuple)
            {
                drawfile << ",";
            }
            else
            {
                firstTuple = false; // Set flag to false after printing the first tuple
            }
            drawfile << gettupple(0, j) << gettupple(1, j);
        }
        drawfile << endl;
    }
    */
    cout << endl;

    end = clock();
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "Time taken by program is : " << fixed
         << time_taken << setprecision(5);
    cout << " sec " << endl;
    return 0;
}