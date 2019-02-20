#include <stdio.h>

int main()
{
	int n;

	if (scanf("%d", &n) == 1)
	{
		printf("\nParsed number is %d ", n);
		for (int i = 0; i < n; i++)
		{
			printf("Vypisuji %d \n", i);
		}
	}
	else
	{
		printf("Input number has not been parsed!\n");
	}


	return 0;
}