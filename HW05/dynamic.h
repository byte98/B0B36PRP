/*
dynamic.h
Source code with some useful functions solving dynamic allocating of memory.
Author: Jiøí Škoda
		student of
		Open Informatics
		at
		Faculty of Electrical Engineering
		at
		Czech Techical Universtity in Prague
*/

#ifndef DYNAMIC_INCLUDE
#define DYNAMIC_INCLUDE

#define ERR -1
#include "utility.h"


//Function to load unknown length array
array loadDynamicArray(char end_char)
{
	int count = 0;
	int size = 64;
	array reti;
	reti.data = (char*)malloc(size * sizeof(char));

	char input = 0;
	while (scanf("%c", &input) == 1 && input != end_char)
	{
		if (input == end_char)
		{
			break;
		}
		else
		{
			if ((count + 1) >= size)
			{
				size += 64;
				reti.data = (char*)realloc(reti.data, size * sizeof(char));
			}

			reti.data[count] = input;
			count++;
		}
	}

	reti.count = count;
	return reti;
}

//Function to load known length array
array loadKnownArray(int count)
{
	array reti;
	reti.count = count;
	reti.data = (char*)malloc(count * sizeof(char));

	for (int i = 0; i < count; i++)
	{
		char input;
		if (scanf("%c", &input) == 1)
		{
			reti.data[i] = input;
		}
		else
		{
			reti.data[i] = ERR;
		}

	}

	return reti;
}

//Function to free array
void freeArray(array input)
{
	free(input.data);
}





#endif 
