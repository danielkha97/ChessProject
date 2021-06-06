#ifndef Q1_h

#define Q1_h


#include "common.h"

chessPosArray*** validKnightMoves();
chessPosArray*** boardCreation();
chessPosArray* cellStepsCheck(char row, char col, chessPosArray* posArray);
void freeMat(chessPosArray*** board);

#endif // !Q1_h

