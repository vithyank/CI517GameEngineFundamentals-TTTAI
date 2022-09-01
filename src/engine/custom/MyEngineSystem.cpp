#include "MyEngineSystem.h"
#include <Windows.h>
#include "MyEngineSystem.h"
#include "MyEngineSystem.h"


void MyEngineSystem::myFunction() {
    std::cout << "Initialize System";
}

void MyEngineSystem::createRandomMove(tttBoard arr[][3]) {
    //
    int count = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (arr[i][j].O || arr[i][j].X) {
                count++;
            }
        }
    }
    
    if (count < 9) {
        int a = rand() % 3;
        int b = rand() % 3;
        while (arr[a][b].X || arr[a][b].O) {
            a = rand() % 3;
            b = rand() % 3;
        }
        arr[a][b].O = true;
    }
}


using namespace std;

struct Move
{
    int row, col;
};



bool areMovesAvailable(tttBoard board[3][3])
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (!board[i][j].O || !board[i][j].X)
                return true;
    return false;
}

int evaluate(tttBoard b[3][3])
{
    // X or O victory is determined by checking rows.
    for (int row = 0; row < 3; row++)
    {
        if (b[row][0].X == b[row][1].X &&
            b[row][1].X == b[row][2].X)
        {
            if (b[row][0].O == b[row][1].O &&
                b[row][1].O == b[row][2].O) {


                if (b[row][0].O)
                    return +10;
                else if (b[row][0].X)
                    return -10;
            }
        }
    }

    //  X or O victory is determined by checking columns.
    for (int col = 0; col < 3; col++)
    {
        if (b[0][col].X == b[1][col].X &&
            b[1][col].X == b[2][col].X)
        {
            if (b[0][col].O == b[1][col].O &&
                b[1][col].O == b[2][col].O) {
                if (b[0][col].O)
                    return +10;

                else if (b[0][col].X)
                    return -10;
            }
        }
    }

    //  X or O victory is determined by checking diagonal positioning
    if (b[0][0].X == b[1][1].X && b[1][1].X == b[2][2].X)
    {
        if (b[0][0].O == b[1][1].O && b[1][1].O == b[2][2].O)
        {
            if (b[0][0].O)
                return +10;
            else if (b[0][0].X)
                return -10;
        }
    }

    if (b[0][2].X == b[1][1].X && b[1][1].X == b[2][0].X)
    {
        if (b[0][2].O == b[1][1].O && b[1][1].O == b[2][0].O)
        {
            if (b[0][2].O)
                return +10;
            else if (b[0][2].X)
                return -10;
        }
    }

    // if no winning conditions met, return 0.
    return 0;
}

//Minimax function (referenced and edited for my game https://www.geeksforgeeks.org/minimax-algorithm-in-game-theory-set-3-tic-tac-toe-ai-finding-optimal-move/?ref=rp)
int minimax(tttBoard board[3][3], int depth, bool isMax)
{
    int score = evaluate(board);

    
    if (score == 10)
        return score;

   
    if (score == -10)
        return score;


    if (areMovesAvailable(board) == false)
        return 0;

    if (isMax)
    {
        int best = -1000;

        
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                //checks if space on board is empty
                if (!board[i][j].O && !board[i][j].X)
                {
                    // Move is made
                    board[i][j].O = true;

                    
                    best = max(best,
                        minimax(board, depth + 1, !isMax));

                    
                    board[i][j].O = false;
                }
            }
        }
        return best;
    }

    // If this minimizer's move
    else
    {
        int best = 1000;

       
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                //checks if space on board is empty
                if (!board[i][j].O && !board[i][j].X)
                {
                    // Move is made
                    board[i][j].X = true;

                  
                    best = min(best,
                        minimax(board, depth + 1, !isMax));

                    
                    board[i][j].X = false;
                }
            }
        }
        return best;
    }
}

// This functionfinds best space to place O (naught).
Move findBestMove(tttBoard board[3][3])
{
    int bestVal = -1000;
    Move bestMove;
    bestMove.row = -1;
    bestMove.col = -1;

    
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            //checks if space on board is empty
            if (!board[i][j].O && !board[i][j].X)
            {
                // Move is made
                board[i][j].O = true;


                int moveVal = minimax(board, 0, false);

                
                board[i][j].O = false;

               //Here, if the moves value is more than the best value, the best move is updated.
                if (moveVal > bestVal)
                {
                    bestMove.row = i;
                    bestMove.col = j;
                    bestVal = moveVal;
                }
            }
        }
    }


    return bestMove;
}

void MyEngineSystem::aiMovement(tttBoard arr[][3]) {
    Move bestmove = findBestMove(arr);
    arr[bestmove.row][bestmove.col].O = true;
}