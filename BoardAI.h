#ifndef BOARDAI_H_INCLUDED
#define BOARDAI_H_INCLUDED
#include "Board.h"
#include "HashMap.h"
#include "ZobristHash.h"

typedef struct TranspositionTable{
    HashMap* hmap;
    ZobristHash* z;
} TranspositionTable;

typedef struct HashValue{
    int depth;
    float alpha;
    float beta;
    float evaluation;
}HashValue;

short makeAIMove(Board* pb, TranspositionTable* table);

void createTranspositionTable(TranspositionTable* table, int n_elems);

void destroyTranspositionTable(TranspositionTable* table);

#endif // BOARDAI_H_INCLUDED
