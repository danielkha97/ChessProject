#include "Q2.h"

chessPosCell* createNewChessPosCell(chessPos position, chessPosCell* next)
/*this function creates new chess pos cell*/
{
	chessPosCell* cpCell = (chessPosCell*)malloc(sizeof(chessPosCell));
	memAllocTest(cpCell);

	cpCell->position[0] = position[0];
	cpCell->position[1] = position[1];
	cpCell->next = next;
	return cpCell;
}

void removeCell(chessPosCell* prev)
/*this function removes a cell and frees it*/
{
	chessPosCell* remove = prev->next;
	prev->next = remove->next;
	free(remove);
}

void display(chessPosList* lst)
/*the function from task 2*/
{
	int x, y;
	bool isExistInList[ROWS][COLS] = { false }; /*a boolean array that checks if a cell exists in the list*/
	chessPosCell* curr = lst->head; 
	chessPosCell* prev = NULL;

	while (curr != NULL)
	{
		x = curr->position[0] - 'A'; 
		y = curr->position[1] - '1';

		if (!isExistInList[x][y]) /* checking if the cell is already in the list*/
			isExistInList[x][y] = true; /*if not, we change his place to true*/

		else
		{
			removeCell(prev); /*if yes, we remove it form the list*/
			curr = prev; /*we return the curr node to the prev one because we the removed a cell before*/
		}

		prev = curr;
		curr = curr->next;
	}
	printBoard(lst); /*printing the board*/
}

void printBoard(chessPosList* lst)
{
	int i, j, x, y;
	int counter = 1;
	int gameBoard[ROWS][COLS] = { 0 };
	chessPosCell* curr = lst->head;

	while (curr != NULL)
	{
		x = (int)curr->position[0] - 'A';
		y = (int)curr->position[1] - '1';

		gameBoard[x][y] = counter;
		counter++;
		curr = curr->next;
	}

	for (i = 0; i < ROWS; i++) /*loops for printing the board according to its size*/
	{
		if (i == 0)
		{
			printf("+---+");

			for (j = 0; j < ROWS; j++)
				printf("---+");

			printf("\n|   |");

			for (j = 0; j < ROWS; j++)
				printf(" %d |", j);

			printf("\n|---|");

			for (j = 0; j < ROWS; j++)
				printf("---|");

			printf("\n");
		}

		printf("| %c |", 'A' + i);

		for (j = 0; j < ROWS; j++)
		{
			if (gameBoard[i][j] == 0)
				printf("   |");
			else if (gameBoard[i][j] >= 10)
				printf("%d |", gameBoard[i][j]);
			else
				printf(" %d |", gameBoard[i][j]);
		}

		printf("\n");
		printf("+---+");

		for (j = 0; j < ROWS - 1; j++)
		{
			printf("---+");
		}

		printf("---+\n");
	}

}

chessPosList* makeEmptyChessPosList()
/*making empty list*/
{

	chessPosList* list = malloc(sizeof(chessPosList)); 
	memAllocTest(list);

	list->head = NULL;
	list->tail = NULL;
	return list;
}

bool isEmptyChessPosList(chessPosList list)
/*checking if a list is empty or not*/
{
	if (list.head == NULL)
		return true;
	return false;
}

void addToStartOfChessPosList(chessPosList* list, chessPosCell* cell)
/*this function adds a cell into the heaf of the list*/
{
	if (isEmptyChessPosList(*list))
		list->head = list->tail = cell;

	else
	{
		cell->next = list->head;
		list->head = cell;
	}
}

void freeChessPosList(chessPosList* list)
{
	chessPosCell* curr, * next;

	if (list != NULL)
	{
		curr = list->head;

		while (curr != NULL)
		{
			next = curr->next;
			free(curr);
			curr = next;
		}
	}

	free(list);
}

void addToListTail(chessPosList* list, int x, int y)
{
	/*this function adds a cell into the end of the list*/
	chessPos* cpArr = setCoordinates(x, y);
	chessPosCell* cpCell = createNewChessPosCell(*cpArr, NULL);

	if (isEmptyChessPosList(*list))
		list->head = list->tail = cpCell;

	else
	{
		list->tail->next = cpCell;
		list->tail = cpCell;
	}
}

chessPos* setCoordinates(int x, int y)
{
	chessPos* cpArr = (chessPos*)malloc(sizeof(chessPos));
	memAllocTest(cpArr);

	(*cpArr)[0] = 'A' + x;
	(*cpArr)[1] = '1' + y;
	return cpArr;
}
