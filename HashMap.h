#ifndef HASHMAP_H_INCLUDED
#define HASHMAP_H_INCLUDED
#define Key long long int
#include <stdlib.h>
#include <stdio.h>

typedef struct HashEntry{
    Key key;
    void* value;
} HashEntry;

typedef struct HashMap{
    int n_elems;
    int size;
    HashEntry** entries;
}HashMap;

void printEntry(HashEntry* entry);

void createHashMap(HashMap* hmap, int n_elems);

float hashAdd(HashMap* hmap, HashEntry* entry);

void* hashGet(HashMap* hmap, Key key);

void destroyHashMap(HashMap* hmap);

#endif // HASHMAP_H_INCLUDED
