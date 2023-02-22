#ifndef ZOBRISTHASH_H_INCLUDED
#define ZOBRISTHASH_H_INCLUDED
#define Key long long int

typedef struct ZobristHash{
    Key*** zobristValues;
    short dim1, dim2, dim3;
}ZobristHash;

void initializeZobristHash(ZobristHash* zhash, short dim1, short dim2);

Key zhash(ZobristHash* zhash, Key* bitBoards, Key currentHash, short newMoveRow, short newMoveColumn, short zobristIndex);

Key undoZHash(ZobristHash* zhash, Key currentHash, short lastMoveRow, short lastMoveColumn, short zobristIndex);

void destroyZobristHash(ZobristHash* zhash);

#endif // ZOBRISTHASH_H_INCLUDED
