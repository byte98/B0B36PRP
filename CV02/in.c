#include <stdio.h>

int main()
{
	int r, n;
	int counter = 0;
	while ((r = scanf("%d", &n)) == 1)
	{
		counter++;
	}
	if (r == 0)
	{
		printf("Wrong input detected!\n");
		return -1;
	}
	else
	{
		printf("Number lines %d\n", counter);
		return 0;
	}
}