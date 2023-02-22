#include <stdio.h>
#include <stdlib.h>
#include "Board.h"
#include "BoardHuman.h"
#include "BoardAI.h"


void play(Board* pb);

int main()
{
    Board* pb = malloc(sizeof(Board));
    createBoard(pb);
    play(pb);
    destroyBoard(pb);
    free(pb);

    return 0;
}

void play(Board* pb){

    printBoard(pb);

    bool player = true;

    short column;
    do{
        if(player)
            column = makeHumanMove(pb);
        else
            column = makeAIMove(pb);
        player = !player;
        printf("\nchosen column: %d", column);
        printBoard(pb);

    }while(!winner(pb, column) && !isTied(pb));

}
