#include "Q4.h"

chessPosList* findKnightPathCoveringAllBoard(pathTree* path_tree)//finds a route covering the whole board
{
	bool found = false;
	int count = 1;

	chessPosList* moves = makeEmptyChessPosList();

	treeNode* tempNode = (treeNode*)malloc(sizeof(treeNode));
	memAllocTest(tempNode);

	tempNode = path_tree->root;

	recFindKnightPathCoveringAllBoard(tempNode, count, &found, moves);//recurssive function call

	if (found)
		return moves;
	else
		return NULL;
}

void recFindKnightPathCoveringAllBoard(treeNode* node, int count, bool* foundRoute, chessPosList* moves)//the recursive function part of findKnightPathCoveringAllBoard
{

	if (ROWS * COLS == count || *foundRoute) //if reached to a route as desired
		*foundRoute = true;	

	else if (node == NULL)//if reached to an end of a spedific route before counting ROWS*COLS cells
		return;

	else
	{

		while (node->next_possible_positions != NULL && *foundRoute == false)
		{
			recFindKnightPathCoveringAllBoard(node->next_possible_positions->node, ++count , foundRoute, moves);//rec call
			--count;
			node->next_possible_positions = node->next_possible_positions->next;
		}
	}
	if (*foundRoute)
		addToStartOfChessPosList(moves, createNewChessPosCell(node->position, NULL));

}


