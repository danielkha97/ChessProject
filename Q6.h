#ifndef  Q6_h
#define Q6_h

#include "common.h"
#include "Q5.h"
#include "Q2.h"


int checkAndDisplayPathFromFile(char* file_name);
int validCoord(int x, int y);
void addChessPosToEndList(chessPosList* list, chessPos cp);
int deleteDuplicateAndCount(chessPosList* lst);
bool isNextValid(chessPos curr, chessPos next);
bool isListValid(chessPosList list);
chessPosArray* validMovesByPosition(int x, int y);
void addToEndOfChessPosList(chessPosList* list, chessPosCell* cell);

#endif // ! Q6_h