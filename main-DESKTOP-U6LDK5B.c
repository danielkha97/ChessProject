#include "common.h"
void main()
{
	/*test for Q1*/
	chessPosArray*** test = validKnightMoves();

	printf("%d\n", test[0][0]->size);
	printf("%c ", test[0][0]->positions[0][0]);
	printf("%c", test[0][0]->positions[0][1]);
	printf("\n");
	printf("%c ", test[0][0]->positions[1][0]);
	printf("%c", test[0][0]->positions[1][1]);

	freeMat(test);
	/*end of test Q1*/

	  /*test Q5*/

		FILE* file;
		file = fopen("binariTest", "rb");
		BYTE byte, mask;
		int i;

		while (fread(&byte, 1, 1, file))
		{
			for (i = 7; i >= 0; i--)
			{
				mask = 1 << i;
				putchar((byte & mask) ? '1' : '0');
			}

			putchar(' ');
		}

		fclose(file);

	 /*end of test Q5*/
}
