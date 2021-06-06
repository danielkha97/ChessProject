#ifndef Q2_h

#define Q2_h

#include "common.h"



void getCoordinates(chessPos position, int* x, int* y);
chessPos* setCoordinates(int x, int y);
chessPosCell* createNewChessPosCell(chessPos position, chessPosCell* next);
void removeChessPosCell(chessPosCell* prev);
void display(chessPosList* lst);
void printBoard(chessPosList* lst);
chessPosList* makeEmptyChessPosList();
bool isEmptyChessPosList(chessPosList list);
void addToStartOfChessPosList(chessPosList* list, chessPosCell* cell);
void freeChessPosList(chessPosList* list);
void addToListTail(chessPosList* list, int x, int y);

#endif // !Q2_h