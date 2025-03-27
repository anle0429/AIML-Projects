#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
using namespace std;

const char HUMAN = 'X';
const char AI = 'O';

void displayBoard(const char board[9]);
void emptySquares(const char board[9], int squares[9], int& num);
void askPlayerX(char board[]);
bool compareSquares(char b1, char b2, char b3);
char winnerCheck(const char board[9]);

int numEmptySquares(const char board[9]);
int minimax(char board[9], int depth, char player);
int bestMove(char board[9]);

int main()
{
    srand(time(NULL));
    char board[9] = { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' };
    char playerTurn = HUMAN;
    char winner = ' ';

    cout << "Welcome to Tic-Tac-Toe!" << endl;
    displayBoard(board);

  
    while (winner == ' ' && numEmptySquares(board) > 0)
    {
        if (playerTurn == HUMAN)
        {
            askPlayerX(board);
        }
        else
        {
            int move = bestMove(board);
            board[move] = AI;
            cout << "Computer chose square " << move + 1 << endl;
        }

        displayBoard(board);
        winner = winnerCheck(board);
        playerTurn = (playerTurn == HUMAN) ? AI : HUMAN;
    }

    if (winner != ' ')
    {
        cout << winner << " wins the game!" << endl;
    }
    else
    {
        cout << "The game is a draw!" << endl;
    }

    return 0;
}

void displayBoard(const char board[9])
{
    cout << endl << endl;
    int row = 0;
    for (int i = 0; i < 3; ++i)
    {
        cout << "   " << board[row] << " | " << board[row + 1] << " | " << board[row + 2] << endl;
        if ((row == 0) || (row == 3))
        {
            cout << "  -----------" << endl;
        }
        row += 3;
    }
    cout << endl << endl;
}

void emptySquares(const char board[9], int squares[9], int& num)
{
    num = 0;
    for (int i = 0; i < 9; ++i)
    {
        if (board[i] == ' ')
        {
            squares[num] = i;
            ++num;
        }
    }
}

void askPlayerX(char board[])
{
    bool validChoice = false;
    int n;
    do {
        cout << "Enter a square number (1-9): ";
        cin >> n;
        --n;
        if (n >= 0 && n < 9 && board[n] == ' ')
        {
            validChoice = true;
            board[n] = HUMAN;
        }
        else
        {
            cout << endl << "Must choose an empty square" << endl << endl;
            validChoice = false;
        }
    } while (validChoice == false);
}

bool compareSquares(char b1, char b2, char b3)
{
    return (b1 == b2 && b2 == b3 && b1 != ' ');
}

char winnerCheck(const char board[9])
{
    for (int i = 0; i < 9; i += 3)
    {
        if (compareSquares(board[i], board[i + 1], board[i + 2]))
        {
            return board[i];
        }
    }

    for (int i = 0; i < 3; ++i)
    {
        if (compareSquares(board[i], board[i + 3], board[i + 6]))
        {
            return board[i];
        }
    }
    if (compareSquares(board[0], board[4], board[8]))
    {
        return board[0];
    }
    if (compareSquares(board[2], board[4], board[6]))
    {
        return board[2];
    }
    return ' ';
}

int numEmptySquares(const char board[9])
{
    int count = 0;
    for (int i = 0; i < 9; i++)
    {
        if (board[i] == ' ')
        {
            count++;
        }
    }
    return count;
}

int minimax(char board[9], int depth, char player)
{
    char result = winnerCheck(board);
    if (result == HUMAN)
        return 1;
    else if (result == AI)
        return -1;
    if (numEmptySquares(board) == 0)
        return 0;

   
    if (depth >= 3)
    {
        cout << "Depth limit reached at depth " << depth << endl;
        return 0;
    }

    int bestScore;
    if (player == HUMAN)
    {
        bestScore = -10;
        for (int i = 0; i < 9; i++)
        {
            if (board[i] == ' ')
            {
                board[i] = HUMAN;
                int score = minimax(board, depth + 1, AI);
                board[i] = ' ';
                bestScore = max(score, bestScore);
            }
        }
    }
    else // player == AI
    {
        bestScore = 10;
        for (int i = 0; i < 9; i++)
        {
            if (board[i] == ' ')
            {
                board[i] = AI;
                int score = minimax(board, depth + 1, HUMAN);
                board[i] = ' ';
                bestScore = min(score, bestScore);
            }
        }
    }
    return bestScore;
}

int bestMove(char board[9])
{
    int bestMoveIndex = -1;
    vector<int> winningOptions;
    vector<int> tieOptions;
    vector<int> losingOptions;
    int depth = 1;

    for (int i = 0; i < 9; i++)
    {
        if (board[i] == ' ')
        {
            board[i] = AI;
            char result = winnerCheck(board);
            if (result == AI)
            {
                winningOptions.push_back(i);
            }
            else
            {
                int score = minimax(board, depth, HUMAN);
                if (score == -1)
                    winningOptions.push_back(i);
                else if (score == 0)
                    tieOptions.push_back(i);
                else if (score == 1)
                    losingOptions.push_back(i);
            }
            board[i] = ' ';
        }
    }

    if (winningOptions.empty() == false)
    {
        int num = rand() % winningOptions.size();
        bestMoveIndex = winningOptions[num];
    }
    else if (tieOptions.empty() == false)
    {
        int num = rand() % tieOptions.size();
        bestMoveIndex = tieOptions[num];
    }
    else if (losingOptions.empty() == false)
    {
        int num = rand() % losingOptions.size();
        bestMoveIndex = losingOptions[num];
    }
    return bestMoveIndex;
}
