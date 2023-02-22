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

    int tableSize = 1 << 20;
    TranspositionTable* table = malloc(sizeof(TranspositionTable));
    createTranspositionTable(table, tableSize);

    short column;
    do{
        if(player)
            column = makeHumanMove(pb);
            //column = makeAIMove(pb, table);
        else
            column = makeAIMove(pb, table);
        player = !player;
        printf("\nchosen column: %d", column);
        printBoard(pb);

    }while(!winner(pb->bb[0]) && !winner(pb->bb[1]) && pb->counter < 42);

    if(winner(pb->bb[0])){
        printf("\nPlayer 1 wins!");
    }
    else if(winner(pb->bb[1])){
        printf("\nPlayer 2 wins!");
    }
    else{
        printf("\nTie game!");
    }

    destroyTranspositionTable(table);

}
