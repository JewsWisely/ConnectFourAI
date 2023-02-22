#include <math.h>
#include <time.h>
#include "BoardAI.h"
#include "Board.h"

static float minimax(Board* pb, short lastMove, short depth, float alpha, float beta);

static short getMoves(Board* pb, short* moves);

static float staticEvaluation(Board* pb, short lastMove);

static float max(float x, float y);

static float min(float x, float y);

short winsPerSlot[row][col] = {{3, 4, 5, 7, 5, 4, 3},
                        {4, 6, 8, 10, 8, 6, 4},
                        {5, 8, 11, 13, 11, 8, 5},
                        {5, 8, 11, 13, 11, 8, 5},
                        {4, 6, 8, 10, 8, 6, 4},
                        {3, 4, 5, 7, 5, 4, 3}};

int winValue = 1000;


/**
    put a piece in the column that results in the best position, return that column
**/
short makeAIMove(Board* pb){

    //keep track of how many AI moves have been made
    static short count = 0;

    //maxDepth starts at 42 and decreases over the course of the game.
    //maxDepth is not affected by the number of human moves,
    //so it is not perfect. maxDepth >= empty grid squares
    short maxDepth = row * col - count;

    //hold the value of the column that yields the best move
    short bestMoveIndex = -1;

    //hold the initial values for alpha and beta for pruning
    //TODO: look into changing these values in the iterative deepening algorithm
    float alpha = -winValue, beta = winValue;

    //retrieve the set of all possible moves and store them in moves
    //moves is dynamically allocated and initialized with size col, then
    //resized based on how many valid moves exist
    short* moves = malloc(col * sizeof(short));
    short numMoves = getMoves(pb, moves), numUnsolvedMoves = numMoves;
    moves = realloc(moves, numMoves * sizeof(short));

    //t0 is a time marker for the beginning of the function
    time_t t0 = time(NULL);

    //APPROXIMATELY how many seconds the AI has to think
    //the real time it takes to think will be greater if it can not search
    //the entire remaining game tree in less time.
    //MUST be >= 1
    short timeToThink = 5;

    //keeps track of whether we should exit the loop, whether because
    //the time has expired, there is only one move left, or a win is found
    bool timeToStop = false;

    //keeps track of which columns, among those that have valid moves,
    //do not need to be searched. This happens when the result of playing in a
    //certain column is known (solved), meaning we know who will win if we play
    //in that column
    short solvedColumns[col] = {0};

    //begin the search at depth 1 and increase depth until maxDepth is reached.
    //this is called iterative deepening, and it allows for some optimizations of
    //the minimax algorithm. For example, when coupled with the solvedColumns array,
    //we don't need to search columns at depth 15 if they are solved at depth 5.
    short depth = 1;
    for( ; depth <= maxDepth; depth++){

        printf("\nsearching depth %d", depth);

        //in each iteration with a new depth, we assume a new index and value for
        //the best move.
        short tempBestMoveIndex = bestMoveIndex;
        float tempBestMoveValue = pb->player == red ? alpha : beta;

        for(short i = 0; i < numMoves; i++){
            if(time(NULL) - t0 >= timeToThink){
                timeToStop = true;
                break;
            }
            short column = *(moves + i);
            if(!solvedColumns[column]){
                if(numUnsolvedMoves == 1){
                    printf("\nonly 1 move");
                    bestMoveIndex = column;
                    timeToStop = true;
                    break;
                }
                putPiece(pb, column);
                float temp = minimax(pb, column, depth - 1, alpha, beta);
                removePiece(pb, column);
                if(temp / winValue == pb->player){
                    bestMoveIndex = column;
                    timeToStop = true;
                    break;
                }
                if(abs(temp / winValue) == 1){
                    solvedColumns[column] = 1;
                    numUnsolvedMoves--;
                    //printf("\ncolumn %d: %f", column, temp);
                    continue;
                }
                if(pb->player == red){
                    if(temp > tempBestMoveValue){
                        tempBestMoveIndex = column;
                        tempBestMoveValue = temp;
                    }
                }
                else{
                    if(temp < tempBestMoveValue){
                        tempBestMoveIndex = column;
                        tempBestMoveValue = temp;
                    }
                }
            }
        }
        if(timeToStop)
            break;
        bestMoveIndex = tempBestMoveIndex;

    }

    count++;
    free(moves);
    putPiece(pb, bestMoveIndex);
    printf("\ntime: %d seconds\nmoves searched ahead: %d moves", time(NULL) - t0, depth);
    return bestMoveIndex;
}


/**
    return value of a given board state after performing minimax with param depth
**/
static float minimax(Board* pb, short lastMove, short depth, float alpha, float beta){

    if(depth <= 0 || winner(pb, lastMove)){
        return staticEvaluation(pb, lastMove);
    }

    short* moves = malloc(col * sizeof(short));
    short numMoves = getMoves(pb, moves);
    moves = realloc(moves, numMoves * sizeof(short));

    float guarantee = pb->player == red ? -winValue : winValue;
    for(int i = 0; i < numMoves; i++){
        putPiece(pb, *(moves + i));
        float nextEval = minimax(pb, *(moves + i), depth - 1, alpha, beta);
        removePiece(pb, *(moves + i));
        guarantee = pb->player == red ? max(guarantee, nextEval) : min(guarantee, nextEval);
        if(pb->player == red)
            alpha = max(alpha, guarantee);
        else
            beta = min(beta, guarantee);
        if(alpha > beta)
            break;
    }

    free(moves);
    return guarantee;
}

/**
    return number of valid moves, store valid moves in param moves
**/
static short getMoves(Board* pb, short* moves){
    short count = 0;
    if(pb->top[3] >= 0)
        *(moves + count++) = 3;
    if(pb->top[2] >= 0)
        *(moves + count++) = 2;
    if(pb->top[4] >= 0)
        *(moves + count++) = 4;
    if(pb->top[1] >= 0)
        *(moves + count++) = 1;
    if(pb->top[5] >= 0)
        *(moves + count++) = 5;
    if(pb->top[0] >= 0)
        *(moves + count++) = 0;
    if(pb->top[6] >= 0)
        *(moves + count++) = 6;
    return count;
}

static float staticEvaluation(Board* pb, short lastMove){
    if(winner(pb, lastMove))
        return pb->board[pb->top[lastMove] + 1][lastMove] * winValue;

    float score = 0;
    for(int c = 0; c < col; c++){
        for(int r = pb->top[c] + 1; r < row; r++){
            //score += pb->board[r][c] / ((min(abs(r - 3), abs(r - 2)) + 1) * (abs(c - 3) + 1));
            score += pb->board[r][c] * winsPerSlot[r][c];
        }
    }
    return score;
}

/**
    return the maximum of two floats
**/
static float max(float x, float y){
    return (x > y) ? x : y;
}

/**
    return the minimum of two floats
**/
static float min(float x, float y){
    return (x < y) ? x : y;
}
