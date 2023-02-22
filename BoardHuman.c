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
    } while(!boundsCheck(column) || pb->top[column] == column * 7 + 6);

    makeMove(pb, column);
    return column;
}

/**
    print the board state
**/
void printBoard(Board* pb){

    /**print the board**/
    printf("\n\n\n");
    /*
    for(int i = 0; i < row; i++){
        printf("\n");
        for(int j = 0; j < col; j++){
            printf("[%c]", pb->board[i][j] == -1 ? 'X' : pb->board[i][j] == 1 ? 'O' : ' ');
        }
    }
    */

    for(int i = row - 1; i >= 0; i--){
        printf("\n");
        for(int j = 0; j < col * col; j += col){
            printf("[%c]", (pb->bb[0] >> (i + j)) & 1 ? 'O' : (pb->bb[1] >> (i + j)) & 1 ? 'X' : ' ');
        }
    }

    /**print the column numbers**/

    printColumnNumbers();
    //printf("\nplayer: %d", pb->player);
    printf("\nplayer: %c", pb->counter & 1 ? 'X' : 'O');
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
