#include "Q6.h"

int checkAndDisplayPathFromFile(char* file_name)         
{                                                      
	int duplicates, i, flag = 0, stepsCount = 0;     
	short positionsListSize;                               
	FILE* file = fopen(file_name, "rb");
	BYTE maskRow = 0xE0, maskCol = 0x1C, maskCase2 = 0x03, maskCase3 = 0x0F, currentByte, prevByte, temp;
	chessPos cp;
	chessPosList* list = makeEmptyChessPosList();
	memAllocTest(list);
	
	if (file == NULL) 
	{
		freeChessPosList(list);
		fclose(file);
		return -1;
	}
	fread(&positionsListSize, sizeof(short), 1, file); 

	for (i = 0; i < positionsListSize; i++)
	{

		if (stepsCount == 4)
			stepsCount = 0;
		if (flag == 0)
		{
			fread(&currentByte, 1, 1, file);
			prevByte = currentByte;
			flag++;
		}                                        
		switch (stepsCount) {                   
											
		case 0:                              
			temp = prevByte;                  
			break;                          
		case 1:                            
			fread(&currentByte, 1, 1, file);  
			temp |= (currentByte >> 2);     
			break;
		case 2:
			fread(&currentByte, 1, 1, file);
			prevByte = (prevByte & maskCase2) << 4;
			temp |= prevByte;
			temp |= currentByte >> 4;
			break;
		case 3:
			fread(&currentByte, 1, 1, file);
			prevByte = (prevByte & maskCase3) << 2;
			temp |= prevByte;
			break;
		}
		cp[0] = (char)((temp & maskRow) >> 5) + 'A';
		cp[1] = (char)((temp & maskCol) >> 2) + '1';
		addToListTail(list, cp[0],cp[1]);
		stepsCount++;
		temp = temp << 6;
		prevByte = currentByte;
	}
	if (!checkChessPosListValidty(*list))
	{
		freeChessPosList(list);
		fclose(file);
		return 1;
	}
	duplicates = deleteDuplicateAndCount(list); 
	positionsListSize -= (short)duplicates;         
	printBoard(list);

	if (positionsListSize == ROWS * COLS && duplicates == 0) 
	{
		freeChessPosList(list);
		fclose(file);
		return 2;
	}
	else           
	{
		freeChessPosList(list);
		fclose(file);
		return 3;
	}
}

int deleteDuplicateAndCount(chessPosList* lst)  
{
	int x, y, count = 0;
	bool duplicatesArr[ROWS][COLS] = { { false } };
	chessPosCell* current = lst->head;
	chessPosCell* previous = NULL;

	while (current != NULL)
	{
		x = current->position[0] - 'A';
		y = current->position[1] - '1';

		if (!duplicatesArr[x][y])
			duplicatesArr[x][y] = true;
		else
		{
			removeChessPosCell(previous);
			count++;
			current = previous;
		}
		previous = current;
		current = current->next;
	}

	return count;
}
bool checkNextMoveValidity(chessPos curr, chessPos next) 
{
	int i;
	bool valid = false;
	chessPosArray* cpa = vkmArrayByCoord(curr[0] - 'A', curr[1] - '1');

	if (cpa == NULL)
		return NULL;

	for (i = 0; i < cpa->size; i++)
	{
		if (next[0] == (cpa->positions)[i][0] && next[1] == (cpa->positions)[i][1])
			valid = true;
	}

	return valid;
}
bool checkChessPosListValidty(chessPosList list) //Goes over the list to check move validity. Returns true for a valid list.
{
	chessPosCell* cell = list.head;

	while (cell->next != NULL)
	{
		if (!checkNextMoveValidity(cell->position, cell->next->position))
			return false;

		cell = cell->next;
	}

	return true;
}
chessPosArray* vkmArrayByCoord(int x, int y) 
{
	chessPosArray* cpa = (chessPosArray*)malloc(sizeof(chessPosArray));

	memAllocTest(cpa);

	cpa->positions = (chessPos*)malloc(sizeof(chessPos) * 8); //8 available moves for a knight.

	memAllocTest(cpa->positions);

	cpa->size = 0;

	int index = 0, currX, currY, i;
	int possiblePositions[8][2] = { {x - 1, y - 2},{x - 2, y - 1},{x - 2, y + 1},{x - 1, y + 2},{x + 1, y + 2},{x + 2, y + 1},{x + 2, y - 1},{x + 1, y - 2} };
	
	for (i = 0; i < 8; i++)
	{

		currX = possiblePositions[i][0];
		currY = possiblePositions[i][1];
		if (validCoord(currX, currY))
		{
			(cpa->size)++;
			(cpa->positions)[index][0] = 'A' + currX;
			(cpa->positions)[index][1] = '1' + currY;
			index++;
		}
	}

	chessPosArray* temp = cpa->positions;
	temp = (chessPos*)realloc(cpa->positions, sizeof(chessPos) * cpa->size);

	memAllocTest(temp);

	cpa->positions = temp;
	return cpa;
}
int validCoord(int x, int y) 
{
	return x >= 0 && x < ROWS&& y >= 0 && y < COLS;
}