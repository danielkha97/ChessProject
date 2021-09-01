#include "Q5.h"


void saveToBinFile(char* file_name, chessPosList* pos_list)
{
	/*variables*/
	unsigned short listSize;
	int countOfZeros = 0;
	chessPosCell* curr = pos_list->head;
	FILE* file = fopen(file_name, "w+b"); /*opening the file*/
	BYTE mask, posConvertion, lastByte;

	fileOpenCheck(file); /*checks if the file opened succesfully*/

	listSize = findListSize(pos_list); /*gets the list size*/
	fwrite(&listSize, sizeof(short), 1, file); /*writing the size to file*/

	while (curr != NULL && listSize != 0)
	{
		posConvertion = posToByte(curr->position); /*converts the position array into 8 bits*/

		if (countOfZeros > 0 ) 
		{
			lastByte = lastByteFromFile(file);
			mask = maskMaker(posConvertion, countOfZeros); /*making the right mask according to the countOfZeros*/
			updateByte(file, lastByte, mask);
			posConvertion <<= countOfZeros;
		}

		if (countOfZeros == 8)/*if this term is true we "closed" a comlepte BYTE*/
			countOfZeros = 0;

		else
			fwrite(&posConvertion, 1, 1, file);

		countOfZeros += 2;
		fflush(file);
		curr = curr->next; /*moving on to the next cell in the chain*/
	}

	fclose(file); /*closing the file*/
}

BYTE lastByteFromFile(FILE* file)
/*getting the last byte from the file*/
{
	BYTE prev;
	fseek(file, -1, SEEK_CUR);
	fread(&prev, 1, 1, file);
	return prev;
}

void updateByte(FILE* file, BYTE prevByte, BYTE mask) 
/*updating the last byte after masking it*/
{
	BYTE masked;
	masked = prevByte | mask;
	fseek(file, -1, SEEK_CUR);
	fwrite(&masked, 1, 1, file);
}

BYTE maskMaker(BYTE posConvertion, int countOfZeros) 
/*creates required mask*/
{
	int toMove = 8 - countOfZeros;
	return posConvertion >> toMove;
}

short findListSize(chessPosList* pos_list)
/*determines list size*/
{
	short size = 0;
	chessPosCell* curr = pos_list->head;

	while (curr != NULL)
	{
		size++;
		curr = curr->next;
	}

	return size;
}

BYTE posToByte(chessPos position)
/*converts the position into 8 bits*/
{
	BYTE x, y;

	x = position[0] - 'A';
	y = position[1] - '1';

	x <<= 5;
	y <<= 2;

	return x | y;
}





