#ifndef Q3_h
#define Q3_h

#include "common.h"
#include "Q1.h"

pathTree findAllPossibleKnightPaths(chessPos* startingPosition);
treeNode* findAllPossibleKnightPathsRec(chessPos startingPosition, chessPosArray*** validMoves, bool isValidPath[][COLS]);
treeNode* createNewTreeNode(chessPos position, treeNodeListCell* next_possible_positions);
treeNodeListCell* createNewTreeNodeListCell(treeNode* node, treeNodeListCell* next);
bool endOfPathCheck(chessPos position, chessPosArray*** vkm, bool isValidPath[][COLS]);
bool possiblePossCheck(chessPos position, bool trackingArray[][COLS]);
void freeTree(pathTree tree);
void freeTreeRec(treeNode* root);
#endif // !Q3_h