#ifndef HASHMAP_H_INCLUDED
#define HASHMAP_H_INCLUDED
#include "Board.h"
#define Key int


typedef struct HashValue{
    float alpha;
    float beta;
} HashValue;

typedef struct HashMap{
    int maxSize;
    int currSize;
    int zobristValues[row][col][3];
    Key* keys;
    HashValue* values;
} HashMap;

void createHashMap(HashMap* hmap, int initKB, int maxKB);

void destroyHashMap(HashMap* hmap);

Key createKey(Board* pb);




#endif // HASHMAP_H_INCLUDED
