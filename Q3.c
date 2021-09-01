#include "Q3.h"


pathTree findAllPossibleKnightPaths(chessPos* startingPosition) /*this function calls the recursive function*/
{
	pathTree tr; /*the tree will be built*/
	tr.root = NULL;
	chessPosArray*** validMoves = validKnightMoves();

	bool isValidPath[ROWS][COLS] = { false }; /*bool array that saves the path to a specific part of the board*/

	tr.root = findAllPossibleKnightPathsRec(startingPosition, validMoves, isValidPath); /*the recursive function that builds the tree*/
	return tr;
}

treeNode* findAllPossibleKnightPathsRec(chessPos startingPosition, chessPosArray*** validMoves, bool isValidPath[][COLS])
/*recursive function of findAllPossibleKnightPaths*/
{
	treeNode* resNode = createNewTreeNode(startingPosition, NULL);

	if (resNode == NULL)
		return NULL; 

	int x, y, i;
	treeNodeListCell* nextListCell = NULL;
	treeNodeListCell* currListCell = NULL;
	treeNode* currTreeNode;

	if (endOfPathCheck(startingPosition, validMoves, isValidPath)) 
		return resNode;

	else
	{
		getCoordinates(startingPosition, &x, &y);
		isValidPath[x][y] = true;

		for (i = 0; i < validMoves[x][y]->size; i++)
		{
			if (possiblePossCheck(validMoves[x][y]->positions[i], isValidPath))
			{
				currTreeNode = findAllPossibleKnightPathsRec(validMoves[x][y]->positions[i], validMoves, isValidPath);
				currListCell = createNewTreeNodeListCell(currTreeNode, nextListCell);

				nextListCell = currListCell;
			}
		}

		resNode->next_possible_positions = currListCell;
	}

	isValidPath[x][y] = false; 
	return resNode;               
}

treeNode* createNewTreeNode(chessPos position, treeNodeListCell* next_possible_positions)
/*this function creates new tree node*/
{
	treeNode* resNode = (treeNode*)malloc(sizeof(treeNode));

	if (resNode == NULL)
	{
		printf("Memory allocation failed!\n");
		return NULL;
	}

	(resNode->position)[0] = position[0];
	(resNode->position)[1] = position[1];

	resNode->next_possible_positions = next_possible_positions;

	return resNode;
}

treeNodeListCell* createNewTreeNodeListCell(treeNode* node, treeNodeListCell* next)
/*this function create new list cell*/
{
	treeNodeListCell* resCell = (treeNodeListCell*)malloc(sizeof(treeNodeListCell));

	if (resCell == NULL)
	{
		printf("Memory allocation failed!\n");
		return NULL;
	}

	resCell->node = node;
	resCell->next = next;

	return resCell;
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