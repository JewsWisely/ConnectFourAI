#include "BoardIO.h"

static void printColumnNumbers();

/**
    get column from user, drop piece in column
**/
short makeHumanMove(Board* pb){
    short column = 9;
    do{
        printf("\n%hd drop piece in column: ", column);
        scanf("%hd", &column);
    } while(!boundsCheck(column));

    putPiece(pb, column);
    return column;
}

/**
    print the board state
**/
void printBoard(Board* pb){

    /**print the board**/

    for(int i = 0; i < row; i++){
        printf("\n|");
        for(int j = 0; j < col; j++){
            printf("%+d|", pb->board[i][j]);
        }
    }

    /**print the column numbers**/

    printColumnNumbers();
}

static void printColumnNumbers(){
    printf("\n ");
    for(int i = 0; i < col; i++)
        printf("% d ", i);
}
