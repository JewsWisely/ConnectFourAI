
#include "Board.h"

/**
    construct a dynamically allocated Board
**/
void createBoard(Board* pb){

    /**dynamically allocate memory for board and top**/

    //board must have the capacity for 6 rows, each row being a short*
    //top must have the capacity of 7 shorts, 1 for each column
    pb->board = malloc(row * sizeof(short*));
    pb->top = malloc(col * sizeof(short));

    /**initialize board and top**/

    //set each row of board to a new chunk of memory filled with 7 0s
    //set the first 6 values of top to 5
    for(int i = 0; i < row; i++){
        *(pb->board + i) = calloc(col, sizeof(short));
        *(pb->top + i) = row - 1;
    }

    //set the 7th value to 5
    *(pb->top + row) = row - 1;

}

/**
    deallocate all memory associated with pb
**/
void destroyBoard(Board* pb){

    /**free all elements of pb**/

    //free each row of the board
    for(int i = 0; i < row; i++){
        free(*(pb->board + i));

    }

    //free the board and top arrays
    free(pb->board);
    free(pb->top);

}

/**
    put a piece on the board
**/
bool put(Board* pb, short index, short player){
    //note: error-check the bounds of index elsewhere

    /**update board and top**/

    //set the value at the top of the column to the value of player
    //increment top[index] for that column
    if(pb->top[index] > 0){
        pb->board[index][pb->top[index]++] = player;
        return true;
    }

    //no room left in the requested column
    return false;
}

/**
    print the board state
**/
void printBoard(Board* pb){
    for(int i = 0; i < row; i++){
        printf("\n|");
        for(int j = 0; j < col; j++){
            printf("%+d|", pb->board[i][j]);
        }
    }
}
