#ifndef Q5_h

#define Q5_h
#include "common.h"
#include "Q2.h"

BYTE lastByteFromFile(FILE* file);
void updateByte(FILE* file, BYTE prevByte, BYTE mask);
BYTE maskMaker(BYTE posConvertion, int countOfZeros);
BYTE posToByte(chessPos position);
void saveToBinFile(char* file_name, chessPosList* pos_list);
short findListSize(chessPosList* pos_list);

#endif // !Q5_h