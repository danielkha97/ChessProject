#include "Q4.h"

chessPosList* findKnightPathCoveringAllBoard(pathTree* path_tree)
{
	bool found = false;
	int count = 1;
	chessPosList* moves = makeEmptyChessPosList();
	memAllocTest(moves);
	treeNode* tempNode = (treeNode*)malloc(sizeof(treeNode));
	tempNode = path_tree->root;

	recFindKnightPathCoveringAllBoard(tempNode, count, &found, moves);

	if (found)
		return moves;
	else
		return NULL;
}

void recFindKnightPathCoveringAllBoard(treeNode* node, int count, bool* foundRoute, chessPosList* moves)
{

	if (ROWS * COLS == count)
	{
		*foundRoute = true;
		addToListTail(moves, node->position[0], node->position[1]);
		return;
	}

	else if (node == NULL)
		return;

	else
	{

		while (node->next_possible_positions != NULL && *foundRoute == false)
		{
			recFindKnightPathCoveringAllBoard(node->next_possible_positions->node, count + 1, foundRoute, moves);
			node = node->next_possible_positions->node;
		}
	}
	if (*foundRoute == true)
		addToStartOfChessPosList(moves, createNewChessPosCell(node->position, NULL));

}


