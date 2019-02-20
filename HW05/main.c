#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
utility.h
Source code with some useful utilities.
Author: Jiří Škoda
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

/*
dynamic.h
Source code with some useful functions solving dynamic allocating of memory.
Author: Jiří Škoda
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

/*
caesar.log.h
Source code with functions to log proccess of Caesar's cipher decoding
Author: Jiří Škoda
		student of
		Open Informatics
		at
		Faculty of Electrical Engineering
		at
		Czech Techical Universtity in Prague
*/

#ifndef WIDTH
#define WIDTH 96
#endif // !WIDTH



#ifndef CAESAR_LOG_INCLUDE
#define CAESAR_LOG_INCLUDE



void printSimpleHeader(array encoded, array decoded)
{
	printNtimes('*', WIDTH);
	printf("\n\n");
	setColor("white");
	printCenterSpaces(19, WIDTH);
	printf("SIMPLE DECODING LOG\n\n");
	resetColor();
	printNtimes(' ', 1);
	printColor(makeArray("SETTINGS:", 10), "yellow");
	resetColor();
	printf("\n");
	setColor("white");
	printf("ENCODED MESSAGE:");
	resetColor();
	printf("\n");
	printArray(encoded);
	printf("\n");
	setColor("white");
	printf("PARTLY DECODED MESSAGE:");
	printf("\n");
	resetColor();
	printArray(decoded);
	printf("\n\n");
	printNtimes('-', WIDTH);
	printf("\n");
	printCenterSpaces(26, WIDTH);
	printColor(makeArray("ACTION: ", 9), "white");
	printf("Find string with");
	printf("\n");
	printCenterSpaces(10, WIDTH);
	printf("the maximum matching letters.");
	printf("\n");
}

void printSimpleTableHeader()
{
	printNtimes('-', WIDTH);
	printf("\n");
	printColor(makeArray("ROW", 3), "magenta");
	printf(" | ");
	printNtimes(' ', (WIDTH - 40) / 2);
	printColor(makeArray("SHIFTED STRING", 14), "blue");
	printNtimes(' ', (WIDTH - 40) / 2);
	printf(" | ");
	printColor(makeArray("MATCHING LETTERS", 16), "green");
	printf("\n");
	printNtimes('-', WIDTH);
	printf("\n");
}

void printSimpleRow(int row, array shifted_string, int matching_letters)
{
	setColor("magenta");
	printf("%02i ", row);
	resetColor();
	printf(" | ");
	setColor("blue");
	printArray(shifted_string);
	resetColor();
	printf(" | ");
	setColor("green");
	printf("%2i\n", matching_letters);
	resetColor();
}

void printAdvancedHeader(array encoded, array decoded)
{
	printNtimes('*', WIDTH);
	printf("\n\n");
	setColor("white");
	printCenterSpaces(21, WIDTH);
	printf("ADVANCED DECODING LOG\n\n");
	resetColor();
	printNtimes(' ', 1);
	printColor(makeArray("SETTINGS:", 10), "yellow");
	resetColor();
	printf("\n");
	setColor("white");
	printf("ENCODED MESSAGE:");
	resetColor();
	printf("\n");
	printArray(encoded);
	printf("\n");
	setColor("white");
	printf("PARTLY DECODED MESSAGE:");
	printf("\n");
	resetColor();
	printArray(decoded);
	printf("\n\n");
	printNtimes('-', WIDTH);
	printf("\n");
	printCenterSpaces(26, WIDTH);
	printColor(makeArray("ACTION: ", 9), "white");
	printf("Find string with the lowest");
	printf("\n");
	printCenterSpaces(10, WIDTH);
	printf("Levenshtein distance.");
	printf("\n");
}

void printAdvancedTableHeader()
{
	printNtimes('-', WIDTH);
	printf("\n");
	printColor(makeArray("ROW", 3), "magenta");
	printf(" | ");
	printNtimes(' ', (WIDTH - 64) / 2);
	printColor(makeArray("SHIFTED STRING", 14), "blue");
	printNtimes(' ', (WIDTH - 64) / 2);
	printf(" |  ");
	printColor(makeArray("MATCHING LETTERS", 16), "green");
	printf(" | ");
	printColor(makeArray("LEVENSHTEIN DISTANCE", 16), "cyan");
	printf("\n");
	printNtimes('-', WIDTH);
	printf("\n");
}

void printAdvancedRow(int row, array shifted_string, int matching_letters, int levenshtein_distance)
{
	setColor("magenta");
	printf("%02i ", row);
	resetColor();
	printf(" | ");
	setColor("blue");
	printArray(shifted_string);
	resetColor();
	printf(" | ");
	setColor("green");
	printf("%2i", matching_letters);
	resetColor();
	printf(" | ");
	setColor("cyan");
	printf("%2i\n", levenshtein_distance);
	resetColor();
}

void printResultHeader(void)
{
	resetColor();
	printf("\n");
	setColor("red");
	printCenterSpaces(16, WIDTH);
	printf("RESULT OF ACTION");
	printf("\n");
	resetColor();
}

void printResult(array encoded, array decoded, int exit_code)
{
	printf("\n");
	printNtimes('-', WIDTH);
	printf("\n");
	printCenterSpaces(16, WIDTH);
	printColor(makeArray("RESULT OF PROGRAM", 17), "yellow");
	printf("\n");
	printNtimes(' ', 2);
	printColor(makeArray("ENCODED MESSAGE", 15), "white");
	printf("\n");
	printArray(encoded);
	printf("\n");
	printNtimes(' ', 2);
	printColor(makeArray("DECODED MESSAGE", 15), "white");
	printf("\n");
	printArray(decoded);
	printf("\n");
	printColor(makeArray("PROGRAM FINISHED WITH EXIT CODE ",32),"blue");
	setColor("cyan");
	printf("%i\n", exit_code);
	resetColor();
	printNtimes('*', WIDTH);
	printf("\n");

}

#endif

/*
caesar.h
Source code with some useful functions solving Caesar's cipher.
Author: Jiří Škoda
		student of
		Open Informatics
		at
		Faculty of Electrical Engineering
		at
		Czech Techical Universtity in Prague
*/

#ifndef CAESAR_INCLUDE
#define CAESAR_INCLUDE



//Function to shift letter
char shiftLetter(char letter, int direction)
{
	char reti = letter;
	reti += direction;
	if (reti < 65)      //check if letter after shift is at least A (65)
	{
		direction += (letter - 65);
		reti = (122 + direction) + 1;
	}

	if (reti > 122)     //check if letter after shift is max z (122)
	{
		reti = 65 + (direction - (122 - letter));
		reti -= 1;
	}

	if (reti > 90 && reti < 97) //check if leter is not in space of ASCII table between Z (90) and a (97)
	{
		if (direction > 0)
		{
			reti = 97 + (direction - (90 - letter));
			reti -= 1;
		}
		else
		{
			reti = 90 + (direction + (letter - 97));
			reti += 1;
		}
	}

	return reti;
}


//Procedure to shift array
void pShiftArray(char *input, int count, int direction)
{
	for (int i = 0; i < count; i++)
	{
		input[i] = shiftLetter(input[i], direction);
	}
}

//Procedure to shift array accepting array struct
void shiftArray(array input, int direction)
{
	pShiftArray(input.data, input.count, direction);
}

//Function to check validity of char
bool isValid(char input)
{
	if ((input >= 65 && input <= 90) || (input >= 97 && input <= 122))
	{
		return TRUE;
	}

	return FALSE;
}

//Function to check validity of array
bool checkArray(array input)
{
	bool reti = TRUE;

	for (int i = 0; i < input.count; i++)
	{
		if (reti == TRUE)
		{
			reti = isValid(input.data[i]);
		}

		if (reti == FALSE)
		{
			break;
		}
	}

	return reti;

}

//Function to get count of same letters
int getSameLetters(array string1, array string2)
{
	int reti = 0;
	int count;

	count = string1.count < string2.count ? string1.count : string2.count;

	for (int i = 0; i < count; i++)
	{
		if (string1.data[i] == string2.data[i])
		{
			reti++;
		}
	}

	return reti;
}

//Function to decode message
array decodeSimple(array encoded, array decoded, bool log)
{

	if (log == TRUE)
	{
		printSimpleHeader(encoded, decoded);
		printSimpleTableHeader();
	}

	int r = 1;

	array reti = copyArray(encoded);
	int best_match = getSameLetters(encoded, decoded);

	if (log == TRUE)
	{
		printSimpleRow(r, reti, best_match);
	}

	for (int i = 0; i < 52; i++)
	{
		r++;
		shiftArray(encoded, 1);
		int match = getSameLetters(encoded, decoded);
		if (match > best_match)
		{
			best_match = match;
			freeArray(reti);
			reti = copyArray(encoded);
		}

		if (log == TRUE)
		{
			printSimpleRow(r, encoded, match);
		}
	}

	r++;

	if (log == TRUE)
	{
		printResultHeader();
		printSimpleRow(r, reti, best_match);
		printResult(encoded, reti, 0);
	}

	return reti;
}

//Function to compute Levenshtein Distance of two strings
int getLevenshteinDistance(array string1, array string2)
{

	int** matrix;

	matrix = malloc(string1.count * sizeof(int*));
	for (int i = 0; i < string1.count; i++) {
		matrix[i] = malloc(string2.count * sizeof(int));
	}



	for (int i = 0; i < string1.count; i++)
	{
		matrix[i][0] = i;
	}

	for (int i = 0; i < string2.count; i++)
	{
		matrix[0][i] = i;
	}

	for (int i = 1; i < string1.count; i++)
	{
		for (int j = 1; j < string2.count; j++)
		{
			if (string1.data[i] == string2.data[j])
			{
				matrix[i][j] = matrix[(i - 1)][(j - 1)];
			}
			else
			{
				int nums[] = { (matrix[(i - 1)][j] + 1) , (matrix[i][(j - 1)] + 1) , (matrix[(i - 1)][(j - 1)] + 1) };
				matrix[i][j] = getMin(nums, 3);

			}

		}
	}

	int reti = matrix[(string1.count - 1)][(string2.count - 1)];


	for (int i = 0; i < string1.count; i++) {
		free(matrix[i]);
	}
	free(matrix);
	return reti;
}

//Function to decode message using Levenshtein Distance
array decodeAdvanced(array encoded, array decoded, bool log)
{

	if (log == TRUE)
	{
		printAdvancedHeader(encoded, decoded);
		printAdvancedTableHeader();
	}

	int r = 1;
	array reti = copyArray(encoded);
	int lowest_ld = getLevenshteinDistance(encoded, decoded);

	if (log == TRUE)
	{
		printAdvancedRow(r, reti, getSameLetters(encoded, decoded),lowest_ld);
	}

	for (int i = 0; i < 52; i++)
	{
		r++;
		shiftArray(encoded, 1);
		int ld = getLevenshteinDistance(encoded, decoded);
		if (ld < lowest_ld)
		{
			lowest_ld = ld;
			freeArray(reti);
			reti = copyArray(encoded);
		}

		if (log == TRUE)
		{
			printAdvancedRow(r, encoded, getSameLetters(encoded, decoded), ld);
		}
	}

	r++;

	if (log == TRUE)
	{
		printResultHeader();
		printAdvancedRow(r, reti, getSameLetters(reti, decoded), lowest_ld);
		printResult(encoded, reti, 0);
	}

	return reti;
}





#endif




//Main function
int main(int argc, char *argv[])
{
	array encoded = loadDynamicArray('\n');
	if (checkArray(encoded) == FALSE)
	{
		freeArray(encoded);
		fprintf(stderr, "Error: Chybny vstup!\n");
		return 100;
	}
	array decoded = loadDynamicArray('\n');
	if (checkArray(decoded) == FALSE)
	{
		freeArray(encoded);
		freeArray(decoded);
		fprintf(stderr, "Error: Chybny vstup!\n");
		return 100;
	}

	if (encoded.count != decoded.count && hasArgument(argv, argc, "-prp-optional") == FALSE)
	{
		freeArray(encoded);
		freeArray(decoded);
		fprintf(stderr, "Error: Chybna delka vstupu!\n");
		return 101;
	}


	if (hasArgument(argv, argc, "-prp-optional") == TRUE)
	{
		array decoded_message = decodeAdvanced(encoded, decoded, hasArgument(argv, argc, "-log"));
		if (hasArgument(argv, argc, "-log") == FALSE)
		{
			printArray(decoded_message);
		}
		freeArray(decoded_message);
	}
	else
	{
		array decoded_message = decodeSimple(encoded, decoded, hasArgument(argv, argc, "-log"));
		if (hasArgument(argv, argc, "-log") == FALSE)
		{
			printArray(decoded_message);
		}
		freeArray(decoded_message);
	}
	printf("\n");
	freeArray(encoded);
	freeArray(decoded);
	return 0;

}

