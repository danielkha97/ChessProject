#include "Q1.h"

chessPosArray*** validKnightMoves()/*Q1 function - fill a mat with all possible moves for a knight*/
{

	chessPosArray*** possiblePositionBoard = boardCreation();/*creation of the board*/

	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			possiblePositionBoard[i][j] = (chessPosArray*)malloc(sizeof(chessPosArray));/*memory allocation for each cell's positions array*/
			cellStepsCheck((i), (j), possiblePositionBoard[i][j]); /*for each cell in the mat we fill the possible steps array*/
		}
	}
	return possiblePositionBoard;/*returns the full mat pointer*/
}
chessPosArray*** boardCreation()/*creates the mat representing the game board*/
{
	chessPosArray*** possiblePositionsBoard = (chessPosArray***)malloc(sizeof(chessPosArray**) * ROWS);/*create of 2D array*/
	memAllocTest(possiblePositionsBoard);/*mem allocation test - generic test for all types of pointers*/

	for (int i = 0; i < ROWS; i++)/*each cell gets assigned with a pointer to an array representing each column*/
	{
		possiblePositionsBoard[i] = (chessPosArray**)malloc(sizeof(chessPosArray**) * COLS);
		memAllocTest(possiblePositionsBoard[i]);
	}

	return possiblePositionsBoard;
}
chessPosArray* cellStepsCheck(char row, char col, chessPosArray* posArray)/*checks each cell's possible next steps*/
{
	int counter = 0;
	chessPos* possibleCellMoves = (chessPos*)malloc(sizeof(chessPos) * MaxValidKnightMoves);
	memAllocTest(possibleCellMoves);

	if (row - 2 < ROWS && row - 2 >= 0 && col - 1 < COLS && col - 1 >= 0)
	{
		possibleCellMoves[counter][0] = (row - 2 + 'A');
		possibleCellMoves[counter][1] = (col - 1 + '1');
		counter++;

	}
	if (row - 1 < ROWS && row - 1 >= 0 && col - 2 < COLS && col - 2 >= 0)
	{
		possibleCellMoves[counter][0] = (row - 1 + 'A');
		possibleCellMoves[counter][1] = (col - 2 + '1');
		counter++;

	}
	if (row + 1 < ROWS && row + 1 >= 0 && col - 2 < COLS && col - 2 >= 0)
	{
		possibleCellMoves[counter][0] = (row + 1 + 'A');
		possibleCellMoves[counter][1] = (col - 2 + '1');
		counter++;

	}
	if (row + 2 < ROWS && row + 2 >= 0 && col - 1 < COLS && col - 1 >= 0)
	{
		possibleCellMoves[counter][0] = (row + 2 + 'A');
		possibleCellMoves[counter][1] = (col - 1 + '1');
		counter++;

	}
	if (row + 2 < ROWS && row + 2 >= 0 && col + 1 < COLS && col + 1 >= 0)
	{
		possibleCellMoves[counter][0] = (row + 2 + 'A');
		possibleCellMoves[counter][1] = (col + 1 + '1');
		counter++;
	}
	if (row + 1 < ROWS && row + 1 >= 0 && col + 2 < COLS && col + 2 >= 0)
	{
		possibleCellMoves[counter][0] = (row + 1 + 'A');
		possibleCellMoves[counter][1] = (col + 2 + '1');
		counter++;

	}
	if (row - 1 < ROWS && row - 1 >= 0 && col + 2 < COLS && col + 2 >= 0)
	{
		possibleCellMoves[counter][0] = (row - 1 + 'A');
		possibleCellMoves[counter][1] = (col + 2 + '1');
		counter++;

	}
	if (row - 2 < ROWS && row - 2 >= 0 && col + 1 < COLS && col + 1 >= 0)
	{
		possibleCellMoves[counter][0] = (row - 2 + 'A');
		possibleCellMoves[counter][1] = (col + 1 + '1');
		counter++;

	}

	possibleCellMoves = (chessPos*)realloc(possibleCellMoves, sizeof(chessPos) * counter);
	memAllocTest(possibleCellMoves);
	posArray->positions = possibleCellMoves;
	posArray->size = counter;

	return posArray;


}
void freeMat(chessPosArray*** board)/*memory allocation clearing*/
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			free(board[i][j]);
		}
	}
	free(board);
}