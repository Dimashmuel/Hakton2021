#define _CRT_SECURE_NO_WARNINGS

/***************************************************
 * Hackathon - Summer 2021                         *
 *                                                 *
 * This program implements the Reversi board game  *
 *                                                 *
 ***************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define GRID_SIZE 8  
#define SEED 1  
#define FIRST  1 
#define SECOND 2 
#define EMPTY  0 
#define TRUE	1
#define FALSE	0
void createBoard(int[][GRID_SIZE]);
int isLegal(int[][GRID_SIZE], int, int, int);
int play(int[][GRID_SIZE], int, int, int);
int benefit(int[][GRID_SIZE], int, int, int);	/* Task 4 */
int possibleMoves(int[][GRID_SIZE], int[][2], int);	/* Task 5 */
int hasMoves(int[][GRID_SIZE], int);				/* Task 6 */
int findTheWinner(int[][GRID_SIZE]);					/* Task 7 */
int gameOver(int[][GRID_SIZE]);					/* Task 8 */

/* Additional functions */
void interactivePlay();
void randomPlayer(int[][GRID_SIZE], int);
void displayBoard(int[][GRID_SIZE]);

/*****************************************************
 * You can add additional function declarations here *
 *****************************************************/

 /* End of function declarations */


 /* ---------------------------------------------------------------------------------------- *
  * The main function																		*
  * ---------------------------------------------------------------------------------------- */
int main()
{
	interactivePlay();

	getchar();
	return 0;
}
void createBoard(int board[][GRID_SIZE]) 
{
	int i, j;
	for (i = 0; i < GRID_SIZE; i++)
		for (j = 0; j < GRID_SIZE; j++)
		{
			board[i][j] = 0;
		}
	board[(GRID_SIZE / 2) - 1][(GRID_SIZE / 2) - 1] = FIRST;
	board[(GRID_SIZE / 2) - 1][(GRID_SIZE / 2)] = SECOND;
	board[(GRID_SIZE / 2)][(GRID_SIZE / 2) - 1] = SECOND;
	board[(GRID_SIZE / 2)][(GRID_SIZE / 2)] = FIRST;
}
int isLegal(int board[][GRID_SIZE], int player, int row, int column) 
{
	int i, j, di, dj, x, y;
	if (board[row][column] != 0)
		return FALSE;
	for (i = row - 1; i <= row + 1; i++)
	{
		for (j = column - 1; j <= column + 1; j++)
		{
			if (!(i >= 0 && i < GRID_SIZE && j >= 0 && j < GRID_SIZE))
				continue;
			if (board[i][j] == 3 - player)
			{
				di = i - row;
				dj = j - column;
				for (x = i, y = j; (x >= 0 && x < GRID_SIZE && y >= 0 && y < GRID_SIZE) && board[x][y] == 3 - player; x += di, y += dj);
				if ((x >= 0 && x < GRID_SIZE && y >= 0 && y < GRID_SIZE) && board[x][y] == player)
					return TRUE;
			}
		}
	}
	return FALSE;
}
int play(int board[][GRID_SIZE], int player, int row, int column) 
{
	int i, j, idelta, jdelta, x, y;
	board[row][column] = player;
	for (i = row - 1; i <= row + 1; i++)
	{
		for (j = column - 1; j <= column + 1; j++)
		{
			if (!(i >= 0 && i < GRID_SIZE && j >= 0 && j < GRID_SIZE))
				continue;
			if (board[i][j] == 3 - player)
			{
				idelta = i - row;
				jdelta = j - column;
				for (x = i, y = j; (x >= 0 && x < GRID_SIZE && y >= 0 && y < GRID_SIZE) && board[x][y] == 3 - player; x += idelta, y += jdelta);
				if ((x >= 0 && x < GRID_SIZE && y >= 0 && y < GRID_SIZE) && board[x][y] == player)
					for (x = i, y = j; (x >= 0 && x < GRID_SIZE && y >= 0 && y < GRID_SIZE) && board[x][y] == 3 - player; x += idelta, y += jdelta)
						board[x][y] = player;
			}
		}
	}
	return isLegal(board, player, row, column);

}
int benefit(int board[][GRID_SIZE], int player, int row, int column) 
{
	int i, j, idelta, jdelta, x, y, counter = 0;
	if (isLegal(board, player, row, column))
		return FALSE;
	for (i = row - 1; i <= row + 1; i++)
	{
		for (j = column - 1; j <= column + 1; j++)
		{
			if (!(i >= 0 && i < GRID_SIZE && j >= 0 && j < GRID_SIZE))
				continue;
			if (board[i][j] == 3 - player)
			{
				idelta = i - row;
				jdelta = j - column;
				for (x = i, y = j; (x >= 0 && x < GRID_SIZE && y >= 0 && y < GRID_SIZE) && board[x][y] == 3 - player; x += idelta, y += jdelta);
				if ((x >= 0 && x < GRID_SIZE && y >= 0 && y < GRID_SIZE) && board[x][y] == player)
					for (x = i, y = j; (x >= 0 && x < GRID_SIZE && y >= 0 && y < GRID_SIZE) && board[x][y] == 3 - player; x += idelta, y += jdelta)
						counter++;
			}
		}
	}

	return counter;
}
int possibleMoves(int board[][GRID_SIZE], int movesArray[][2], int player) 
{
	int i, j, count = 0;
	for (i = 0; i < GRID_SIZE; i++)
	{
		for (j = 0; j < GRID_SIZE; j++)
		{
			if (isLegal(board, player, i, j))
			{
				movesArray[count][0] = i;
				movesArray[count][1] = j;
				count++;
			}
		}
	}
	return count;
}
int hasMoves(int board[][GRID_SIZE], int player) 
{
	int i, j;
	for (i = 0; i < GRID_SIZE; i++)
		for (j = 0; j < GRID_SIZE; j++)
			if ((board, player, i, j))
				return TRUE;
	return FALSE;
}
int findTheWinner(int board[][GRID_SIZE]) 
{
	int i, j;
	int count1 = 0;
	int count2 = 0;
	for (i = 0; i < GRID_SIZE; i++)
	{
		for (j = 0; j < GRID_SIZE; j++)
		{
			if (board[i][j] == 1)
				count1++;
			if (board[i][j] == 2)
				count2++;
		}
	}
	if (count1 > count2)
		return count1;
	if (count2 > count1)
		return count2;
	if (count2 = count1)
		return 0;
}
int gameOver(int board[][GRID_SIZE]) 
{
	int i, j;
	int count1 = 0;
	int count2 = 0;
	for (i = 0; i < GRID_SIZE; i++)
	{
		for (j = 0; j < GRID_SIZE; j++)
		{
			if (board[i][j] == 1)
				count1++;
			if (board[i][j] == 2)
				count2++;
		}
	}
	return  count1 + count2 == (GRID_SIZE * GRID_SIZE) || count2 == 0 || count1 == 0;
}
void interactivePlay()
{
	int board[GRID_SIZE][GRID_SIZE];
	int row, column, winner;
	unsigned int seed = SEED;

	createBoard(board);
	displayBoard(board);

	printf("\nWelcome to the most magnificent Reversi Game!\n");

	/* Seed for the random player */
	srand(seed);

	printf("You are player 1... \n");

	/* Check whether the game is not over */
	while (!gameOver(board))
	{
		/* If player 1 has no moves - skip to player 2 */
		if (hasMoves(board, FIRST))
		{
			printf("\nPlay:\n");
			printf("Enter row and column: ");
			scanf("%d %d", &row, &column);

			while (!(isLegal(board, FIRST, row, column)))
			{
				printf("Not a legal move! Please try again...\n");
				printf("Enter row and column: ");
				scanf("%d %d", &row, &column);
			}

			play(board, FIRST, row, column);
			displayBoard(board);
		}
		else
			printf("You can't play, there are no legal moves. Player 2 will play again\n");

		printf("May I (player 2) play? (press ENTER for Yes)\n");
		getchar();
		getchar();

		/* If player 2 has no moves - skip to player 1 */
		if (hasMoves(board, SECOND))
		{
			randomPlayer(board, SECOND);
			displayBoard(board);
		}
		else
			printf("I can't play, there are no legal moves. Player 1 will play again\n");
	} /* End of while(!gameOver(board....) */

	/* Declare the winner */
	winner = findTheWinner(board);

	if (winner == FIRST)
	{
		printf("\n\t *************************");
		printf("\n\t * You are the winner !! *");
		printf("\n\t *************************\n");
	}
	else if (winner == SECOND)
		printf("\nYou lost :( \n");
	else
		printf("\nThe game ended in a tie...\n");
} /* End of interactivePlay */
void randomPlayer(int board[][GRID_SIZE], int player)
{
	/* Define the parameters and their initial values */
	int movesArray[GRID_SIZE * GRID_SIZE][2];
	int numOfMoves, chosenMove;
	int row, column;

	/* number of possible moves */
	numOfMoves = possibleMoves(board, movesArray, player); /* Gets the possible moves of <player> */

	/* The chosen move out of all the possible moves */
	chosenMove = (int)((double)rand() / ((double)RAND_MAX + 1) * (numOfMoves)); /* The index (in movesArray) of the move */

	printf("Move %d out of %d\n", chosenMove, numOfMoves);

	if (chosenMove != -1)
	{ /* There is a possible move (with benefit > 0) */
		row = movesArray[chosenMove][0];
		column = movesArray[chosenMove][1];
		play(board, player, row, column);
	}
	/* Else - we didn't change the board */
} /* End of randomPlayer */
void displayBoard(int board[][GRID_SIZE])
{
	int row, column;

	/* First row */
	printf("   ");
	for (column = 0; column < GRID_SIZE; column++)
		printf(" %d ", column);

	/* Second row */
	printf("\n   ");
	for (column = 0; column < GRID_SIZE; column++)
		printf("---");

	/* The board */
	for (row = 0; row < GRID_SIZE; row++)
	{
		printf("\n%d |", row);
		for (column = 0; column < GRID_SIZE; column++)
		{
			if (board[row][column] != EMPTY)
				printf(" %d ", board[row][column]);
			else
				printf("   ");
		} /* End of for column */
		printf("|");
	} /* End of for row */

	/* Last row) */
	printf("\n   ");
	for (column = 0; column < GRID_SIZE; column++)
		printf("---");
	printf("\n");
} /* End of displayBoard */