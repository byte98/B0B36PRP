#include <stdio.h>

double Leibniz(int n);
void printBinary(int input);

int main()
{
	int reti = 0;
	//int n = 0;
	//int product = 1;
	char n = 0;
	//if (scanf("%i", &n) == 1)
	if (scanf("%c", &n) == 1)
	{
		//Even numbers to n
		/*for (int i = 0; i <= n; i++)
		{
			if (i % 2 == 0)
			{
				printf("%i ", i);
				if (i != 0)
				{
					product *= i;
				}
				
			}
		}*/

		//n even numbers
		/*
		int count = 0;
		int nr = 0;
		while (count < n)
		{
			if (nr % 2 == 0)
			{
				printf("%i ", nr);
				count++;
				if (nr != 0)
				{
					product *= nr;
				}
				
			}
			nr++;
		}*/
		//-1 1 numbers
		/*
		int one = 1;
		for (int i = 0; i < n; i++)
		{
			printf("%i, ", one);
			one *= -1;
		}*/

		//Ludolf's number
		//printf("%.50f", Leibniz(n));

		//Number formats
		printf("\n");
		printf("%c\n", n);
		printf("%i\n", n);
		printf("0x%x\n", n);
		printBinary(n);
	}
	else
	{
		reti = -1;
	}
	//printf("Soucin: %i", product);
	printf("\n");
	return reti;
}

double Leibniz(int n)
{
	double reti = 0;
	double one = 1;

	for (int k = 0; k < n; k++)
	{
		reti += (one / (2 * k + 1));
		one *= -1;
	}
	return (4 * reti);
}

void printBinary(int input)
{
	int b = 128;
	printf("b");
	while (b >= 1)
	{
		(input & b) ? printf("1") : (printf("0"));
		//b /= 2;

		//b = b >> 1;
		b >>= 1;
	}
}
