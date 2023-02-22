#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED
#include <stdlib.h>
#include <stdbool.h>
#define row 6
#define col 7

typedef enum{
    black = -1, red = 1
} Player;

typedef struct _Board{
    short** board;
    short* top;
    Player player;
} Board;

void createBoard(Board* pb);

void destroyBoard(Board* pb);

bool putPiece(Board* pb, short index);

void removePiece(Board* pb, short index);

bool winner(Board* pb, short index);

bool boundsCheck(short index);

bool isTied(Board* pb);

#endif // BOARD_H_INCLUDED
