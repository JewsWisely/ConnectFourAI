#include <math.h>
#include <time.h>
#include <stdio.h>
#include "BoardAI.h"

static float minimax(Board* pb, short depth, float alpha, float beta, time_t t0);

//static short getMoves(Board* pb, short* moves);

static float staticEvaluation(Board* pb);

static float max(float x, float y);

static float min(float x, float y);

short winsPerSlot[row][col] = {{3, 4, 5, 7, 5, 4, 3},
                        {4, 6, 8, 10, 8, 6, 4},
                        {5, 8, 11, 13, 11, 8, 5},
                        {5, 8, 11, 13, 11, 8, 5},
                        {4, 6, 8, 10, 8, 6, 4},
                        {3, 4, 5, 7, 5, 4, 3}};

int winValue = 1000;

//how many seconds the AI has to think
//MUST be >= 1
short timeToThink = 5;

/**
    put a piece in the column that results in the best position, return that column
**/
short makeAIMove(Board* pb, TranspositionTable* table){

    //maxDepth starts at 42 and decreases over the course of the game.
    //maxDepth is not affected by the number of human moves,
    //so it is not perfect. maxDepth >= empty grid squares
    short maxDepth = row * col;

    //hold the value of the column that yields the best move
    short bestMoveIndex = -1;
    float bestMoveValue;

    //retrieve the set of all possible moves and store them in moves
    //moves is dynamically allocated and initialized with size col, then
    //resized based on how many valid moves exist
    short* moves = malloc(col * sizeof(short));
    short numMoves = listMoves(pb, moves), numUnsolvedMoves = numMoves;
    //moves = realloc(moves, numMoves * sizeof(short));

    //keeps track of whether we should exit the loop, whether because
    //the time has expired, there is only one move left, or a win is found
    bool timeToStop = false;

    //keeps track of which columns, among those that have valid moves,
    //do not need to be searched. This happens when the result of playing in a
    //certain column is known (solved), meaning we know who will win if we play
    //in that column
    short solvedColumns[col] = {0};


    //t0 is a time marker for the beginning of the function
    time_t t0 = time(NULL);

    printf("\nThinking...");

    //begin the search at depth 1 and increase depth until maxDepth is reached.
    //this is called iterative deepening, and it allows for some optimizations of
    //the minimax algorithm. For example, when coupled with the solvedColumns array,
    //we don't need to search columns at depth 15 if they are solved at depth 5.
    short depth = 1;
    for( ; depth <= maxDepth; depth++){

        //hold the initial values for alpha and beta for pruning
        //TODO: look into changing these values in the iterative deepening algorithm
        float alpha = -winValue, beta = winValue;

        //printf("\nsearching depth %d", depth);

        //in each iteration with a new depth, we assume a new index and value for
        //the best move.
        short tempBestMoveIndex = bestMoveIndex;
        float tempBestMoveValue = !(pb->counter & 1) ? alpha : beta;
        short i = 0;

        for( ; i < numMoves; i++){
            if(time(NULL) - t0 >= timeToThink){
                timeToStop = true;
                break;
            }
            short column = moves[i];
            if(!solvedColumns[column]){
                if(numUnsolvedMoves == 1){
                    //printf("\nonly 1 move");
                    bestMoveIndex = column;
                    timeToStop = true;
                    break;
                }

                /*
                    I made the choice here to pass -winValue and winValue for
                    alpha and beta instead of the values I know them to be.
                    The reason for this is because if I pass the real values
                    of alpha and beta, it will prune at this level. This means
                    that it may not realize that certain positions are lost.
                    For example, in the position after (3, 3), (2, ) the AI realizes
                    that 3 and 2 are losing moves, but once it evaluates 4, it
                    uses the beta value for 4 in the search, and this prevents
                    the moves 5, 0, and 6 from being evaluated fully, which I
                    want to happen. I'm not sure how much this will effect
                    runtime for the general case, and I haven't thought of
                    another fix for this yet.

                    UPDATE: after running the code with (2, 3), (3, 3), (4, 3),
                    (4, 3), (3, 2), (4, ), the AI's only move is 4, otherwise
                    the player will win. When using -winValue and winValue, the
                    AI realizes this once it finishes searching at depth 2. When
                    using alpha and beta, it searches as long as it can to evaluate
                    the position 4, but it also returns beta for positions it
                    hasn't fully evaluated yet (1, 5, 0 ,6). I have reverted
                    BACK to using alpha and beta since even though it yields
                    imperfect results in situations like this, it can search
                    much farther than with -winValue and winValue. Results:
                    14 13 14 13 16 11 vs. 12 13 13 12 13 3 (finds win at depth
                                                            11, finds loss at
                                                            depth 3)
                */
                makeMove(pb, column);
                float temp = minimax(pb, depth - 1, alpha, beta, t0);
                //float temp = minimax(pb, depth - 1, -winValue, winValue, t0);
                undoMove(pb);

                //printf("\n%d: %f", column, temp);

                //found a winning move for self
                if(temp / winValue == (pb->counter & 1 ? -1 : 1)){
                    bestMoveIndex = column;
                    //printf("bestMoveIndex: %d\n", bestMoveIndex);
                    timeToStop = true;
                    break;
                }
                //printf("\n%lf", fabs(temp / winValue));

                //found a winning move for opponent
                if(fabs(temp / winValue) == 1){
                    solvedColumns[column] = 1;
                    numUnsolvedMoves--;
                    //printf("\ncolumn %d: %f", column, temp);
                    continue;
                }
                if(!(pb->counter & 1)){
                    if(temp > tempBestMoveValue){
                        tempBestMoveIndex = column;
                        tempBestMoveValue = temp;
                        alpha = temp;
                    }
                }
                else{
                    if(temp < tempBestMoveValue){
                        tempBestMoveIndex = column;
                        tempBestMoveValue = temp;
                        beta = temp;
                    }
                }
                if(alpha > beta){
                    timeToStop = true;
                    break;
                }
            }
            else{
                //printf("\n%d was skipped", moves[i]);
            }
        }
        if(i == numMoves){
            bestMoveIndex = tempBestMoveIndex;
            bestMoveValue = tempBestMoveValue;
        }
        if(timeToStop)
            break;

    }

    free(moves);
    makeMove(pb, bestMoveIndex);
    printf("\nterminated while searching depth: %d", depth);

    //printf("\n\ntime: %lld seconds", time(NULL) - t0);
    return bestMoveIndex;
}


/**
    return value of a given board state after performing minimax with param depth
**/
static float minimax(Board* pb, short depth, float alpha, float beta, time_t t0){

    if(depth <= 0 || time(NULL) - t0 >= timeToThink || winner(pb->bb[0]) || winner(pb->bb[1])){
        //printBoard(pb);
        //printf("\n%f\n", staticEvaluation(pb));
        return staticEvaluation(pb);
    }

    short* moves = malloc(col * sizeof(short));
    short numMoves = listMoves(pb, moves);
    //moves = realloc(moves, numMoves * sizeof(short));

    float guarantee = pb->counter & 1 ? winValue : -winValue;
    for(int i = 0; i < numMoves; i++){
        makeMove(pb, moves[i]);
        float nextEval = minimax(pb, depth - 1, alpha, beta, t0);
        undoMove(pb);
        guarantee = pb->counter & 1 ? min(guarantee, nextEval) : max(guarantee, nextEval);
        if(!(pb->counter & 1))
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
/*
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
*/

void createTranspositionTable(TranspositionTable* table, int n_elems){
    table->hmap = malloc(sizeof(HashMap));
    createHashMap(table->hmap, n_elems);
    table->z = malloc(sizeof(ZobristHash));
    initializeZobristHash(table->z, 7, 6);
}

void destroyTranspositionTable(TranspositionTable* table){
    destroyZobristHash(table->z);
    destroyHashMap(table->hmap);
}

static float staticEvaluation(Board* pb){
    if(winner(pb->bb[0])){
        return winValue;
    } else if (winner(pb->bb[1])){
        return -winValue;
    }

    /*
    float score = 0;
    for(int c = 0; c < col; c++){
        for(int r = pb->top[c] + 1; r < row; r++){
            //score += pb->board[r][c] / ((min(abs(r - 3), abs(r - 2)) + 1) * (abs(c - 3) + 1));
            score += pb->board[r][c] * winsPerSlot[r][c];
        }
    }
    */

    float score = 0;
    for(int c = 0; c < col * col; c += col){
        for(int r = 0; r < pb->top[c / col] - c; r++){
            score += (((pb->bb[0] >> (r + c)) & 1) - ((pb->bb[1] >> (r + c)) & 1)) * winsPerSlot[r][c / col];
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
