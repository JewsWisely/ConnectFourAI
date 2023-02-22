
#include "Board.h"

//static void updateTurn(Board* pb);

//static int max(int x, int y);

//static int min(int x, int y);

/**
    construct a dynamically allocated Board
**/
void createBoard(Board* pb){

    /**dynamically allocate memory for board and top**/

    /*
    //board must have the capacity for 6 rows, each row being a short*
    //top must have the capacity of 7 shorts, 1 for each column
    pb->board = malloc(row * sizeof(short*));
    pb->top = malloc(col * sizeof(short));
    */

    //now using bitboards to represent board states
    pb->bb = (long long int*)calloc(2, sizeof(long long int));
    pb->top = (short*)malloc(col * sizeof(short));
    pb->counter = 0;
    pb->history = (short*)calloc(row * col, sizeof(short));

    /**initialize board and top**/

    //set each row of board to a new chunk of memory filled with 7 0s
    //set the first 6 values of top to 5

    /*
    for(int i = 0; i < row; i++){
        *(pb->board + i) = calloc(col, sizeof(short));
        *(pb->top + i) = row - 1;
    }
    */


    //set the values of top to the bit-indeces of where
    //the next piece should be places per column
    for(int i = 0; i < col; i++){
        *(pb->top + i) = i * 7;
    }

    //set the 7th value to 5
    //*(pb->top + col - 1) = row - 1;

    //set player to red
    //pb->player = red;
}

/**
    deallocate all memory associated with pb
**/
void destroyBoard(Board* pb){

    /**free all elements of pb**/

    //free each row of the board
    /*
    for(int i = 0; i < row; i++){
        free(*(pb->board + i));

    }*/

    //free the board and top arrays
    free(pb->bb);
    free(pb->top);
    free(pb->history);

    //set player to 0; neither red nor black
    //pb->player = 0;
}

/**
    put a piece on the board
**/
void makeMove(Board* pb, short index){
    //note: error-check the bounds of index elsewhere

    /**update board, top, and player**/

    //set the value at the top of the column to the value of player
    //increment top[index] for that column
    /*
    if(pb->top[index] >= 0){
        pb->board[pb->top[index]--][index] = pb->player;
        updateTurn(pb);
        return true;
    }
    */

    long long int move = 1LL << pb->top[index]++;
    pb->bb[pb->counter & 1] ^= move;
    pb->history[pb->counter++] = index;

    //no room left in the requested column
    //return true;
}

/**
    remove a piece from the board
**/
void undoMove(Board* pb){
    //note: error-check the bounds of index elsewhere

    /**update board, top, and player**/

    /*
    if(pb->top[index] + 1 < row){
        pb->board[++pb->top[index]][index] = 0;
    }
    updateTurn(pb);
    */

    short index = pb->history[--pb->counter];
    long long int move = 1LL << --pb->top[index];
    pb->bb[pb->counter & 1] ^= move;

}

/**
    return dynamically-allocated array of valid moves
**/
short listMoves(Board* pb, short* moves){

    int columns[col] = {3, 2, 4, 1, 5, 0, 6};
    short numMoves = 0;
    for(int c = 0; c < col; c++){
        if(pb->top[columns[c]] != columns[c] * 7 + 6)
            moves[numMoves++] = columns[c];
    }
    return numMoves;
}

/**
    switch the player variable
**/
/*
static void updateTurn(Board* pb){
    pb->player *= -1;
}*/

bool isTied(Board* pb){
    return pb->counter == row * col && !winner(pb->bb[0]) && !winner(pb->bb[1]);
}

/**
    return whether there is a win on the board
**/

bool winner(long long int bb){

    short directions[4] = {1, row, col, col + 1};
    for(int i = 0; i < 4; i++)
        if(bb & (bb >> directions[i]) & (bb >> 2 * directions[i]) & (bb >> 3 * directions[i]))
            return true;
    return false;

}

/*
bool winner(Board* pb, short column){

    int rval = pb->top[column] + 1;
    Player winner = pb->board[rval][column];

    //horizontal
    int count = 0;
    for(int c = 0; c < col; c++){
        if((count = pb->board[rval][c] == winner ? count + 1 : 0) == 4)
            return true;
    }

    //main diagonal
    int r = max(0, rval - column), c = column - rval + r;
    count = 0;
    while(r < row && c < col){
        if((count = pb->board[r++][c++] == winner ? count + 1 : 0) == 4)
            return true;
    }

    //other diagonal
    r = min(row - 1, rval + column), c = column + rval - r;
    count = 0;
    while(r >= 0 && c < col){
        if((count = pb->board[r--][c++] == winner ? count + 1 : 0) == 4)
            return true;
    }

    //vertical
    if(rval <= 2
       && pb->board[rval][column] == pb->board[rval + 1][column]
       && pb->board[rval][column] == pb->board[rval + 2][column]
       && pb->board[rval][column] == pb->board[rval + 3][column]
    ) return true;

    return false;
}*/

/**
    return whether index is within the bounds of the board
**/

bool boundsCheck(short index){
    return index >= 0 && index < col;
}

/**
    return the maximum of two integers
**/
/*
static int max(int x, int y){
    return (x > y) ? x : y;
}
*/
/**
    return the minimum of two integers
**/
/*
static int min(int x, int y){
    return (x < y) ? x : y;
}
*/
