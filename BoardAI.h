#ifndef BOARDAI_H_INCLUDED
#define BOARDAI_H_INCLUDED
#include "Board.h"
#include "HashMap.h"
#include "ZobristHash.h"

typedef struct TranspositionTable{
    HashMap* hmap;
    ZobristHash* z;
} TranspositionTable;

typedef enum HashType{
    lower,
    upper,
    exact
} HashType;

typedef struct HashValue{
    int depth;
    HashType type;
    float evaluation;
}HashValue;

short makeAIMove(Board* pb, TranspositionTable* table, short use_table);

void createTranspositionTable(TranspositionTable* table, int n_elems);

void destroyTranspositionTable(TranspositionTable* table);

#endif // BOARDAI_H_INCLUDED
