
#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
char **create_board(int size);
void printBoard(char **board, int size);
int check_win (char **board, int row, int col, int size, char mark);
void free_board (char **board, int size);

int main()
{
    char **board;
    int row, col, size_row, size_col, counter_moves=0;

    printf("Enter the dimensions of the board: "); /* Get size of the board from the user && check validation */
    if (scanf("%d%d",&size_row,&size_col) != 2)
    {
        printf("\nInput Error!");
        return 1;
    }
    if (size_row != size_col || size_row<3)
    {
        printf("\nInput Error!");
        return 1;
    }

    board = create_board(size_row);

    while (TRUE)
    {
        printf("\nThe turn of A, type your choice (row col): "); /* Get input position of 'X' */
        if (scanf("%d%d",&row,&col) != 2)
        {
            printf("\nInput Error!");
            return 1;
        }
        if (row<0 || col<0 || row>=size_row || col>=size_row || board[row][col]!=' ') /* Check validation */
        {
            printf("\nInput Error!");
            return 1;
        }
        counter_moves++;

        board[row][col] = 'X';
        printBoard(board,size_row);
        if (counter_moves >= size_row*2-1) /* Condition for filtering cases that the win is impossible */
            if (check_win(board,row,col,size_row,'X') == 1)
            {
                printf("\nPlayer A won the game!");
                return 0;
            }

        if (counter_moves == size_row*size_row) /* The board is full */
        {
            printf("\nTIE");
            return 0;
        }


        printf("\nThe turn of B, type your choice (row col): ");  /* Get input position of '0' */
        if (scanf("%d%d",&row,&col) != 2)
        {
            printf("\nInput Error!");
            return 1;
        }
        if (row<0 || col<0 || row>=size_row || col>=size_row || board[row][col]!=' ') /* Check validation */
        {
            printf("\nInput Error!");
            return 1;
        }
        counter_moves++;

        board[row][col] = 'O';
        printBoard(board,size_row);
        if (counter_moves >= size_row*2-1) /* Condition for filtering cases that the win is impossible */
            if (check_win(board,row,col,size_row,'O') == 1)
            {
                printf("\nPlayer B won the game!");
                return 0;
            }

    }

    free_board(board,size_row);
    return 0;
}

char **create_board(int size)
/*
Function Name: create_board()
Description: Create 2D array with dynamic allocation and reset the array.
Input: size of the array (square array).
Output: pointer to the start of the array.
*/
{
    int i,j;
    char **board;

    board = (char**) malloc(sizeof(char*)*size);
    if (board == NULL)
    {
        printf("\nAllocation failed!");
        exit(1);
    }

    for (i=0; i<size; i++)
    {
        board[i] = (char*) malloc(sizeof(char)*size);
        if (board[i] == NULL)
        {
            printf("\nAllocation failed!");
            exit(1);
        }
    }

    for (i=0; i<size; i++) /* Enter ' '(space) to all the array */
        for (j=0; j<size; j++)
            board[i][j] = ' ';
    printBoard(board,size);
    return board;
}


void printBoard(char **board, int size)
/*
Function Name: printBoard()
Description: print the board.
Input: pointer to the array of the board and the array's size.
Output: just print.
*/
{
    int i,j;
    printf("\n");
    for(i=0;i<size;i++)
    {
        for(j=0;j<size;j++)
        {
            printf("[%c] ",board[i][j]);
        }
        printf("\n");
    }
}

int check_win (char **board, int row, int col, int size, char mark)
/*
Function Name: check_win()
Description: Check if one of the players won (check row, column, main diagonal and secondary diagonal)
Input: board of the game,position of row and column of the new input, size of the sqare array, and the mark of the player ('X' or 'O').
Output: 1 if win, 0 if not.
*/
{
    int i, j, help_check=TRUE; /* i and j indexes of the loop and help_check is auxilary variable */

    for (i=0; i<size; i++) /* Check row */
        if (board[row][i] != mark)
            help_check = FALSE;
    if (help_check == TRUE)
        return 1;


    help_check = TRUE; /* Check column */
    for (i=0; i<size; i++)
        if (board[i][col] != mark)
            help_check = FALSE;
    if (help_check == TRUE)
        return 1;


    if (row == col) /* Check main diagonal */
    {
        help_check = TRUE;
        for (i=0; i<size; i++)
        if (board[i][i] != mark)
            help_check = FALSE;
    }
    if (help_check == TRUE)
        return 1;


    if (row + col == size - 1) /* Check Secondary diagonal */
    {
        help_check = TRUE;
        for (i=0; i<size; i++)
            for (j=size-1; j>=0; j--)
                if (board[i][j] != mark && i+j==size-1)
                    help_check = FALSE;
    }
    if (help_check == TRUE)
        return 1;

    return 0;
}


void free_board (char **board, int size)
/*
Function Name: free_board()
Description: free the memory that we allocated.
Input: board and his size.
Output: just free.
*/
{
    int i=0;

    while (i<size)
        free(board[i++]);
    free (board);
    return;
}

