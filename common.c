#include "common.h"

void memAllocTest(void* p)/*memory allocation test*/
{
	if (p == NULL)
	{
		printf("\nMemory allocation failed. Exiting...\n");
		exit(1);
	}
}

void fileOpenCheck(FILE* file)
{
	if (file == NULL)
	{
		printf("file failed to open. Exiting...");
		exit(1);
	}
}

void getCoordinates(chessPos position, int* x, int* y)
/*this function saves the coordinates of a position*/
{
	*x = position[0] - 'A';
	*y = position[1] - '1';
}

