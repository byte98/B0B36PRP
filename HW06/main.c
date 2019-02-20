#include <stdio.h>
#include <stdlib.h>


/*
matrix.h
Source code with functions to work with matrices.
Author: Jiri Skoda
Student of Open Informatics
at Faculty of Electrical Engineering
of Czech Technical University in Prague

(c) Jiri Skoda 2017
*/

#ifndef MATRIX_H_INCLUDE
#define MATRIX_H_INCLUDE

#ifndef MAX
#define MAX 100
#endif // !MAX


#define bool int
#define TRUE 1
#define FALSE 0

#include <limits.h>
#define ERR INT_MAX

int actual_row = 0;
int actual_col = 0;

typedef struct matrix
{
	int rows;
	int cols;
	int** data;
} matrix;



//Function to free memory allocated by matrix
void freeMatrix(matrix input)
{
	for (int i = 0; i < input.rows; i++)
	{
		free(input.data[i]);
	}
	free(input.data);
}

//Function to print matrix
void printMatrix(matrix input)
{
	for (int r = 0; r < input.rows; r++)
	{
		for (int c = 0; c < input.cols; c++)
		{
			if (c > 0)
			{
				printf(" ");
			}
			printf("%i", input.data[r][c]);
		}
		printf("\n");
	}
}

//Function to raise indexes of rows and cols
void raiseRowsAndCols(matrix checking_matrix)
{
	actual_col++;
	if (actual_col >= checking_matrix.cols)
	{
		actual_col = 0;
		actual_row++;
	}
}

//Function to allocate memory for matrix
matrix mallocMatrix(int rows, int cols)
{
	matrix reti;
	reti.cols = cols;
	reti.rows = rows;
	reti.data = (int **)malloc(rows * sizeof(int *));
	for (int i = 0; i < rows; i++)
	{
		reti.data[i] = (int *)malloc(cols * sizeof(int));
	}

	return reti;
}


//Function which returns error matrix
matrix errMatrix(void)
{
	matrix reti = mallocMatrix(2, 2);
	reti.data[0][0] = ERR;
	reti.data[0][1] = ERR;
	reti.data[1][0] = ERR;
	reti.data[1][1] = ERR;

	return reti;
}

//Function to load matrix
matrix loadMatrix(int rows, int cols)
{
	matrix reti = mallocMatrix(rows, cols);
	for (int i = 0; i < (rows * cols); i++)
	{
		int input = 0;
		if (scanf("%i", &input) == 0)
		{
			freeMatrix(reti);
			return errMatrix();
		}
		reti.data[actual_row][actual_col] = input;
		raiseRowsAndCols(reti);
	}


	actual_col = 0;
	actual_row = 0;
	return reti;
}

//Function to add member to matrix
matrix addMember(int member, matrix matrix)
{
	matrix.data[actual_row][actual_col] = member;
	raiseRowsAndCols(matrix);
	return matrix;
}

//Function to check two matrixes
bool isSame(matrix input1, matrix input2)
{
	if (input1.rows == input2.rows && input1.cols == input2.cols)
	{
		for (int r = 0; r < input1.rows; r++)
		{
			for (int c = 0; c < input1.cols; c++)
			{
				if (input1.data[r][c] != input2.data[r][c])
				{
					return FALSE;
				}
			}
		}

		return TRUE;
	}

	return FALSE;
}

//Function to load unknown length matrix
matrix loadUnknownMatrix(void)
{
	int cols = 0;
	int rows = 0;
	matrix reti = mallocMatrix(MAX, MAX);

	int col_index = 0;
	int row_index = 0;

	int count = 0;
	int input = 0;
	do
	{
		count = scanf("%i", &input);
		reti.data[row_index][col_index] = input;
		col_index++;
		if (rows == 0)
		{
			cols++;
		}
		if (getchar() == '\n')
		{
			rows++;
			col_index = 0;
			row_index++;
		}
	} while (count > 0);

	reti.cols = cols;
	reti.rows = rows;

	return reti;

}

#endif // !MATRIX_H

/*
matrix.math.h
Source code with functions to provide counting with matrices.
Author: Jiri Skoda
Student of Open Informatics
at Faculty of Electrical Engineering
of Czech Technical University in Prague

(c) Jiri Skoda 2017
*/

#ifndef MATRIX_MATH_INCLUDE
#define MATRIX_MATH_INCLUDE




//Function to sum two matrices
matrix sum(matrix input1, matrix input2)
{
	if (input1.rows == input2.rows && input1.cols == input2.cols)
	{
		matrix reti = mallocMatrix(input1.rows, input2.cols);
		for (int r = 0; r < input1.rows; r++)
		{
			for (int c = 0; c < input1.cols; c++)
			{
				reti.data[r][c] = input1.data[r][c] + input2.data[r][c];
			}
		}

		return reti;
	}
	else
	{
		return errMatrix();
	}
}

//Function to substract two matrices
matrix minus(matrix input1, matrix input2)
{
	if (input1.rows == input2.rows && input1.cols == input2.cols)
	{
		matrix reti = mallocMatrix(input1.rows, input2.cols);
		for (int r = 0; r < input1.rows; r++)
		{
			for (int c = 0; c < input1.cols; c++)
			{
				reti.data[r][c] = input1.data[r][c] - input2.data[r][c];
			}
		}

		return reti;
	}
	else
	{
		return errMatrix();
	}
}

//Function to get member of matrix after multiply
int getMultiplyResult(int row, matrix input1, int col, matrix input2)
{
	int reti = 0;
	int r = 0;
	int c = 0;

	while (c < input1.cols && r < input2.rows)
	{
		reti += (input1.data[row][c] * input2.data[r][col]);


		r++;
		c++;
	}

	return reti;
}


//Function to multiply two matrices
matrix multiply(matrix input1, matrix input2)
{
	if (input1.cols != input2.rows)
	{
		return errMatrix();
	}

	matrix reti = mallocMatrix(input1.rows, input2.cols);

	for (int row = 0; row < reti.rows; row++)
	{
		for (int col = 0; col < reti.cols; col++)
		{
			reti.data[row][col] = getMultiplyResult(row, input1, col, input2);
		}
	}

	return reti;
}

//Function to provide operation selection and select right counting function
matrix compute(matrix input1, char op, matrix input2)
{
	switch (op)
	{
	case '+':
		return sum(input1, input2);
		break;
	case '-':
		return minus(input1, input2);
		break;
	case '*':
		return multiply(input1, input2);
		break;
	default:
		return errMatrix();
		break;
	}
}

//Function to check if multiplying is included
int multiplyMatrices(matrix *matrices, int count, char* ops)
{
	int op_c = 0;
	int m_c = 0;
	int reti = count;
	while (op_c < count)
	{
		if (ops[op_c] == '*')
		{
			matrices[op_c] = multiply(matrices[m_c], matrices[(m_c + 1)]);
			reti--;
			m_c++;
		}
		else
		{
			matrices[op_c] = matrices[m_c];
		}

		op_c++;
		m_c++;
	}
	return reti;
}

//Function to sum matrices
matrix computeResult(matrix *matrices, int count1, char *ops, int count2)
{
	matrix reti = matrices[0];
	int index = 1;
	for (int i = 0; i < (count2 - 1); i++)
	{
		if (ops[i] != '*')
		{
			reti = compute(reti, ops[i], matrices[index]);
			index++;
		}
	}
	return reti;
}




#endif

/*
main.c
Main program file for homework 6 for subject Procedrual Programming
Author: Jiri Skoda
Student of Open Informatics
at Faculty of Electrical Engineering
of Czech Technical University in Prague

(c) Jiri Skoda 2017
*/


//Just simple function to free data in matrices
void freeMatrices(matrix *matrices, int count)
{
	for (int i = 0; i < count; i++)
	{
		freeMatrix(matrices[i]);
	}
	free(matrices);
}

int main(int argc, char *argv[])
{

	matrix *matrices = (matrix*)malloc(128 * sizeof(matrix));
	int index = 0;
	char *ops = (char*)malloc(128 * sizeof(char));
	char check;

	matrix err = errMatrix();

	do
	{
		int rows = 0;
		int cols = 0;

		if (scanf("%i%i", &rows, &cols) != 2)
		{
			free(ops);
			freeMatrix(err);
			freeMatrices(matrices, 128);
			fprintf(stderr, "Error: Chybny vstup!\n");
			return 100;
		}

		matrices[index] = loadMatrix(rows, cols);
		if (isSame(err, matrices[index]))
		{

			free(ops);
			freeMatrix(err);
			freeMatrices(matrices, 128);
			fprintf(stderr, "Error: Chybny vstup!\n");
			return 100;
		}

		ops[index] = getchar();
		while (ops[index] == '\n')
		{
			ops[index] = getchar();
		}


		index++;

	} while (scanf("%c", &check) != EOF);

	int count = multiplyMatrices(matrices, index, ops);
	matrix *matrices2 = malloc(count * sizeof(matrix));
	for (int i = 0; i < count; i++)
	{
		matrices2[i] = matrices[i];
	}
	freeMatrices(matrices, index);
	matrix output = computeResult(matrices2, count, ops, index);

	freeMatrices(matrices2, count);

	printf("%i %i\n", output.rows, output.cols);

	printMatrix(output);

	freeMatrix(output);

	free(ops);
	freeMatrix(err);

	return 0;

}

