#ifndef Q4_h
#define Q4_h


#include "common.h"
#include "Q3.h"
#include "Q2.h"

chessPosList* findKnightPathCoveringAllBoard(pathTree* path_tree);
void recFindKnightPathCoveringAllBoard(treeNode* node, int count, bool* foundRoute);

#endif // !Q4_h