/*
#include "HashMap.h"
#include <stdlib.h>
#include <stdio.h>


void createHashMap(HashMap* hmap, int initKB, int maxKB){
    hmap->zobristValues = malloc(row * col * 3 * sizeof(long long int));
    srand(time(0));
    for(int r = 0; r < row; r++){
        for(int c = 0; c < col; c++){
            for(int d = 0; d < 2; d++){
                hmap->zobristValues[d + c * 2 + r * 2 * col] = ((long long int)rand() << 31 & rand()) | 0b0000001000000100000010000001000000100000010000001000000000000000;
                for(int i = 0; i < 64; i++){
                    printf("%d", hmap->zobristValues[d + c * 2 + r * 2 * col] >> i & 1);
                }
            }
        }
    }

    hmap->maxSize = 1024 * maxKB / sizeof(Key);
    hmap->currSize = 1024 * initKB / sizeof(Key);
    hmap->entries = malloc(hmap->currSize * sizeof(HashEntry));
}

void destroyHashMap(HashMap* hmap){

    free(hmap->zobristValues);
    free(hmap->values);
    hmap->currSize = 0;
    hmap->maxSize = 0;

}

Key createKey(HashMap* hmap, Board* pb){
    Key key = 0;
    for(int c = 0; c < col * col; c += col){
        for(int r = 0; r < pb->top[c / col] - c; r++){
            if(pb->bb[0] >> (r + c) & 1)
                key ^= hmap->zobristValues[c + r];
            else if(pb->bb[1] >> (r + c) & 1)
                key ^= hmap->zobristValues[c + r + 1];
        }
    }
    return key;
}

HashValue createValue(float depth, float alpha, float beta){
    HashValue value = {depth, alpha, beta};
    return value;
}

HashEntry createEntry(Key key, HashValue value){
    HashEntry entry = {key, value};
    return entry;
}

void put(HashMap* hmap, HashEntry entry){

    int position = entry.key % hmap->currSize;
    if(hmap->entries[position] != NULL){

    }

}


void get(Key key){

}
*/
