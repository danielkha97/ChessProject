#include "common.h"
#include "Q1.h"
#include "Q2.h"
#include "Q3.h"
#include "Q4.h"
#include "Q5.h"

void main()
{
	///*test for Q1*/
	//chessPosArray*** test = validKnightMoves();

	//printf("%d\n", test[0][0]->size);
	//printf("%c ", test[0][0]->positions[0][0]);
	//printf("%c", test[0][0]->positions[0][1]);
	//printf("\n");
	//printf("%c ", test[0][0]->positions[1][0]);
	//printf("%c", test[0][0]->positions[1][1]);

	//freeMat(test);
	///*end of test Q1*/



	/*test Q4*/

	chessPos position = { 'A','3' };
	pathTree tree = findAllPossibleKnightPaths(&position);
	chessPosList* list;
	list = findKnightPathCoveringAllBoard(&tree);
	printf("success?");

	/*end of test Q4*/

	 // /*test Q5*/

		//FILE* file;
		//file = fopen("file_name", "rb");
		//BYTE byte, mask;
		//int i;

		//while (fread(&byte, 1, 1, file))
		//{
		//	for (i = 7; i >= 0; i--)
		//	{
		//		mask = 1 << i;
		//		putchar((byte & mask) ? '1' : '0');
		//	}

		//	putchar(' ');
		//}

		//fclose(file);

	 ///*end of test Q5*/



}
