#include <stdio.h>

//Print n stars on line
void stars(int);

//Print n × n matrix
void print_matrix(int);

//Print top-left bottom-right diagonal of n × n matrix
void print_first_diag(int);

//Print top-right bottom-left diagonal of n × n matrix
void print_second_diag(int);

//Print both diagonals of n × n matrix
void print_both_diag(int);

static char *name_of_month[] = {
	"January",
	"February",
	"March",
	"April",
	"May",
	"June",
	"July",
	"August",
	"September",
	"October",
	"November",
	"December"
};
static int days_in_month[] = { 31, 29, 31, 30, 31, 30,
							   31, 31, 30, 31, 30, 31 };
static int first_day_in_year = 0; // 1. 1. 2018 is Monday

//Print month
void print_month(int);

//Print months from to
void print_months(int, int);



int main(int argc, char **argv)
{
	//Size of matrix
	int SIZE = 8;

	printf("\n");
	print_matrix(SIZE);
	printf("\n");
	print_first_diag(SIZE);
	printf("\n");
	print_second_diag(SIZE);
	printf("\n");
	print_both_diag(SIZE);
	printf("\n");
	print_month(10);
	printf("---\n");
	print_months(9, 11);
}

void stars(int n)
{
	for (; n >= 0; n--)
	{
		printf("*");
	}
	printf("\n");
}

void print_matrix(int size)
{
	int max = (size * size) - 1;
	for (int i = 0; i <= max; i++)
	{
		printf("%3i", i);
		if (i % size == (size - 1) && i > 0)
		{
			printf("\n");
		}
	}
}

void print_first_diag(int size)
{
	int max = (size * size) - 1;
	int row = 0;
	for (int i = 0; i <= max; i++)
	{
		if (i % size == row)
		{
			printf("%3i", i);
		}
		else
		{
			printf("   ");
		}
		
		if (i % size == (size - 1) && i > 0)
		{
			printf("\n");
			row++;
		}
	}
}

void print_second_diag(int size)
{
	int max = (size * size) - 1;
	int row = 1;
	for (int i = 0; i <= max; i++)
	{
		if (i % size == (size - row))
		{
			printf("%3i", i);
		}
		else
		{
			printf("   ");
		}

		if (i % size == (size - 1) && i > 0)
		{
			printf("\n");
			row++;
		}
	}
}

void print_both_diag(int size)
{
	int max = (size * size) - 1;
	int row = 0;
	for (int i = 0; i <= max; i++)
	{
		if (i % size == row)
		{
			printf("%3i", i);
		}
		else if(i % size == (size - (row + 1)))
		{
			printf("%3i", i);
		}
		else
		{
			printf("   ");
		}

		if (i % size == (size - 1) && i > 0)
		{
			printf("\n");
			row++;
		}
	}
}

void print_month(int month)
{
	int month_index = month - 1;
	int start_day = first_day_in_year;
	for (int m = 0; m < month_index; m++)
	{
		start_day += days_in_month[m];
	}
	start_day = (start_day % 7);

	printf(" %s\n", name_of_month[month_index]);
	printf(" Mo Tu We Th Fr Sa Su \n");
	for (int i = 1; i < (days_in_month[month_index] + start_day); i++)
	{
		if (i < start_day)
		{
			printf("   ");
		}
		else
		{
			printf("%3i", (i - start_day + 1));
		}
		
		if (i % 7 == 0)
		{
			printf("\n");
		}
	}
}

void print_months(int start, int end)
{
	for (int i = (start - 1); i <= (end - 1); i++)
	{
		print_month(i);
		printf("\n");
	}
}
