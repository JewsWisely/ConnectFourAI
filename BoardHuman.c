#include "BoardIO.h"

static void printColumnNumbers();

/**
    get column from user, drop piece in column
**/
short makeHumanMove(Board* pb){
    short column;
    do{
        column = 9;
        printf("\ndrop piece in column: ");
        scanf(" %c", &column);
        column -= '0';
    } while(!boundsCheck(column));

    putPiece(pb, column);
    return column;
}

/**
    print the board state
**/
void printBoard(Board* pb){

    /**print the board**/
    printf("\n\n\n");
    for(int i = 0; i < row; i++){
        printf("\n");
        for(int j = 0; j < col; j++){
            printf("[%c]", pb->board[i][j] == -1 ? 'X' : pb->board[i][j] == 1 ? 'O' : ' ');
        }
    }

    /**print the column numbers**/

    printColumnNumbers();
    printf("\nplayer: %d", pb->player);
}

void printBoardExtra(Board* pb){
    printBoard(pb);
    printf("\ntop:\n");
    for(int i = 0; i < col; i++){
        printf(" %d ", pb->top[i]);
    }
}

static void printColumnNumbers(){
    printf("\n");
    for(int i = 0; i < col; i++)
        printf("% d ", i);
}
