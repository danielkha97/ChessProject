#include "Q3.h"


pathTree findAllPossibleKnightPaths(chessPos* startingPosition) /*this function calls the recursive function*/
{
	pathTree tr; /*the tree we need to build*/
	tr.root = NULL;
	chessPosArray*** validMoves = validKnightMoves();

	bool isValidPath[ROWS][COLS] = { false }; /*bool array that saves the path to a specific part of the board*/
	tr.root = findAllPossibleKnightPathsRec(startingPosition, validMoves, isValidPath); /*the recursive function that builds the tree*/
	return tr;
}

treeNode* findAllPossibleKnightPathsRec(chessPos startingPosition, chessPosArray*** validMoves, bool isValidPath[][COLS])
/*this is the recursive function that finds all the possible paths*/
{
	/*variables*/
	int x, y;
	int i;
	treeNode* res = createNewTreeNode(startingPosition, NULL);
	treeNode* currNode;
	treeNodeListCell* nextCell = NULL;
	treeNodeListCell* currCell = NULL;

	if (endOfPathCheck(startingPosition, validMoves, isValidPath)) /*checks if there is no place to continue to*/
		return res;

	getCoordinates(startingPosition, &x, &y);
	isValidPath[x][y] = true; /*using bool matrix to check if a cell is "used" before*/

	for (i = 0; i < validMoves[x][y]->size; i++)
	{
		if (possiblePossCheck(validMoves[x][y]->positions[i], isValidPath))
		{
			currNode = findAllPossibleKnightPathsRec(validMoves[x][y]->positions[i], validMoves, isValidPath);
			currCell = createNewTreeNodeListCell(currNode, nextCell);
			nextCell = currCell;
		}
	}

	res->next_possible_positions = currCell;
	isValidPath[x][y] = false;
	return res;
}

treeNode* createNewTreeNode(chessPos position, treeNodeListCell* next_possible_positions)
/*this function creates new tree node*/
{
	treeNode* res = (treeNode*)malloc(sizeof(treeNode));
	memAllocTest(res);

	(res->position)[0] = position[0];
	(res->position)[1] = position[1];
	res->next_possible_positions = next_possible_positions;
	return res;
}

treeNodeListCell* createNewTreeNodeListCell(treeNode* node, treeNodeListCell* next)
/*this function create new list cell*/
{
	treeNodeListCell* res = (treeNodeListCell*)malloc(sizeof(treeNodeListCell));
	memAllocTest(res);

	res->node = node;
	res->next = next;
	return res;
}

bool endOfPathCheck(chessPos position, chessPosArray*** validMoves, bool isValidPath[][COLS])
/*this function checks if we arrived to the end of the path*/
{
	int x, y, i, currX, currY;

	getCoordinates(position, &x, &y);

	for (i = 0; i < validMoves[x][y]->size; i++)
	{
		getCoordinates(validMoves[x][y]->positions[i], &currX, &currY);

		if (isValidPath[currX][currY] == false)
			return false;
	}

	return true;
}

bool possiblePossCheck(chessPos position, bool isValidPath[][COLS])
{
	/*this function checks if we "used" particular cell in the path before*/
	int x, y;
	getCoordinates(position, &x, &y);
	return !isValidPath[x][y];
}

void freeTree(pathTree tree)
{
	freeTreeRec(tree.root);
}

void freeTreeRec(treeNode* root)
{
	if (root == NULL)
		return;

	treeNodeListCell* curr = root->next_possible_positions;

	while (curr != NULL)
	{
		freeTreeRec(curr->node);
		curr = curr->next;
	}

	free(root);
}