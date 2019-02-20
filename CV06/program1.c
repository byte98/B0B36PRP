#include <stdio.h>
#include <stdlib.h>

void print_array(int*, int);

int strlen(const char* str);

int main(int argc, char *argv[])
{
	int reti = 0;

	int size = 0;
	printf("Size of array? ");
	if (scanf("%i", &size) == 1)
	{
		int* array = malloc(size * sizeof(int));
		int index = 0;
		while (scanf("%i", &array[index]) == 1 && index < size)
		{
			index++;
			if (index >= size)
			{
				break;
			}
		}

		printf("\nArray content:\n");
		print_array(array, size);
		free(array);
	}
	else
	{
		reti = -1;
	}
	return reti;
}

void print_array(int* array, int array_length)
{
	for (int i = 0; i < array_length; i++)
	{
		printf("%i\n", array[i]);
	}
}

int strlen(const char* str)
{
	int reti = 0;
	int i = 0;
	while (str[i] != "\0")
	{
		reti++;
	}
	return reti;
}