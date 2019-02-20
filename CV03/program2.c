#include <stdio.h>

int main(void)
{
	int i = 10;
	

	//Standart for
	for (int j = 0; j < i; j++)
	{
		printf("j = %i, i = %i\n", j, i);
	}

	//Same functionality, different look
	int j = 0;
	for (;;)
	{
		printf("j = %i, i = %i\n", j, i);
		if (j >= i)
		{
			break;
		}
		j++;
	}

	//While
	j = 0;
	while (1)
	{
		printf("j = %i, i = %i\n", j, i);
		if (j >= i)
		{
			break;
		}
		j++;
	}
}
