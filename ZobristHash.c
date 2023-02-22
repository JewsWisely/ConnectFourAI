#include "ZobristHash.h"
#include <stdlib.h>

static Key randomNumber();

void initializeZobristHash(ZobristHash* zhash, short dim1, short dim2){

    zhash->dim1 = dim1;
    zhash->dim2 = dim2;
    zhash->dim3 = 3;

    srand(time(0));
    zhash->zobristValues = malloc(dim1 * sizeof(Key**));
    for(int i = 0; i < dim1; i++){
        zhash->zobristValues[i] = malloc(dim2 * sizeof(Key*));
        for(int k = 0; k < dim2; k++){
            zhash->zobristValues[i][k] = malloc(zhash->dim3 * sizeof(Key));
            for(int m = 0; m < zhash->dim3; m++){
                zhash->zobristValues[i][k][m] = randomNumber();
            }
        }
    }

}

//this is implemented specifically for connect four, with only 2 players and therefore only 2 bitboards
Key zhash(ZobristHash* zhash, Key* bitBoards, Key currentHash, short newMoveRow, short newMoveColumn, short zobristIndex){

    Key key = 0;
    if(bitBoards != NULL){
        for(int r = 0; r < zhash->dim1; r++){
            for(int c = 0; c < zhash->dim2; c++){
                if((bitBoards[0] >> (r + c)) & 1)
                    key ^= zhash->zobristValues[r][c][0];
                else if((bitBoards[1] >> (r + c)) & 1)
                    key ^= zhash->zobristValues[r][c][1];
                else
                    key ^= zhash->zobristValues[r][c][2];
            }
        }
    }
    else{
        key = currentHash ^ zhash->zobristValues[newMoveRow][newMoveColumn][zobristIndex];
    }
    return key;

}

//takes current hash value and last move info and xors the last move out of the hash
Key undoZHash(ZobristHash* zhash, Key currentHash, short lastMoveRow, short lastMoveColumn, short zobristIndex){

    return currentHash ^ zhash->zobristValues[lastMoveRow][lastMoveColumn][zobristIndex];

}

void destroyZobristHash(ZobristHash* zhash){

    //printf("\ndestroying zobrist hash...");
    for(int i = 0; i < zhash->dim1; i++){
        for(int k = 0; k < zhash->dim2; k++){
            free(zhash->zobristValues[i][k]);
        }
        free(zhash->zobristValues[i]);
    }
    free(zhash->zobristValues);
    //printf(" Success!\n");
}



//return a random sequence of 64 bits
Key randomNumber(){

    return ((((Key)(rand() - RAND_MAX)) << 32) + rand() - RAND_MAX)/* | 0b0000001000000100000010000001000000100000010000001000000000000000*/;

}
