#include "HashMap.h"
#include <stdlib.h>

/*
void createHashMap(HashMap* hmap, int initKB, int maxKB){
    hmap->zobristValues =  new int[row][col][3]
                           {{{0}, {0}, {0}, {0}, {0}, {0}},
                            {{0}, {0}, {0}, {0}, {0}, {0}},
                            {{0}, {0}, {0}, {0}, {0}, {0}},
                            {{0}, {0}, {0}, {0}, {0}, {0}},
                            {{0}, {0}, {0}, {0}, {0}, {0}},
                            {{0}, {0}, {0}, {0}, {0}, {0}},
                            {{0}, {0}, {0}, {0}, {0}, {0}}};
    srand(time(0)));
    for(int r = 0; r < row; r++){
        for(int c = 0; c < col; c++){
            for(int d = 0; d < 3; d++){
                hmap->zobristValues[r][c][d] = rand();
            }
        }
    }

    hmap->maxSize = 0b10000000000 * maxKB / sizeof(Key);
    hmap->currSize = 0b10000000000 * initKB / sizeof(Key);
    hmap->keys = malloc(currSize * sizeof(Key));
    hmap->values = malloc(currSize * sizeof(HashValue));
}

void destroyHashMap(HashMap* hmap){

    free(hmap->keys);
    free(hmap->values);
    hmap->currSize = 0;
    hmap->maxSize = 0;


}

Key createKey(HashMap* hmap, Board* pb){
    Key key = 0;
    for(int c = 0; c < col; c++){
        for(int r = pb->top[c] + 1; r < row; r++){
            if(board[r][c] == black)
                key ^= hmap->zobristValues[r][c][0];
            else if(board[r][c] == red)
                key ^= hmap->zobristValues[r][c][2];
            else
                key ^= hmap->zobristValues[r][c][1];
        }
    }
    return key;
}

HashValue createHashValue(){

}
*/
