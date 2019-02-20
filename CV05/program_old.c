#include <stdio.h>

//Names of months
static char *names[] = {
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

//First day in year (4.1.)
static int first_day_in_year = 4;

//Days in months
static int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };


//Five stars
void stars(int n)
{
	int row = 1;
	for (int i = 1; i <= n; i++)
	{
		for (int c = 1; c <= row; c++)
		{
			printf("*");
		}
		printf("\n");
		row++;
	}
	row = n;
	for (int i = n; i >= 1; i--)
	{
		for (int c = 1; c <= row; c++)
		{
			printf("*");
		}
		printf("\n");
		row--;
	}
}

//Print number table
void numbers_one(int max)
{
	for (int i = 0; i <= max; i++)
	{
		if (i % 10 == 0 && i != 0)
		{
			printf("\n");
		}

		printf("%3i ", i);
	}
	printf("\n");
}

//Print left-top right-bottom diagonal
void diag(int max)
{
	for (int i = 0; i <= max; i++)
	{
		for (int c = 0; c <= max; c++)
		{
			if (c == i && c == 0)
			{
				printf("%i ", c);
			}
			else if (c == i)
			{
				printf("%i%i", i, c);
			}
			else
			{
				printf("  ");
			}
			printf(" ");


		}
		printf("\n");
	}
}

//Print top-right bottom-left diagonal
void second_diag(int max)
{
	for (int i = 0; i <= max; i++)
	{
		for (int c = 0; c <= max; c++)
		{
			if (c + i == max && i == 0)
			{
				printf(" %i", c);
			}
			else if (c + i == max)
			{
				printf("%i%i", i, c);
			}
			else
			{
				printf("  ");
			}
			printf(" ");


		}
		printf("\n");
	}
}

//Both diagonals
void both_diag(int max)
{
	for (int i = 0; i <= max; i++)
	{
		for (int c = 0; c <= max; c++)
		{
			if (c + i == max && i == 0)
			{
				printf(" %i", c);
			}
			else if (c + i == max)
			{
				printf("%i%i", i, c);
			}
			else if (c == i && c == 0)
			{
				printf("%i ", c);
			}
			else if (c == i)
			{
				printf("%i%i", i, c);
			}
			else
			{
				printf("  ");
			}
			printf(" ");
		}
		printf("\n");
	}
}

//Print number tables
void numbers_two(int max)
{
	for (int i = 0; i <= 9; i++)
	{
		for (int c = 0; c <= 9; c++)
		{
			if (i == 0)
			{
				printf(" %i ", c);
			}
			else
			{
				printf("%i%i ", i, c);
			}

		}
		printf("\n");
	}
}

//Print month
int print_month(int days, int first_day)
{
	printf(" Mo Tu We Th Fr Sa Su\n");
	int day = 1;
	int reti = 0;
	while (day <= days)
	{
		for (int c = 1; c <= 7; c++)
		{
			if (c == first_day && day == 1)
			{
				printf("%3i", day);
				day++;
			}
			else if (day > 1 && day <= days)
			{
				printf("%3i", day);
				day++;
				reti = c;
			}
			else
			{
				printf("   ");
			}
		}
		printf("\n");
	}
	return reti;
}

//Print months from to
void print_months(int starting_month, int finishing_month, int year)
{
	int start_day = first_day_in_year;
	if (year % 4 == 0)
	{
		days[1] = 29;
	}

	int month_index = starting_month - 1;

	for (int i = 0; i <= month_index; i++)
	{
		start_day += days[i];
	}

	start_day = (start_day % 7);

	for (int i = 0; i <= (finishing_month - starting_month); i++)
	{
		printf(" %s\n", names[month_index]);
		start_day = (print_month(days[month_index], start_day) % 7);
		month_index++;
		printf("\n");
	}


}


int main(int argc, char *argv[])
{
	both_diag(5);
	printf("\n");
	print_months(9, 11, 2016);

	return 0;
}