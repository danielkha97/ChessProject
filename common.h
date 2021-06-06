#ifndef common_h
#define common_h


#define _CRT_SECURE_NO_WARNINGS 
#define ROWS 5
#define COLS 5
#define MaxValidKnightMoves 8


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef char chessPos[2]; /*each position is represented by X,Y cords of the board*/

typedef struct _chessPosArray
{                               /*struct that describes the tools positions over the board at a given moment*/
	unsigned int size;
	chessPos* positions;        /*pointer to an array of positions*/
} chessPosArray;

typedef unsigned char BYTE;

typedef struct chessPosCell;

typedef struct _chessPosCell {
	chessPos position;
	struct _chessPosCell* next;
} chessPosCell;

typedef struct _chessPosList {
	chessPosCell* head;
	chessPosCell* tail;
} chessPosList;

struct _treeNodeListCell;

typedef struct _treeNode {
	chessPos position;
	struct _treeNodeListCell* next_possible_positions;
} treeNode;

typedef struct _treeNodeListCell {
	treeNode* node;
	struct _treeNodeListCell* next;
} treeNodeListCell;

typedef struct _pathTree {
	treeNode* root;
} pathTree;




void getCoordinates(chessPos position, int* x, int* y);
void memAllocTest(void* p);
void fileOpenCheck(FILE* file);

#endif /* common_h */
