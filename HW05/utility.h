/*
utility.h
Source code with some useful utilities.
Author: Jiøí Škoda
		student of
		Open Informatics
		at
		Faculty of Electrical Engineering
		at
		Czech Techical Universtity in Prague
*/

#ifndef UTILITY_INCLUDE
#define UTILITY_INCLUDE

#define bool int
#define TRUE 1
#define FALSE 0

#define color char*

//Definitions of colors in shell
#define RED   "\x1B[1;31m"
#define GRN   "\x1B[1;32m"
#define YEL   "\x1B[1;33m"
#define BLU   "\x1B[1;34m"
#define MAG   "\x1B[1;35m"
#define CYN   "\x1B[1;36m"
#define WHT   "\x1B[1;37m"
#define RESET "\x1B[1;0m"

//Array structure for keeping data and size of array
typedef struct arrays
{
	int count;
	char *data;
} array;




//Function to make array
array makeArray(char *data, int count)
{
	array reti;
	reti.data = data;
	reti.count = count;
	return reti;
}

//Function to copy data
char* copyData(char* input, int count)
{
	char *reti = malloc(count * sizeof(char));
	for (int i = 0; i < count; i++)
	{
		reti[i] = input[i];
	}

	return reti;
}

//Function to copy array
array copyArray(array input)
{
	array reti;
	reti.data = copyData(input.data, input.count);
	reti.count = input.count;

	return reti;
}

//Function to print char n times
void printNtimes(char input, int count)
{
	for (int i = 1; i <= count; i++)
	{
		printf("%c", input);
	}
}

//Function to print array
void printArray(array input)
{
	for (int i = 0; i < input.count; i++)
	{
		printf("%c", input.data[i]);
	}
}

//Function to get color from name
color getColorFromName(color name)
{
	color reti = RESET;
	if (strncmp(name, "red", 3) == 0)
	{
		reti = RED;
	}
	else if (strncmp(name, "green", 5) == 0)
	{
		reti = GRN;
	}
	else if (strncmp(name, "yellow", 6) == 0)
	{
		reti = YEL;
	}
	else if (strncmp(name, "blue", 4) == 0)
	{
		reti = BLU;
	}
	else if (strncmp(name, "magenta", 7) == 0)
	{
		reti = MAG;
	}
	else if (strncmp(name, "cyan", 4) == 0)
	{
		reti = CYN;
	}
	else if (strncmp(name, "white", 5) == 0)
	{
		reti = WHT;
	}

	return (char*)reti;
}

//Function to set color
void setColor(color c)
{
	array color_array;
	color_array.data = getColorFromName(c);
	color_array.count = 7;

	printArray(color_array);

}

void printColor(array string, color c)
{
	printArray(makeArray(getColorFromName(c), 7));
	printArray(string);
	printf(RESET);
}

//Function to check if arguments of main has searched argument
bool hasArgument(char *argv[], int argc, char *arg)
{
	int i;
	for (i = 0; i < argc; i++)
	{
		if (strstr(argv[i], arg) != NULL)
		{
			return TRUE;
		}

	}
	return FALSE;
}

//Function to print char n times in color
void printNtimesColor(char input, int count, color c)
{
	setColor(c);
	printNtimes(input, count);
	printf(RESET);
}

//Function to print string in center of space
void printCenterSpaces(int string_width, int space_width)
{
	printNtimes(' ', ((space_width - string_width) / 2));
}


//Function to get minimum from array items
int getMin(int *numbers, int count)
{
	int reti = numbers[0];
	for (int i = 0; i < count; i++)
	{
		if (numbers[i] < reti)
		{
			reti = numbers[i];
		}
	}
	return reti;
}

//Function to reset color
void resetColor(void)
{
	printf(RESET);
}

#endif
