#include <stdio.h>
#include <stdlib.h>
#include "Board.h"

int main()
{
    Board* pb = malloc(sizeof(Board*));
    createBoard(pb);
    printBoard(pb);
    destroyBoard(pb);
    free(pb);

    return 0;
}
