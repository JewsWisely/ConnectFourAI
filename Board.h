#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define row 6
#define col 7

typedef struct _Board{
    short** board;
    short* top;
} Board;

enum Player{black = -1, red = 1};

void createBoard(Board* pb);

void destroyBoard(Board* pb);

bool put(Board* pb, short index, short player);

void printBoard(Board* pb);

#endif // BOARD_H_INCLUDED
