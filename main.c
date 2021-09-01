
#include "main.h"


#define MAX_SIZE 25



void main()
{
	menu();
}

void printMenu()
{
	printf("1. Enter knight's starting position\n");
	printf("2. Create all possible knight paths\n");
	printf("3. Find a knight path covering all board\n");
	printf("4. Save knight path covering all board to file\n");
	printf("5. Load and display path from file\n");
	printf("6. Exit\n");
}

void menu()
{
	int playerChoice = -9;

	chessPos* startingPosition = NULL; /*initializing the chesspos to null to prevent usage of free to unreadable memory*/
	pathTree tr;
	tr.root = NULL; /*initializing the tree root to be null*/
	chessPosList* lst = NULL; /*initializing the lst root to be null*/

	while (1)
	{
		printMenu();
		scanf("%d", &playerChoice);

		while (playerChoice < 1 || playerChoice > 6) /*if the player choice is not valid, he can try again*/
		{
			printf("invalid choice, please try again!\n");
			scanf("%d", &playerChoice);
		}

		switch (playerChoice)
		{
		case 1:
			free(startingPosition);
			startingPosition = option1();
			break;
		case 2:
			freeTree(tr);
			tr = option2(startingPosition);
			break;
		case 3:
			freeChessPosList(lst);
			lst = option3(startingPosition, tr);
			break;
		case 4:
			option4(startingPosition, tr, lst);
			break;
		case 5:
			option5();
			break;
		case 6:
			printf("Good bye...\n");
			exit(1);
		default:
			break;
		}
	}
}

/*option 1 function and helper*/

chessPos* option1()
{
	char row;
	int col;
	chessPos* startingPosition = malloc(sizeof(chessPos));
	memAllocTest(startingPosition); /*memory allocation check*/

	(*startingPosition)[0] = -9; /*initializing the pos array for entering the loop with false value*/
	(*startingPosition)[1] = -9;

	while (1)
	{
		printf("enter row: \n");
		scanf(" %c", &row);

		printf("enter col: \n");
		scanf("%d", &col);

		if ('A' <= row && row < ('A' + ROWS) && 0 < col && col <= COLS)
		{
			(*startingPosition)[0] = row;
			(*startingPosition)[1] = (col + '0');
			break;
		}
	}

	//	while (isValidInput(*startingPosition)) /*checking if the input is valid, if not, you get to enter the position again*/
	//	{
	//		printf("enter row: \n");
	//		scanf(" %c", &row);
	//
	//		printf("enter col: \n");
	//		scanf(" %c", &col);
	//
	//		(*startingPosition)[0] = row;
	//		(*startingPosition)[1] = col;
	//	}
	printf("Position set!\n\n");
	return startingPosition;
}
//
//bool isValidInput(chessPos position)
//{
//	return (position[1] >= '1' + COLS || position[1] < '1' || position[0] < 'A' || position[0] >= 'A' + ROWS);
//}

/*option 2 function*/

pathTree option2(chessPos* startingPosition)
{
	pathTree tr;
	tr.root = NULL;

	if (startingPosition == NULL) /*if there is no starting position*/
	{
		printf("To generate the tree, please enter a starting position first!\n\n");
	}
	else
	{
		tr = findAllPossibleKnightPaths(startingPosition); /*generating the function from 3*/

		if (tr.root == NULL) /*if there are no optional paths*/
			printf("No paths found!\n");
		else
			printf("The tree generated! All possible paths saved into it!\n\n");
	}

	return tr;
}

/*option 3*/

chessPosList* option3(chessPos* startingPosition, pathTree tr)
{
	chessPosList* lst = NULL; /*initializing rhe list to be null at first*/

	if (tr.root == NULL)
		tr = option2(startingPosition); /*if the tree from option 2 is empty, we generate it*/

	lst = findKnightPathCoveringAllBoard(&tr); /*generating the function from 4*/

	if (lst == NULL)
		printf("A path that covering all the board is not found!\n\n");

	else
		printf("The list created with all board path!\n\n");

	return lst;
}

/*option 4*/

void option4(chessPos* startingPosition, pathTree tr, chessPosList* lst)
{
	int phySize = 0;
	char* fileName;

	fileName = (char*)malloc((MAX_SIZE) * sizeof(char));
	memAllocTest(fileName);

	printf("Please enter the file name, with no spaces and with max 25 characters\n");
	scanf("%s", fileName);

	saveToBinFile(fileName, lst); /*generating the function from 5*/
	free(fileName);
}

/*option 5*/

void option5()
{
	char* fileName;
	int value;

	fileName = (char*)malloc((MAX_SIZE) * sizeof(char));
	memAllocTest(fileName);

	printf("Please enter the file name, with no spaces and with max 25 characters\n");
	scanf("%s", fileName);

	value = checkAndDisplayPathFromFile(fileName); /*generating the function from 6*/

	switch (value) /*switch case according to the direction of 6*/
	{
	case -1:
		printf("The file is not found!\n\n");
		break;
	case 1:
		printf("The path is invalid!\n\n");
		break;
	case 2:
		printf("The path covered all the board!\n\n");
		break;
	case 3:
		printf("The path is valid!\n\n");
		break;
	default:
		break;
	}

	free(fileName);
}






