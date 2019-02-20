
#include <stdio.h>

//Print recursively n-times hello world
void print_hello_world(int);

//Get length of string recursively
int rec_strlen(char*);

//Print numbers of selected ciphers and length (recursively, of course)
void print_numbers(int*, int, int, int);

/* Main function */
int main(int argc, char* argv[])
{
	print_hello_world(1);
	char s[] = { 't', 'e', 's', 't', '\0' };

	int ciphers[] = { 1, 2, 7 };
	int numbers_length = 3;

	printf("String length: %i\n", rec_strlen(s));

	print_numbers(ciphers, 0, (sizeof(ciphers) / sizeof(int)), numbers_length);
	printf("\n");

	return 0;
}



void print_hello_world(int n)
{
	if (n > 0)
	{
		printf("Hello world!\n");
		print_hello_world(n - 1);
	}
}

int rec_strlen(char* string)
{
	if (*string == '\0')
		return 0;
	else
		return (1 + rec_strlen(string + 1));
}

void print_numbers(int* ciphers, int number, int length, int depth)
{
	if (depth == 0)
	{
		printf("%i ", number);
	}
	else
	{
		for (int i = 0; i < length; i++)
		{
			print_numbers(ciphers, (ciphers[i] + (10 * number)), length, (depth - 1));
		}
	}


}
