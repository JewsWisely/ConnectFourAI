/*
#ifndef HASHMAP_H_INCLUDED
#define HASHMAP_H_INCLUDED
#include "Board.h"
#define Key long long int

typedef struct HashValue{
    float depth;
    float alpha;
    float beta;
} HashValue;

typedef struct HashEntry{
    Key key;
    HashValue value;
} HashEntry;

typedef struct HashMap{
    int maxSize;
    int currSize;
    long long int* zobristValues;
    HashEntry* entries;
} HashMap;

void createHashMap(HashMap* hmap, int initKB, int maxKB);

void destroyHashMap(HashMap* hmap);

Key createKey(HashMap* hmap, Board* pb);

HashValue createValue(float depth, float alpha, float beta);

HashEntry createEntry(Key key, HashValue value);

#endif // HASHMAP_H_INCLUDED
*/
