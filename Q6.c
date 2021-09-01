#include "Q6.h"

int checkAndDisplayPathFromFile(char* file_name)          
{                                                       
	int duplicates, i, flag = 0, stepCounter = 0;      
	short posListSize;                               
	FILE* fp = fopen(file_name, "rb");
	BYTE maskRow = 0xE0, maskCol = 0x1C, maskCase2 = 0x03, maskCase3 = 0x0F, currByte, prevByte, temp;
	chessPos cp;

	chessPosList* list = makeEmptyChessPosList();
	memAllocTest(list);

	if (fp == NULL) // File not found.
	{
		freeChessPosList(list);
		fclose(fp);
		return -1;
	}

	fread(&posListSize, sizeof(short), 1, fp);  //Gets the size of the list.

	for (i = 0; i < posListSize; i++)
	{

		if (stepCounter == 4)
			stepCounter = 0;
		if (flag == 0)
		{
			fread(&currByte, 1, 1, fp);
			prevByte = currByte;
			flag++;
		}                                         
		switch (stepCounter) {                   
												
		case 0:                               
			temp = prevByte;                  
			break;                          
		case 1:                             
			fread(&currByte, 1, 1, fp);  
			temp |= (currByte >> 2);      
			break;
		case 2:
			fread(&currByte, 1, 1, fp);
			prevByte = (prevByte & maskCase2) << 4;
			temp |= prevByte;
			temp |= currByte >> 4;
			break;
		case 3:
			fread(&currByte, 1, 1, fp);
			prevByte = (prevByte & maskCase3) << 2;
			temp |= prevByte;
			break;
		}
		cp[0] = (char)((temp & maskRow) >> 5) + 'A';
		cp[1] = (char)((temp & maskCol) >> 2) + '1';
		addChessPosToEndList(list, cp);
		
		stepCounter++;
		temp = temp << 6;
		prevByte = currByte;
	}
	if (!isListValid(*list)) // Invalid move set.
	{
		freeChessPosList(list);
		fclose(fp);
		return 1;
	}
	duplicates = deleteDuplicateAndCount(list);  //duplicates removed from list
	posListSize -= (short)duplicates;           
	printBoard(list);

	if (posListSize == ROWS*COLS && duplicates == 0) // Knight's tour, full board.
	{
		freeChessPosList(list);
		fclose(fp);
		return 2;
	}
	else            // Valid move set.
	{
		freeChessPosList(list);
		fclose(fp);
		return 3;
	}
}
int deleteDuplicateAndCount(chessPosList* lst)  // Deletes duplicate moves using a bool array. A number is returned to deduct from the list length.
{
	int x, y, count = 0;
	bool dupArray[ROWS][COLS] = { { false } };
	chessPosCell* curr = lst->head;
	chessPosCell* previous = NULL;

	while (curr != NULL)
	{
		x = curr->position[0] - 'A';
		y = curr->position[1] - '1';

		if (!dupArray[x][y])
			dupArray[x][y] = true;
		else
		{
			removeCell(previous);
			count++;
			curr = previous;
		}
		previous = curr;
		curr = curr->next;
	}

	return count;
}
bool isNextValid(chessPos curr, chessPos next) //Checks if the next position is a valid move.
{
	int i;
	bool valid = false;
	chessPosArray* cpa = validMovesByPosition(curr[0] - 'A', curr[1] - '1');

	if (cpa == NULL)
		return NULL;

	for (i = 0; i < cpa->size; i++)
	{
		if (next[0] == (cpa->positions)[i][0] && next[1] == (cpa->positions)[i][1])
			valid = true;
	}

	return valid;
}
bool isListValid(chessPosList list) //Goes over the list to check move validity. Returns true for a valid list.
{
	chessPosCell* cell = list.head;

	while (cell->next != NULL)
	{
		if (!isNextValid(cell->position, cell->next->position))
			return false;

		cell = cell->next;
	}

	return true;
}
chessPosArray* validMovesByPosition(int x, int y) //Creates an array of valid knight moves by coordinates. 
{
	chessPosArray* positionArray = (chessPosArray*)malloc(sizeof(chessPosArray));
	memAllocTest(positionArray);

	positionArray->positions = (chessPos*)malloc(sizeof(chessPos) * 8); //8 available moves for a knight.
	memAllocTest(positionArray->positions);

	positionArray->size = 0;

	int index = 0, currX, currY, i;
	int possiblePositions[8][2] = { {x - 1, y - 2},{x - 2, y - 1},{x - 2, y + 1},{x - 1, y + 2},{x + 1, y + 2},{x + 2, y + 1},{x + 2, y - 1},{x + 1, y - 2} };
	//The possible position array will be used to calculate if the coordinates are valid for each possible knight move.
	for (i = 0; i < MaxValidKnightMoves; i++)
	{

		currX = possiblePositions[i][0];
		currY = possiblePositions[i][1];
		if (validCoord(currX, currY))
		{
			(positionArray->size)++;
			(positionArray->positions)[index][0] = 'A' + currX;
			(positionArray->positions)[index][1] = '1' + currY;
			index++;
		}
	}

chessPosArray* temp = positionArray->positions;
	temp = (chessPos*)realloc(positionArray->positions, sizeof(chessPos) * positionArray->size);

	memAllocTest(temp);

	positionArray->positions = temp;
	return positionArray;
}
int validCoord(int x, int y) //Checks if we are within board bounds.
{
	return x >= 0 && x < ROWS&& y >= 0 && y < COLS;
}
void addChessPosToEndList(chessPosList* list, chessPos cp) //Creates a cell by position, and adds it to the tail end of a list.
{
	chessPosCell* cell = createNewChessPosCell(cp, NULL);

	if (cell == NULL)
		return NULL;

	addToEndOfChessPosList(list, cell);
}
void addToEndOfChessPosList(chessPosList* list, chessPosCell* cell) //Connects a cell to the tail of a list.
{
	if (isEmptyChessPosList(*list))
		list->head = list->tail = cell;

	else
	{
		list->tail->next = cell;
		list->tail = cell;
	}
}