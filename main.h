#ifndef main_h
#define main_h

#include "common.h"
#include "Q1.h"
#include "Q2.h"
#include "Q3.h"
#include "Q4.h"
#include "Q5.h"
#include "Q6.h"

#define MAX_SIZE 25

/*options prototypes*/

chessPos* option1();
//bool isValidInput(chessPos position);
pathTree option2(chessPos* startingPosition);
chessPosList* option3(chessPos* startingPosition, pathTree tr);
void option4(chessPos* startingPosition, pathTree tr, chessPosList* lst);
void option5();

#endif
