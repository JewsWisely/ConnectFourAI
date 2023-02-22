#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED
#include <stdlib.h>
#include <stdbool.h>
#define row 6
#define col 7

/*
typedef enum{
    black = -1, red = 1
} Player;
*/

/*
typedef struct _Board{
    short** board;
    short* top;
    Player player;
} Board;
*/

typedef struct _Board{
    long long int* bb;
    short* top;
    short counter;
    short* history;
} Board;


void createBoard(Board* pb);

void destroyBoard(Board* pb);

void makeMove(Board* pb, short index);

void undoMove(Board* pb);

short listMoves(Board* pb, short* moves);

//bool winner(Board* pb, short index);

bool winner(long long int bb);

bool boundsCheck(short index);

bool isTied(Board* pb);

#endif // BOARD_H_INCLUDED
