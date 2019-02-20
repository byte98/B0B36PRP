#include <stdio.h>

int main()
{
	int a = 1;
	int b = 1;
	int act = a + b;


	//Defined iterations
	/*printf("Enter input: ");
	int iter = 0;
	scanf("%d", &iter);
	for (int i = 0; i < iter; i++)
	{
		printf("%i\n", (act));
		a = b;
		b = act;
		act = a + b;
	}*/

	//Defined maximum
	int max = 0;
	printf("Enter input: ");
	scanf("%d", &max);
	while(act < max)
	{
		printf("%i\n", (act));
		a = b;
		b = act;
		act = a + b;		
	}
}
