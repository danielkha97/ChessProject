#include "Q2.h"

chessPosCell* createNewChessPosCell(chessPos position, chessPosCell* next)
{
	chessPosCell* cpCell = (chessPosCell*)malloc(sizeof(chessPosCell));
	memAllocTest(cpCell);

	cpCell->position[0] = position[0];
	cpCell->position[1] = position[1];
	cpCell->next = next;
	return cpCell;
}

void removeChessPosCell(chessPosCell* prev)
{
	chessPosCell* remove = prev->next;
	prev->next = remove->next;
	free(remove);
}

void display(chessPosList* lst)
{
	int x, y;
	bool isExistInList[ROWS][COLS] = { false };
	chessPosCell* curr = lst->head;
	chessPosCell* prev = NULL;

	while (curr != NULL)
	{
		x = curr->position[0] - 'A';
		y = curr->position[1] - '1';

		if (!isExistInList[x][y])
			isExistInList[x][y] = true;

		else
		{
			removeChessPosCell(prev);
			curr = prev;
		}

		prev = curr;
		curr = curr->next;
	}
	printBoard(lst);
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

	for (i = 0; i < ROWS; i++)
	{
		if (i == 0)
		{
			printf("x---^");
			for (j = 0; j < ROWS; j++)
				printf("---^");

			printf("\n| + |");
			for (j = 0; j < ROWS; j++)
				printf(" %d |", j);

			printf("\n|---!");
			for (j = 0; j < ROWS; j++)
				printf("---|");
			printf("\n");
		}

		printf("| %c |", 'A' + i);

		for (j = 0; j < ROWS; j++)
		{
			if (gameBoard[i][j] == 0)
				printf("   |");
			else
				printf(" %d |", gameBoard[i][j]);
		}

		printf("\n");
		printf("+---+---+---+---+---+---+---+---+---+\n");
	}

}

chessPosList* makeEmptyChessPosList()
{
	chessPosList* list = malloc(sizeof(chessPosList));
	memAllocTest(list);

	list->head = NULL;
	list->tail = NULL;
	return list;
}

bool isEmptyChessPosList(chessPosList list)
{
	if (list.head == NULL)
		return true;
	return false;
}

void addToStartOfChessPosList(chessPosList* list, chessPosCell* cell)
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
