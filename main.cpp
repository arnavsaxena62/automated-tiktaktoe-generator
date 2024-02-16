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


using namespace std;

#define gettupple(int, tuple) (get<int>(tuple))
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


int main()
{
    clock_t start, end;
    start = clock();
    srand(time(NULL));

    // string input = "21,01,10,20,12,00,02,11,22";
    // gameturns_array testarray = printedline_to_gamearray(input);
    // string** game = gamearray_to_game(testarray);
    // printGame(game);

    // gameturns_array gamearray = generateRandomGame();
    // cout<<gamearray_to_printedline(gamearray)<<endl;
    // printGame(gamearray_to_game(gamearray));

    vector<gameturns_array> Xwins;
    ofstream Xwinsfile("Xwins.txt");
    vector<gameturns_array> Owins;
    ofstream Owinsfile("Owins.txt");
    vector<gameturns_array> draw;
    ofstream drawfile("draw.txt");
    int total = 100000;

    for (int i = 0; i < total; i++)
    {
        gameturns_array game = generateRandomGame();
        string win = checkGameStatus(gamearray_to_game(game));

        auto existsInVector = [](const gameturns_array &game, const std::vector<gameturns_array> &vec)
        {
            return find(vec.begin(), vec.end(), game) != vec.end();
        };

        if (win == "X" && !existsInVector(game, Xwins))
        {
            Xwins.push_back(game);
        }
        else if (win == "O" && !existsInVector(game, Owins))
        {
            Owins.push_back(game);
        }
        else if (!existsInVector(game, draw))
        {
            draw.push_back(game);
        }
        else
        {
            i--;
        }
        cout << '\r' << std::setprecision(2) << std::fixed << ((static_cast<double>(i) / total) * 100) << " %";
        cout.flush(); 
    }

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
    cout<<endl;
    end = clock();
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "Time taken by program is : " << fixed
         << time_taken << setprecision(5);
    cout << " sec " << endl;
    return 0;
}