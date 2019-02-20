#include <stdio.h>

#pragma warning(disable : 4996)

int main()
{
	int reti = 0;
	int i;
	printf("Enter input:");
	if (scanf("%i", &i) == 1)
	{
		if (i > 20)
		{
			printf("Hello1\n");
		}
		else
		{
			if (i == 10)
			{
				printf("Hello2\n");
			}
			else
			{
				printf("Hello3\n");
			}
		}
	}
	else
	{
		printf("CHYBNY VSTUP!\n");
		reti = -1;
	}

	return reti;
	
}
