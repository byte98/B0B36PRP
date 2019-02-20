#include <stdio.h>

int main()
{
	int n;

	if (scanf("%d", &n) == 1 && n <= 100)
	{
		for (int i = 0; i < n; i++)
		{
			for (int c = 0; c < n; c++)
			{
				printf("%d ", (c + 1));
			}
			printf("\n");
		}
		return 0;
	}
	else
	{
		printf("Wrong input!\n");
		return -1;
	}
}